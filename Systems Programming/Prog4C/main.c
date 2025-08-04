#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

/*

Name: Kevin Ho
NetID: Kth258
Date: 9/17/2024
Description: The main point of this program is to simply just read the values and determine of the values
are in range of -20 to 20 and to also read the data at intervals per second.

*/

struct DataPoint {
    double angle[3];
};


int main() {
    // Path to the "accl.dat" file
    const char* acclPath = "angl.dat";

    // Open the file for reading
    int input_fd = open(acclPath, O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open accl.dat file");
        return 1;
    }

    // Variables to hold the read data
    struct DataPoint data;
    ssize_t bytesRead;
    int count = 0 ;
    struct timespec req = {1, 0};
    char* outside = "Outside Range";
    char* inside = "Inside Range";
    const char* words[] = {"Roll", "Pitch","Yaw"};

    // Read the contents of accl.dat and print to console
    printf("Contents of angl.dat:\n");
    while ((bytesRead = read(input_fd, &data, sizeof(struct DataPoint))) == sizeof(struct DataPoint)) {
        count++;
        printf("%d: ",count);

        // Write binary angle data to angl.dat
        printf("Roll: %.8f, Pitch: %.8f, Yaw: %.8f\n", data.angle[0], data.angle[1], data.angle[2]);
        for (int i = 0; i < 3; i++) {
            if ((data.angle[i] < -20) || (data.angle[i] > 20)) {
                printf("%s: %s  ",words[i], outside);
            }
            else{
                printf("%s: %s  ",words[i], inside);
            }
        }
        printf("\n");

        nanosleep(&req, NULL);

    }

    if (bytesRead < 0) {
        perror("Error reading from accl.dat");
    }

    // Close the file descriptor
    close(input_fd);

    return 0;
}
