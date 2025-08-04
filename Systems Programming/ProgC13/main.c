/* Write a multiple concurrent process program that does the following
   1. Displays "ascii modern art" composed of a series of
      randomly generated blocks of 2 or more repeating characters

   The program should perform this task in the following way:
   1. Create a semaphore set of size 2 -- use IPC_PRIVATE as your key
      a. Initialize the semaphore representing the child to available
      b. Initialize the semaphore representing the parent to in use
   2. Create a segment of shared memory -- use IPC_PRIVATE as your key

   3. Create a child process that:
      a. Attaches the segment of shared memory
      b. Seeds the random number generator
      c. Reserves the child semaphore
      d. Generates and stores the total number of blocks to generate.
         This should be between 10 and 20
      c. For each block, generate and store the following values:
         1. The length of the block (i.e. the number of characters to display)
            This should be between 2 and 10
         2. The character that comprises the block.
            This should be between 'a' and 'z'
      d. Release the parent semaphore
      e. Reserve the child semaphore
      f. Detach the shared memory segment
      g. Release the parent semaphore

   4. Create a parent process that:
      a. Attaches the segment of shared memory
      b. Seeds the random number generator
      c. Reserve the parent semaphore
      d. Generate a random width for the ASCII art.
         This should be between 10 and 15
      e. Using the data stored in the shared memory segment, output an image
         Use the following tips:
         1. One value stored in the segment should represent the number
            of (length, character) pairings. For each (length, character)
            pairing, you should output length instances of the given
            character. This means if the pairing was (3, 'b'), you would
            output "bbb".
         2. The random image has basically been encoded use run-length
            encoding (RLE); RLE doesn't including the location of new lines.
            The location of new lines is determined by the random width
            generated in step d. Each time you output width total characters,
            output a new line.
      f. Release the child semaphore
      g. Reserve the parent semaphore
      h. Detach the shared memory segment

   5. Delete the semaphore
   6. Delete the shared memory

   -- You can use/should use the binary semaphore protocol introduced in class
 */




/* Problem 3 -- List the inlcude files you need for this program. */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>
#include "binary_sem.h"

// so semun is already defined in macOS sooooo
#include "semun.h"


/* Problem 4 -- remember to declare a structure that represents the data
   stored in the shared memory */

typedef struct {
    int total_blocks;
    int lengths[20];      // Maximum 20 blocks
    char characters[20];  // Characters for each block
} SharedData;

/* Problem 5 -- create a function to handle the code for the child.
   Be certain to pass this function the id values for both the semaphore
   and the shared memory segment */
void child_process(int sem_id, int shm_id) {
    SharedData *data;

    // Attach shared memory
    data = (SharedData *)shmat(shm_id, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL) + getpid()); // Seed RNG

    reserveSem(sem_id, 0); // Reserve the child semaphore

    // Generate block data
    data->total_blocks = 10 + rand() % 11; // Between 10 and 20 blocks
    for (int i = 0; i < data->total_blocks; i++) {
        data->lengths[i] = 2 + rand() % 9;      // Length between 2 and 10
        data->characters[i] = 'a' + rand() % 26; // Random character 'a'-'z'
    }

    releaseSem(sem_id, 1); // Release parent semaphore
    reserveSem(sem_id, 0); // Reserve the child semaphore

    // Detach shared memory
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    releaseSem(sem_id, 1); // Release parent semaphore
    exit(EXIT_SUCCESS);
}

/* Problem 6 -- create a function to handle the code for the parent.
   Be certain to pass this function the id values for both the semaphore
   and the shared memory segment */
void parent_process(int sem_id, int shm_id) {
    SharedData *data;

    // Attach shared memory
    data = (SharedData *)shmat(shm_id, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL)); // Seed RNG

    reserveSem(sem_id, 1); // Reserve the parent semaphore

    int width = 10 + rand() % 6; // Random width between 10 and 15

    printf("ASCII Modern Art (Width: %d):\n", width);
    int current_width = 0;
    for (int i = 0; i < data->total_blocks; i++) {
        for (int j = 0; j < data->lengths[i]; j++) {
            putchar(data->characters[i]);
            current_width++;
            if (current_width >= width) {
                putchar('\n');
                current_width = 0;
            }
        }
    }
    if (current_width > 0) {
        putchar('\n'); // Print leftover characters
    }

    releaseSem(sem_id, 0); // Release child semaphore
    reserveSem(sem_id, 1); // Reserve the parent semaphore

    // Detach shared memory
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
}


/* Problem 7 -- implement function main */




int main() {
    int sem_id, shm_id;

    // Create semaphore set
    sem_id = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0600);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores: Child semaphore available, Parent semaphore in use
    if (initSemAvailable(sem_id, 0) == -1 || initSemInUse(sem_id, 1) == -1) {
        perror("Initializing semaphores");
        semctl(sem_id, 0, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    }

    // Create shared memory
    shm_id = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1) {
        perror("shmget");
        semctl(sem_id, 0, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    }

    // Fork to create child process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        semctl(sem_id, 0, IPC_RMID, 0);
        shmctl(shm_id, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        child_process(sem_id, shm_id);
    } else {
        parent_process(sem_id, shm_id);

        // Wait for child process to finish
        wait(NULL);

        // Cleanup
        if (semctl(sem_id, 0, IPC_RMID, 0) == -1) {
            perror("semctl - IPC_RMID");
        }
        if (shmctl(shm_id, IPC_RMID, 0) == -1) {
            perror("shmctl - IPC_RMID");
        }
    }

    return 0;
}




