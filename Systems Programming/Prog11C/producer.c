#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

/*

Name: Kevin Ho
NetID: Kth258
Date: 11/5/2024
Description: Main point of this program is to basically use a FIFO and understand how to code it.
*/

int main() {
    char buffer[BUFFER_SIZE];
    int fifo_fd;

    // Open the FIFO for writing
    fifo_fd = open(FIFO_NAME, O_WRONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for writing");
        exit(1);
    }

    printf("Please enter text at the producer:\n");

    while (1) {
        printf("producer: ");
        if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
            // Remove newline character if it exists
            buffer[strcspn(buffer, "\n")] = '\0';

            // Write to FIFO
            if (write(fifo_fd, buffer, strlen(buffer) + 1) == -1) {
                perror("Failed to write to FIFO");
                exit(1);
            }
        }
    }

    close(fifo_fd);
    return 0;
}
