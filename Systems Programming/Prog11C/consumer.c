#include <stdio.h>
#include <stdlib.h>
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

    // Open the FIFO for reading
    fifo_fd = open(FIFO_NAME, O_RDONLY);
    if (fifo_fd == -1) {
        perror("Failed to open FIFO for reading");
        exit(1);
    }

    while (1) {
        // Read from FIFO
        ssize_t bytesRead = read(fifo_fd, buffer, BUFFER_SIZE);
        if (bytesRead > 0) {
            printf("consumer: %s\n", buffer);
        } else if (bytesRead == -1) {
            perror("Failed to read from FIFO");
            exit(1);
        }
    }

    close(fifo_fd);
    return 0;
}
