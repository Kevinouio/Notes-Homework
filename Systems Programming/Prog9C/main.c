#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

/*
Name: Kevin Ho
NetID: Kth258
Date: 10/20/2024
Description: This program implements the high-low game using threads for Player 1 and Player 2,
and the referee handles the game logic. Threads communicate using condition variables and mutexes.
*/

// Global variables and synchronization primitives
int player1_guess = -1, player2_guess = -1;
int rdy[2] = {0, 0};  // rdy[0] for Player 1, rdy[1] for Player 2
int cmp[2] = {0, 0};  // cmp[0] for Player 1 comparison, cmp[1] for Player 2 comparison
int game_target;
int player1_score = 0, player2_score = 0;
int p1_cor = 0, p2_cor = 0;

// Separate mutexes and condition variables for each player
pthread_mutex_t mtx[2] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};
pthread_cond_t cnd[2] = {PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};
pthread_mutex_t referee_mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t referee_cond = PTHREAD_COND_INITIALIZER;

// Function to generate a random number within a range
int generate_random(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

// Player 1 behavior (average-based strategy)
void* player1_behavior(void* arg) {
    int p1min = 0, p1max = 101;

    while (1) {
        pthread_mutex_lock(&mtx[0]);

        // Player 1 signals that it is ready
        rdy[0] = 1;
        pthread_cond_signal(&referee_cond);
        pthread_cond_wait(&cnd[0], &mtx[0]); // Wait until referee signals

        // Player 1 guesses the average of the bounds
        player1_guess = (p1min + p1max) / 2;
        printf("Player 1 guessed: %d\n", player1_guess);

        // Adjust bounds based on feedback
        if (player1_guess < game_target) {
            p1min = player1_guess + 1;
        } else if (player1_guess > game_target) {
            p1max = player1_guess - 1;
        }
        else {
            p1_cor = 1;
        }

        if (p1_cor) {
            p1min = 0;
            p1max = 101;
            usleep(1000000);
            p1_cor = 0;
        }
        else if (p2_cor) {
            p1min = 0;
            p1max = 101;
            usleep(500000);
            p2_cor = 0;
        }
        pthread_mutex_unlock(&mtx[0]);

        // Simulate some delay before the next guess
        usleep(500000);
    }

    return NULL;
}

void* player2_behavior(void* arg) {
    int p2min = 0, p2max = 101;

    // Seed the random number generator for Thread 2
    srand(time(NULL) ^ (unsigned long)pthread_self());

    while (1) {
        pthread_mutex_lock(&mtx[1]);

        // Player 2 signals that it is ready
        rdy[1] = 1;
        pthread_cond_signal(&referee_cond);
        pthread_cond_wait(&cnd[1], &mtx[1]); // Wait until referee signals

        // Player 2 guesses a random number within the bounds
        if (p2min > p2max) {
            p2min = 0;
            p2max = 101;
        }
        player2_guess = generate_random(p2min, p2max);

        printf("Player 2 guessed: %d\n", player2_guess);

        // Adjust bounds based on feedback
        if (player2_guess < game_target) {
            p2min = player2_guess + 1;
        } else if (player2_guess > game_target) {
            p2max = player2_guess - 1;
        }
        else{
            p2_cor = 1;
        }

        if (p2_cor) {
            p2min = 0;
            p2max = 101;
            usleep(1000000);
            p1_cor = 0;
        }
        else if (p1_cor) {
            p2min = 0;
            p2max = 101;
            usleep(500000);
            p2_cor = 0;
        }
        pthread_mutex_unlock(&mtx[1]);

        // Simulate some delay before the next guess
        usleep(500000);
    }

    return NULL;
}

// Referee function
void referee() {
    srand(time(NULL));  // Seed the random number generator

    for (int game = 1; game <= 10; game++) {
        printf("Starting game %d\n", game);

        pthread_mutex_lock(&referee_mtx);

        // Generate the target number
        game_target = generate_random(1, 100);
        printf("Referee chose target: %d\n", game_target);

        // Wait for both players to be ready
        while (rdy[0] == 0 || rdy[1] == 0) {
            pthread_cond_wait(&referee_cond, &referee_mtx);
        }

        // Reset the ready flags for the next round
        rdy[0] = rdy[1] = 0;

        pthread_mutex_unlock(&referee_mtx);

        while (1) {
            // Signal players to make their guesses
            pthread_mutex_lock(&mtx[0]);
            pthread_cond_signal(&cnd[0]);
            pthread_mutex_unlock(&mtx[0]);

            pthread_mutex_lock(&mtx[1]);
            pthread_cond_signal(&cnd[1]);
            pthread_mutex_unlock(&mtx[1]);

            // Simulate waiting for both players to guess
            usleep(500000);

            // Check Player 1's guess
            if (player1_guess == game_target) {
                player1_score++;
                printf("Player 1 guessed correctly!\n");
                break;
            }

            // Check Player 2's guess
            if (player2_guess == game_target) {
                player2_score++;
                printf("Player 2 guessed correctly!\n");
                break;
            }
        }

        // Reset guesses for the next game
        player1_guess = player2_guess = -1;

    }

    // Print final scores
    printf("Final Scores: Player 1: %d, Player 2: %d\n", player1_score, player2_score);
}

int main() {
    pthread_t player1_thread, player2_thread;

    // Create threads for Player 1 and Player 2
    pthread_create(&player1_thread, NULL, player1_behavior, NULL);
    pthread_create(&player2_thread, NULL, player2_behavior, NULL);

    // Referee handles the game
    referee();

    // Wait for both threads to finish (they won't in this implementation, but this is standard)
    pthread_join(player1_thread, NULL);
    pthread_join(player2_thread, NULL);

    return 0;
}



void wait_for_signal() {
    // Lock the mutex before checking the condition
    pthread_mutex_lock(&mtx[0]);

    // Wait until rdy[0] becomes 1 (condition met)
    while (rdy[0] == 0) {
        pthread_cond_wait(&cnd[0], &mtx[0]);  // Wait for the condition variable to be signaled
    }

    // rdy[0] is now 1, proceed with the rest of the code

    // Unlock the mutex when done
    pthread_mutex_unlock(&mtx[0]);
}
