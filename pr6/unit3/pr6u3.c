#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_REPETITIONS 5
#define NUM_RANDOM_NUMBERS 5
#define RANDOM_NUMBER_THRESHOLD 50

// Структура для передачі параметрів у потокову функцію
struct ThreadParams {
    const char *name;
    int num;
};

// Потокова функція для виведення тексту
void *textThreadFunction(void *arg) {
    struct ThreadParams *params = (struct ThreadParams *)arg;

    for (int i = 1; i <= params->num; ++i) {
        printf("Child Thread. Iteration: %d\n", i);
        sleep(rand() % 3); // "Засипання" на випадковий час від 0 до 2 секунд
    }

    pthread_exit(NULL);
}

// Потокова функція для генерації та виведення псевдовипадкових чисел
void *randomThreadFunction(void *arg) {
    struct ThreadParams *params = (struct ThreadParams *)arg;

    for (int i = 1; i <= params->num; ++i) {
        int randomNumber = rand() % 100; // Генерація псевдовипадкового числа від 0 до 99
        printf("Child Thread. Random Number: %d\n", randomNumber);

        if (randomNumber < RANDOM_NUMBER_THRESHOLD) {
            printf("Child Thread. Random Number is less than %d. Exiting...\n", RANDOM_NUMBER_THRESHOLD);
            pthread_exit(NULL);
        }

        sleep(rand() % 3); // "Засипання" на випадковий час від 0 до 2 секунд
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t textThread, randomThread;

    struct ThreadParams textParams = {.name = "Text", .num = NUM_REPETITIONS};
    struct ThreadParams randomParams = {.name = "Random", .num = NUM_RANDOM_NUMBERS};

    // Створення дочірнього потоку для виведення тексту
    if (pthread_create(&textThread, NULL, textThreadFunction, (void *)&textParams) != 0) {
        perror("Error creating text thread");
        return 1;
    }

    // Створення дочірнього потоку для генерації та виведення псевдовипадкових чисел
    if (pthread_create(&randomThread, NULL, randomThreadFunction, (void *)&randomParams) != 0) {
        perror("Error creating random thread");
        return 1;
    }

    // Очікування завершення обох дочірніх потоків
    if (pthread_join(textThread, NULL) != 0) {
        perror("Error joining text thread");
        return 1;
    }

    if (pthread_join(randomThread, NULL) != 0) {
        perror("Error joining random thread");
        return 1;
    }

    printf("Main Thread. All child threads have finished.\n");

    return 0;
}