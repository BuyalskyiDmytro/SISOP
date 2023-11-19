#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 10

// Функція, яку викликає новий потік
void *childThreadFunction(void *arg) {
    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3); // "Засипання" на випадковий час від 0 до 2 секунд
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t childThread;

    // Створення нового потоку
    if (pthread_create(&childThread, NULL, childThreadFunction, NULL) != 0) {
        perror("Error creating thread");
        return 1;
    }

    // Виконання дій у батьківському потоці
    for (int i = 1; i <= NUM_ITERATIONS; ++i) {
        printf("Main Thread. Iteration: %d\n", i);
        sleep(rand() % 3); // "Засипання" на випадковий час від 0 до 2 секунд
    }

    // Очікування завершення нового потоку
    if (pthread_join(childThread, NULL) != 0) {
        perror("Error joining thread");
        return 1;
    }

    return 0;
}
