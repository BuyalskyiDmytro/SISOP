#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int *data;

void reader_handle_signal(int sig) {
    if (sig == SIGUSR2) {
        printf(" Process 2: Received sum: %d\n", data[0]);

        if (shmdt(data) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <buffer_size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int buffer_size = atoi(argv[1]);

    key_t key = ftok(".", 's');
    int shmid = shmget(key, (buffer_size + 1) * sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    data = (int *)shmat(shmid, NULL, 0);
    if (data == (int *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    data[0] = buffer_size;

    signal(SIGUSR2, reader_handle_signal);

    pause();

    return 0;
}