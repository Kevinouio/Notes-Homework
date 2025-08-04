#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define NUM_VALUES 60
#define FILENAME_SIZE 12
#define BUFFER_SIZE 32  // Increased buffer size for reading

int main() {
    pid_t pid;
    int status;

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: execute myRand program
        execl("./myRand", "./myRand", (char *) NULL);
        perror("exec failed");
        exit(1);
    } else {
        // Parent process: wait for the child to finish
        wait(&status);

        // Get the exit status from the child process
        int randomX = WEXITSTATUS(status);

        // Create the filename dataX.dat
        char filename[FILENAME_SIZE];
        snprintf(filename, FILENAME_SIZE, "data%d.dat", randomX);

        // Open the generated file
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Error opening the data file");
            exit(1);
        }

        // Read the 60 values from the file and compute the average
        int value;
        double total = 0;
        char buffer[BUFFER_SIZE];
        ssize_t bytesRead;
        int numbers[NUM_VALUES];
        int i = 0;  // Number of values read

        printf("Reading values from file %s:\n", filename);

        // Read from the file
        while (i < NUM_VALUES && (bytesRead = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
            buffer[bytesRead] = '\0'; // Null-terminate the buffer

            // Tokenize the buffer to extract integers
            char *token = strtok(buffer, "\n");
            while (token != NULL && i < NUM_VALUES) {
                if (sscanf(token, "%d", &numbers[i]) == 1) {
                    i++;
                }
                token = strtok(NULL, "\n"); // Move to the next token
            }
        }

        for (int j = 0; j < NUM_VALUES; j++) {
            total += numbers[j];
        }
        double average = (total/NUM_VALUES);
        printf("Average Value: %f", average);



        // Close the file
        close(fd);
        // Unlink (delete) the file
        if (unlink(filename) == -1) {
            perror("Error deleting the file");
            exit(1);
        }

    }

    return 0;
}
