#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

/*

Name: Kevin Ho
NetID: Kth258
Date: 10/4/2024
Description: So the main idea for this code is to rewrite program 4 potentiallly except with signal ahndlers
and forks.

*/


struct DataPoint {
    // Roll, Pitch, Yaw
    double angle[3];
};

// Parent process signal handlers
void handle_sigchld(int sig) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid > 0) {
        printf("Child process %d terminated\n", pid);
    }

    // Check if there are no more children
    if (pid == -1 && errno == ECHILD) {
        printf("No more children. Parent terminating.\n");
        exit(0);
    }
}

// Sig handler for Ctrl+C
void handle_sigint(int sig) {
    char response;
    printf("Exit: Are you sure (Y/n)? ");
    response = getchar();
    if (response == 'Y' || response == 'y') {
        printf("Parent exiting...\n");
        exit(0);
    }
}

// Sig Handler for Roll Value
void handle_sigusr1(int sig) {
    printf("Warning! Roll outside of bounds\n");
}

// Sig Handler for Pitch Value
void handle_sigusr2(int sig) {
    printf("Warning! Pitch outside of bounds\n");
}

// Child process
void child_process(pid_t parent_pid) {
    // Inital variables needed
    const char* file_path = "angl.dat";
    int input_fd = open(file_path, O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open angl.dat file");
        exit(1);
    }
    struct DataPoint data;
    ssize_t bytesRead;
    struct timespec req = {1, 0};
    int count = 0;

    // Reads through the file
    while ((bytesRead = read(input_fd, &data, sizeof(struct DataPoint))) == sizeof(struct DataPoint)) {
        count++;
        printf("Child: Reading data set %d: Roll: %.8f, Pitch: %.8f, Yaw: %.8f\n", count, data.angle[0], data.angle[1], data.angle[2]);

        // Send SIGUSR1 for roll out of bounds
        if (data.angle[0] < -20 || data.angle[0] > 20) {
            kill(parent_pid, SIGUSR1);
        }

        // Send SIGUSR2 for pitch out of bounds
        if (data.angle[1] < -20 || data.angle[1] > 20) {
            kill(parent_pid, SIGUSR2);
        }

        // Wait for 1 second between reads
        nanosleep(&req, NULL);
        printf("\n");
    }

    if (bytesRead < 0) {
        perror("Error reading from angl.dat");
    }

    // Closes out the file can child process
    close(input_fd);
    printf("Child process finished reading from file.\n");
    exit(0);
}

// Parent process function
void parent_process() {
    while (1) {
        pause();
    }
}

// Main function
int main() {
    pid_t child_pid;
    struct sigaction sa;

    // Set up SIGCHLD handler (clean up child processes)
    sa.sa_handler = handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    // Set up SIGINT handler (parent termination prompt)
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    // Set up SIGUSR1 handler (roll out of bounds)
    sa.sa_handler = handle_sigusr1;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    // Set up SIGUSR2 handler (pitch out of bounds)
    sa.sa_handler = handle_sigusr2;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR2, &sa, NULL);

    // Fork a child process
    child_pid = fork();

    // Fork Error
    if (child_pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);

    // Child Process
    } else if (child_pid == 0) {
        // Child process code
        printf("Child process started with PID: %d\n", getpid());
        child_process(getppid());

    // Parent Process
    } else {
        // Parent process code
        printf("Parent process started with child PID: %d\n", child_pid);
        parent_process();
    }

    return 0;
}
