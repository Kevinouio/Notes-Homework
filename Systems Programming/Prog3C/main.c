#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

/*

Name: Kevin Ho
NetID: Kth258
Date: 9/9/2024
Description: The point of the program is to read data from a binary "data.dat" file and write the acceleration, velocity, and angle
data to separate files in the binary format.

*/

// Define the structure to match the DataPoint structure
struct DataPoint {
    double acceleration[3];  // X, Y, Z for acceleration
    double velocity[3];      // X, Y, Z for velocity
    double angle[3];         // X, Y, Z for angle
};

int main() {
    // Step 1: Create a directory named "values"
    const char* dirName = "values";
    if (mkdir(dirName, 0755) == -1) {
        if (errno == EEXIST) {
            printf("Directory '%s' already exists.\n", dirName);
        } else {
            perror("Error creating directory");
            return 1;
        }
    } else {
        printf("Directory '%s' created successfully.\n", dirName);
    }

    // File paths
    char acclPath[256], rotaPath[256], anglPath[256];
    snprintf(acclPath, sizeof(acclPath), "%s/accl.dat", dirName);
    snprintf(rotaPath, sizeof(rotaPath), "%s/rota.dat", dirName);
    snprintf(anglPath, sizeof(anglPath), "%s/angl.dat", dirName);

    // Creating files "accl.dat", "rota.dat", "angl.dat" in the "values" directory
    int fd_accl = open(acclPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd_rota = open(rotaPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int fd_angl = open(anglPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd_accl < 0 || fd_rota < 0 || fd_angl < 0) {
        perror("Failed to create files");
        return 1;
    }

    // Step 3: Open the "data.dat" file
    const char* inputFileName = "data.dat";
    int input_fd = open(inputFileName, O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input file");
        return 1;
    }

    struct DataPoint data;
    ssize_t bytesRead;

    // Step 4: Read X, Y, Z and store them into their respective file
    while ((bytesRead = read(input_fd, &data, sizeof(struct DataPoint))) == sizeof(struct DataPoint)) {
        // Write binary acceleration data to accl.dat
        write(fd_accl, data.acceleration, sizeof(data.acceleration));

        // Write binary angle data to angl.dat
        write(fd_angl, data.angle, sizeof(data.angle));

        // Write binary velocity data to rota.dat
        write(fd_rota, data.velocity, sizeof(data.velocity));
    }

    if (bytesRead < 0) {
        perror("Error reading from input file");
    }

    // Close file descriptors
    close(input_fd);
    close(fd_accl);
    close(fd_rota);
    close(fd_angl);

    return 0;
}
