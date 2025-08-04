#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024


/*

Name: Kevin Ho
NetID: Kth258
Date: 10/29/2024
Description: main thing is just sending information between the parent and child through a pipe

*/

int main() {
    int pipefd[2];  // Array to hold the pipe file descriptors: pipefd[0] for reading, pipefd[1] for writing
    pid_t pid;
    char buffer[BUFFER_SIZE];

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process to create a child
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent process
        close(pipefd[0]);  // Close unused read end

        // Get input from the user
        printf("Please enter text at the parent: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Write the input to the pipe
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);  // Close the write end of the pipe

        // Wait for the child process to complete
        wait(NULL);
    }
    else {  // Child process
        close(pipefd[1]);  // Close unused write end

        // Read from the pipe
        read(pipefd[0], buffer, BUFFER_SIZE);
        close(pipefd[0]);  // Close the read end of the pipe

        // Print the data received from the parent
        printf("child: %s", buffer);
    }

    return 0;
}
