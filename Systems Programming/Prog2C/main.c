#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // For open(), O_RDONLY, O_WRONLY, etc.
#include <unistd.h>     // For read(), write(), close()
#include <stdint.h>     // For fixed-width integers like uint8_t
#include <string.h>     // For memset

// Define a structure for holding decompressed data points
struct DataPoint {
    double acceleration[3];  // X, Y, Z for acceleration
    double velocity[3];     // X, Y, Z for velocity
    double angle[3];  // X, Y, Z for angle
};

struct DataPoint decompressPacket(const int8_t packet[20]) {
    struct DataPoint data;

    // Combine the bytes to form signed 16-bit integers
    for (int i = 0; i < 3; i++) {
        // Combine two 8-bit integers into a signed 16-bit integer for acceleration
        int16_t accelValue = (int16_t)((packet[(2 * i) + 2] & 0xFF) | (packet[(2 * i) + 3] << 8));
        data.acceleration[i] = accelValue / 32768.0 * 16;

        // Combine two 8-bit integers into a signed 16-bit integer for velocity
        int16_t velocityValue = (int16_t)((packet[(2 * i) + 8] & 0xFF) | (packet[(2 * i) + 9] << 8));
        data.velocity[i] = velocityValue / 32768.0 * 2000;

        // Combine two 8-bit integers into a signed 16-bit integer for angle
        int16_t angleValue = (int16_t)((packet[(2 * i) + 14] & 0xFF) | (packet[(2 * i) + 15] << 8));
        data.angle[i] = angleValue / 32768.0 * 180;
    }

    return data;
}

int main() {
    const char* inputFileName = "raw.dat";  // Input binary file
    const char* outputFileName = "data.dat";  // Output binary file
    int count = 0;

    // Open the input file using file descriptors
    int input_fd = open(inputFileName, O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input file");
        return 1;
    }

    // Open the output file using file descriptors (create if it doesn't exist)
    int output_fd = open(outputFileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Failed to open output file");
        close(input_fd);
        return 1;
    }

    int8_t packet[20];  // Buffer for reading the 20-byte data packet
    struct DataPoint data;  // Struct to hold decompressed data

    ssize_t bytesRead;
    while ((bytesRead = read(input_fd, packet, sizeof(packet))) == sizeof(packet)) {
        count++;
        printf("Packet %d\n", count);

        // Decompress the packet into the DataPoint struct
        data = decompressPacket(packet);

        // Print decompressed data to the console (example for acceleration data)
        printf("Acceleration: Ax = %.8f Ay = %.8f Az = %.8f\n",
               data.acceleration[0], data.acceleration[1], data.acceleration[2]);
        printf("Angular Velocity: Wx = %.8f Wy = %.8f Wz = %.8f\n",
               data.velocity[0], data.velocity[1], data.velocity[2]);
        printf("Angle: Roll = %.8f Pitch = %.8f Yaw = %.8f\n\n",
               data.angle[0], data.angle[1], data.angle[2]);

        // Write decompressed data to the output binary file
        ssize_t bytesWritten = write(output_fd, &data, sizeof(struct DataPoint));
        if (bytesWritten != sizeof(struct DataPoint)) {
            perror("Failed to write to output file");
            close(input_fd);
            close(output_fd);
            return 1;
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from input file");
    }

    // Close file descriptors
    close(input_fd);
    close(output_fd);

    return 0;
}
