/*
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

void handle_sigterm(int sig) {
    printf("Received SIGTERM, terminating child process.\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigterm;
    sigaction(SIGTERM, &sa, NULL);

    // Block SIGINT to prevent child from terminating
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    // Open file and read data
    FILE *file = fopen("angl.dat", "r");
    if (!file) {
        perror("Failed to open angl.dat");
        exit(1);
    }

    float pitch, roll, yaw;
    while (fscanf(file, "%f %f %f", &pitch, &roll, &yaw) == 3) {
        if (roll < -20.0 || roll > 20.0) {
            kill(getppid(), SIGUSR1);  // Send SIGUSR1 to parent
        }
        if (pitch < -20.0 || pitch > 20.0) {
            kill(getppid(), SIGUSR2);  // Send SIGUSR2 to parent
        }
        sleep(1);  // Wait 1 second before next read
    }

    fclose(file);
    return 0;
}
*/
