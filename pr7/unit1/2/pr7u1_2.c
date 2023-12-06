#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int *data;

void write_handle_signal(int sig) {
    if (sig == SIGUSR1) {
        int sum = 0;
        for (int i = 1; i <= data[0]; ++i) {
            sum += data[i];
        }

        data[0] = sum;

        printf("Process 1: Sum calculated: %d\n", sum);

        kill(getpid() + 1, SIGUSR2);
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

    signal(SIGUSR1, write_handle_signal);

    printf("Enter %d integers:\n", buffer_size);
    for (int i = 1; i <= buffer_size; ++i) {
        scanf("%d", &data[i]);
    }

    kill(getpid() - 1, SIGUSR1);

    pause();

    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}