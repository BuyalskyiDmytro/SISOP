#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 1024  
#define SEM_KEY 1234   

int *shared_memory;
int sem_id;

union semun {
    int val;
    struct semid_ds *buf;
   unsigned short *array;
};

void signal_handler(int signo) {
    if (signo == SIGUSR1) {
       struct sembuf semaphore = {0, -1, 0};  
        semop(sem_id, &semaphore, 1);

       int sum = 0;
        int count = shared_memory[0];  
        for (int i = 1; i <= count; ++i) {
            sum += shared_memory[i];
        }

        shared_memory[0] = sum;  
        semaphore.sem_op = 1;  
        semop(sem_id, &semaphore, 1);
    } else if (signo == SIGUSR2) {
        shmdt(shared_memory);
        shmctl(shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666), IPC_RMID, NULL);
        semctl(sem_id, 0, IPC_RMID);
        exit(0);
    }
}

int main() {
     sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    union semun init_sem;
    init_sem.val = 1;  
    if (semctl(sem_id, 0, SETVAL, init_sem) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    key_t key = ftok("/tmp", 'S');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    shared_memory = (int *)shmat(shmid, NULL, 0);

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        int count;
        printf("¬вед≥ть к≥льк≥сть чисел:\n-1 щоб вийти ");
        scanf("%d", &count);

        if (count == -1) {
            kill(getpid() + 1, SIGUSR2);
            break;
        }

        shared_memory[0] = count;

            for (int i = 1; i <= count; ++i) {
            printf("¬вед≥ть число %d: ", i);
            scanf("%d", &shared_memory[i]);
        }

        kill(getpid() + 1, SIGUSR1);

        pause();

        printf("—уму в≥д 2 процесу: %d\n", shared_memory[0]);
    }

    wait(NULL);

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}