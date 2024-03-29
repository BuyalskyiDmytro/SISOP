#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <errno.h>
int main(int argc, char *argv[]){
    int shmid;
    key_t key;
    int *shared_memory;
    int n, i, sum = 0;
    sem_t *semaphore;
    if(argc < 2){
        printf("������ ������������� ������ ���'��:\n");
        return -1;
    }
    sscanf(argv[1], "%d", &shmid);
    shared_memory = (int *)shmat(shmid, NULL, 0);
    if(shared_memory == (int *)(-1)){
        perror("�� ������� �������� ������ ������");
        return -1;
    }
    semaphore = sem_open("/my_semaphore", 0);
    if(semaphore == SEM_FAILED){
        perror("�� ������� ������� �������");
        return -1;
    }
    sem_wait(semaphore);
    printf("������ ������� ��������, �� ������� ����������: ");
    scanf("%d", &n);
    printf("�������� � ������ ������ ���'��:\n");
    for(i = 0; i < n; i++){
        printf("%d ", shared_memory[i]);
        sum += shared_memory[i];
    }
    printf("\nSum of elements: %d\n", sum);
    shmdt((void *)shared_memory);
    sem_close(semaphore);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
