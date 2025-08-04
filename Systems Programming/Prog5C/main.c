#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/time.h>

#define LENGTH 256

/*

Name: Kevin Ho
NetID: Kth258
Date: 9/25/2024
Description: The point of the program is to created a time quiz with the program prompting a question every 15 seconds for the
user to respond/answer. The program is also used to demonstrate usage of the file descriptors and read,write,open, close.
Also makes use of signal handlers.

*/

volatile sig_atomic_t timed_out = 0; // To track if the timer has expired
int quiz_running = 1; // To control quiz flow

// Signal handler for timer expiration
void timer_handler(int signum) {
    timed_out = 1; // Set the timed_out flag
}

// Function to flush the input buffer after reading input
void flush_input_buffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void start_timer() {
    struct itimerval timer;
    timer.it_value.tv_sec = 15; // 15 seconds for the first timer
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; // No repeated interval
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL); // Start the timer
}

void stop_timer() {
    struct itimerval timer = {0}; // Stop the timer
    setitimer(ITIMER_REAL, &timer, NULL);
}

// Signal handler for SIGINT (Ctrl-C)
void sigint_handler(int signum) {
    char response[3]; // To store the user's response to "Exit (y/N)?"

    // Stop the timer first
    stop_timer();

    // Prompt the user for exit confirmation
    write(STDOUT_FILENO, "\nExit (y/N)? ", 13);

    // Read the user's response
    ssize_t bytes_read = read(STDIN_FILENO, response, sizeof(response) - 1);
    if (bytes_read > 0) {
        response[bytes_read - 1] = '\0'; // Null-terminate the string

        if (response[0] == 'y' || response[0] == 'Y') {
            quiz_running = 0; // Set flag to stop the quiz
        } else {
            write(STDOUT_FILENO, "Resuming quiz...\n", 17);
            flush_input_buffer();
            start_timer(); // Resume the timer if not exiting
        }
    }
}

// Helper function to read a single line from a file descriptor using 'read'
ssize_t read_line(int fd, char *buffer, size_t max_length) {
    ssize_t bytes_read;
    size_t total_read = 0;

    while (total_read < max_length - 1) {
        bytes_read = read(fd, buffer + total_read, 1);  // Read one byte at a time
        if (bytes_read <= 0) {
            break;
        }

        // Stops reading at the new line
        if (buffer[total_read] == '\n') {
            break;
        }

        total_read += bytes_read;
    }

    buffer[total_read] = '\0';
    return total_read;
}

int main() {
    char question[LENGTH];
    char answer[LENGTH];
    char user_input[LENGTH];
    int correct_answers = 0;
    int total_questions = 0;

    // Setup signal handlers
    struct sigaction sa;
    sa.sa_handler = timer_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);

    struct sigaction sa_int;
    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    // Inform the user and ask to proceed
    printf("You are about to begin a timed quiz.\n");
    printf("You have 15 seconds to answer each question.\n");
    printf("You can exit the program anytime by pressing Ctrl-C.\n");
    printf("Do you wish to proceed? (y/N): ");
    printf("\n");

    // Reads the user input for whether they are going to be taking the quiz
    read(STDIN_FILENO, user_input, sizeof(user_input));
    if (user_input[0] != 'y' && user_input[0] != 'Y') {
        printf("Exiting the quiz.\n");
        return 0;
    }

    // Open the questions and answers files
    int q_fd = open("quest.txt", O_RDONLY);
    int a_fd = open("ans.txt", O_RDONLY);

    if (q_fd < 0 || a_fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Read each question and answer line by line
    while (quiz_running && (read_line(q_fd, question, sizeof(question)) > 0) &&
           (read_line(a_fd, answer, sizeof(answer)) > 0)) {
        total_questions++;

        // Remove newline characters from question and answer
        question[strcspn(question, "\n")] = 0;
        answer[strcspn(answer, "\n")] = 0;

        // Display the question and start timer
        printf("\nQuestion: %s\n", question);
        printf("Your answer: ");

        // Start the timer
        timed_out = 0;
        start_timer();

        // Read user input using read
        ssize_t bytes_read = read(STDIN_FILENO, user_input, sizeof(user_input) - 1);
        stop_timer();

        if (bytes_read > 0) {
            user_input[bytes_read - 1] = '\0'; // Null-terminate the string
        }

        // Check for timeout
        if (timed_out) {
            printf("Time has elapsed.\n");
        } else {
            // Compare user's answer to the correct answer
            if (strcmp(user_input, answer) == 0) {
                printf("Correct!\n");
                correct_answers++;
            } else {
                printf("Wrong! The correct answer was: %s\n", answer);
            }
        }
    }

    // Close files
    close(q_fd);
    close(a_fd);

    // Display results
    printf("\nQuiz finished! You answered %d out of %d questions correctly.\n",
           correct_answers, total_questions);

    return 0;
}
