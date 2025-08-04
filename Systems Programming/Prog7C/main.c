#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

/*

Name: Kevin Ho
NetID: Kth258
Date: 10/12/2024
Description: So the main point of this program is to remake the hi low game but mainly with processes using
forks and signal handk.lers.

*/

// Global variables to track signals
volatile sig_atomic_t player1_ready = 0;
volatile sig_atomic_t player2_ready = 0;
volatile sig_atomic_t player1_guess_signal = 0;
volatile sig_atomic_t player2_guess_signal = 0;
int player1_score = 0;
int player2_score = 0;
int game_target = 0;
pid_t player1_pid, player2_pid;

// Signal handlers for the parent (referee)

// Player 1 is ready or made a guess
void handle_sigusr1(int sig) {
    player1_ready = 1;
    player1_guess_signal = 1;
}

// Player 2 is ready or made a guess
void handle_sigusr2(int sig) {
    player2_ready = 1;
    player2_guess_signal = 1;
}

// Reap any child process that has terminated
void handle_sigchld(int sig) {
    wait(NULL);
}

// SIGINT handler for graceful termination
void handle_sigint(int sig) {
    printf("\nTerminating game...\n");
    kill(0, SIGTERM);
    exit(0);
}

// Signal handlers for the children (players)
volatile sig_atomic_t guess_low = 0;
volatile sig_atomic_t guess_high = 0;
volatile sig_atomic_t game_reset = 0;

// Guess was too low
void handle_player_sigusr1(int sig) {
    guess_low = 1;
}

// Guess was too high
void handle_player_sigusr2(int sig) {
    guess_high = 1;
}

// Reset the game for the next round
void handle_player_sigint(int sig) {
    game_reset = 1;
}

// Exit on SIGTERM
void handle_sigterm(int sig) {
    exit(0);
}

// Function to generate a random number within a range
int generate_random(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

// Player 1 (average-based strategy)
void player1_behavior(int fd) {
    signal(SIGUSR1, handle_player_sigusr1);
    signal(SIGUSR2, handle_player_sigusr2);
    signal(SIGINT, handle_player_sigint);
    signal(SIGTERM, handle_sigterm);

    int min = 0, max = 101, guess;
    char buffer[16];
    struct timespec ts = {3, 0};

    while (1) {
        // Notify the parent the player is ready
        kill(getppid(), SIGUSR1);
        printf("Player 1 is ready.\n");

        // Game loop
        while (!game_reset) {
            guess_low = guess_high = 0;

            // Player 1 guesses the average of the bounds
            guess = (min + max) / 2;

            // Open file with O_TRUNC flag to reset it before writing the guess
            fd = open("player1_guess.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

            // Player makes a guess and writes it to the file
            int len = snprintf(buffer, sizeof(buffer), "%d\n", guess);
            write(fd, buffer, len);
            fsync(fd);  // Make sure the guess is fully written to disk
            close(fd);  // Close the file immediately after writing

            // Notify the referee of the guess
            kill(getppid(), SIGUSR1);
            printf("Player 1 guessed: %d\n", guess);

            // Wait for feedback from the parent
            nanosleep(&ts, NULL);

            // Adjust bounds based on the feedback
            if (guess_low) {
                min = guess;
            } else if (guess_high) {
                max = guess;
            }

            // Break if the game is reset
            if (game_reset) break;
        }

        // Reset min and max for the next game
        min = 0;
        max = 101;
        game_reset = 0;
    }
}

void signal_handler(int sig) {
    if (sig == SIGUSR1) {
        sgn1 = 1;
    } else if (sig == SIGUSR2) {
        sgn2 = 1;
    } else if (sig == SIGINT) {
        sgn1 = 2;
        sgn2 = 2;
    } else if (sig == SIGTERM) {
        printf("Child process exiting due to SIGTERM\n");
        exit(0);  // Exit the program
    }
}
// Player 2 (random-based strategy)
void player2_behavior(int fd) {
    signal(SIGUSR1, handle_player_sigusr1);
    signal(SIGUSR2, handle_player_sigusr2);
    signal(SIGINT, handle_player_sigint);
    signal(SIGTERM, handle_sigterm);

    srand(time(NULL) ^ getpid()); // Seed the random number generator

    int min = 0, max = 101, guess;
    char buffer[16];
    struct timespec ts = {3, 0}; // 50 ms sleep

    while (1) {
        // Notify the parent the player is ready
        kill(getppid(), SIGUSR2);
        printf("Player 2 is ready.\n");

        // Game loop
        while (!game_reset) {
            guess_low = guess_high = 0;

            // Player 2 guesses a random number within the bounds
            guess = generate_random(min, max);

            // Open file with O_TRUNC flag to reset it before writing the guess
            fd = open("player2_guess.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

            // Player makes a guess and writes it to the file
            int len = snprintf(buffer, sizeof(buffer), "%d\n", guess);
            write(fd, buffer, len);
            fsync(fd);  // Make sure the guess is fully written to disk
            close(fd);  // Close the file immediately after writing

            // Notify the referee of the guess
            kill(getppid(), SIGUSR2);
            printf("Player 2 guessed: %d\n", guess);

            // Wait for feedback from the parent
            nanosleep(&ts, NULL);

            // Adjust bounds based on the feedback
            if (guess_low) {
                min = guess;
            } else if (guess_high) {
                max = guess;
            }

            // Break if the game is reset
            if (game_reset) break;
        }

        // Reset min and max for the next game
        min = 0;
        max = 101;
        game_reset = 0;
    }
}

// Parent (Referee) function
void referee() {
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGUSR2, handle_sigusr2);
    signal(SIGCHLD, handle_sigchld);
    signal(SIGINT, handle_sigint);

    srand(time(NULL));

    int player1_fd = open("player1_guess.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int player2_fd = open("player2_guess.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    char buffer[16];
    struct timespec ts = {0, 50000000};  // 50 ms sleep
    struct timespec tss = {5, 0}; // 5 s sleep
    for (int game = 1; game <= 10; game++) {
        printf("Starting game %d\n", game);

        // Wait for both players to be ready
        while (!player1_ready || !player2_ready) {
            printf("Waiting for players to be ready... Player 1: %d, Player 2: %d\n", player1_ready, player2_ready);
            nanosleep(&tss, NULL);
        }

        printf("Both players are ready.\n");

        player1_ready = player2_ready = 0;

        // Generate the target number
        game_target = generate_random(1, 100);
        printf("Referee chose target: %d\n", game_target);

        while (1) {
            // Wait for both players to make their guesses
            while (!player1_guess_signal || !player2_guess_signal) {
                //printf("Waiting for guesses... Player 1 guessed: %d, Player 2 guessed: %d\n", player1_guess_signal, player2_guess_signal);
                nanosleep(&ts, NULL);
            }

            // Read guesses
            player1_guess_signal = player2_guess_signal = 0; // Reset flags here after reading

            // Read Player 1's guess
            lseek(player1_fd, 0, SEEK_SET);  // Go to the start of the file
            read(player1_fd, buffer, sizeof(buffer)); // Read the guess from the file
            int guess1 = atoi(buffer);  // Convert string to integer
            //printf("Player 1 guessed: %d\n", guess1);

            // Read Player 2's guess
            lseek(player2_fd, 0, SEEK_SET);  // Go to the start of the file
            read(player2_fd, buffer, sizeof(buffer)); // Read the guess from the file
            int guess2 = atoi(buffer);  // Convert string to integer
            //printf("Player 2 guessed: %d\n", guess2);

            // Compare guesses to the target

            // Low guess
            if (guess1 < game_target) {
                kill(player1_pid, SIGUSR1);

            // High guess
            } else if (guess1 > game_target) {
                kill(player1_pid, SIGUSR2);

            // Correct guess
            } else {
                player1_score++;
                printf("Player 1 guessed correctly!\n");
                break; // Player 1 guessed correctly
            }

            // Low guess
            if (guess2 < game_target) {
                kill(player2_pid, SIGUSR1);

            // High guess
            } else if (guess2 > game_target) {
                kill(player2_pid, SIGUSR2);

            // Correct guess
            } else {
                player2_score++;
                printf("Player 2 guessed correctly!\n");
                break; // Player 2 guessed correctly
            }


        }

        // Notify both players to reset for the next game
        kill(player1_pid, SIGINT);
        kill(player2_pid, SIGINT);
        nanosleep(&ts, NULL); // Give some time for the players to reset
    }

    // Print final scores
    printf("Final Scores: Player 1: %d, Player 2: %d\n", player1_score, player2_score);

    close(player1_fd);
    close(player2_fd);
    exit(0);
}

int main() {
    // Fork to create Player 1
    if ((player1_pid = fork()) == 0) {
        int fd = open("player1_guess.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        player1_behavior(fd);
        close(fd);
        exit(0);
    }

    // Fork to create Player 2
    if ((player2_pid = fork()) == 0) {
        int fd = open("player2_guess.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
        player2_behavior(fd);
        close(fd);
        exit(0);
    }

    // Referee handles the game
    referee();

    // Wait for both children to terminate
    wait(NULL);
    wait(NULL);

    return 0;
}
