#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define NUM_VALUES 60
#define MAX_RAND 100
#define FILENAME_SIZE 12
#define BUFFER_SIZE 10  // Buffer size for storing string versions of numbers

int main() {
    int fd;
    int randomValue;
    char filename[FILENAME_SIZE];
    char buffer[BUFFER_SIZE];
    int randomX;
    ssize_t writtenBytes;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate a random number between 0 and 255
    randomX = rand() % 256;

    // Create the filename dataX.dat
    snprintf(filename, FILENAME_SIZE, "data%d.dat", randomX);

    // Open the file using file descriptors
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening the file");
        return 1; // Exit if file opening fails
    }

    double count = 0;

    // Debugging: Print the file being created
    printf("Creating file: %s\n", filename);

    // Write 60 random values between 0 and 100 to the file
    for (int i = 0; i < NUM_VALUES; i++) {
        randomValue = rand() % (MAX_RAND + 1); // Random number between 0 and 100
        count += randomValue;

        // Convert the integer to a string (with newline) to write it to the file
        snprintf(buffer, BUFFER_SIZE, "%d\n", randomValue);

        // Write the value to the file
        writtenBytes = write(fd, buffer, strlen(buffer));
        if (writtenBytes == -1) {
            perror("Error writing to the file");
            close(fd);
            return 1; // Exit if writing fails
        }

        // Debugging: Print each value written
        printf("Written Value %d: %d\n", i + 1, randomValue);
    }


    // Close the file
    if (close(fd) == -1) {
        perror("Error closing the file");
        return 1; // Exit if file closing fails
    }

    // Exit with the random number X as the status
    exit(randomX);
}
