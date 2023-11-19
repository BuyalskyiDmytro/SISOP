#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_CATALAN 10
#define NUM_PRIMES 10

// Функція для обчислення чисел Каталана
void calculateCatalanNumbers(long long catalan[]) {
    catalan[0] = 1;
    for (int i = 1; i < NUM_CATALAN; ++i) {
        catalan[i] = 0;
        for (int j = 0; j < i; ++j) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }
}

// Функція для перевірки, чи число є простим
int isPrime(int num) {
    if (num < 2) {
        return 0;  // Непросте число
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0;  // Непросте число
        }
    }
    return 1;  // Просте число
}

// Функція для обчислення перших простих чисел
void calculatePrimes(int primes[]) {
    int count = 0;
    for (int num = 2; count < NUM_PRIMES; ++num) {
        if (isPrime(num)) {
            primes[count++] = num;
        }
    }
}

// Функція, яку викликає перший потік
void *catalanThreadFunction(void *arg) {
    long long *catalan = (long long *)malloc(NUM_CATALAN * sizeof(long long));
    if (catalan == NULL) {
        perror("Error allocating memory");
        pthread_exit(NULL);
    }

    calculateCatalanNumbers(catalan);

    // Повертаємо масив чисел Каталана через аргумент
    pthread_exit((void *)catalan);
}

// Функція, яку викликає другий потік
void *primeThreadFunction(void *arg) {
    int *primes = (int *)malloc(NUM_PRIMES * sizeof(int));
    if (primes == NULL) {
        perror("Error allocating memory");
        pthread_exit(NULL);
    }

    calculatePrimes(primes);

    // Повертаємо масив простих чисел через аргумент
    pthread_exit((void *)primes);
}

int main() {
    pthread_t catalanThread, primeThread;
    void *catalanResult, *primeResult;

    // Створення потоків
    if (pthread_create(&catalanThread, NULL, catalanThreadFunction, NULL) != 0 ||
        pthread_create(&primeThread, NULL, primeThreadFunction, NULL) != 0) {
        perror("Error creating threads");
        return 1;
    }

    // Очікування завершення потоків та отримання результатів
    if (pthread_join(catalanThread, &catalanResult) != 0 ||
        pthread_join(primeThread, &primeResult) != 0) {
        perror("Error joining threads");
        return 1;
    }

    // Виведення результатів
    printf("Catalan Numbers: ");
    for (int i = 0; i < NUM_CATALAN; ++i) {
        printf("%lld ", ((long long *)catalanResult)[i]);
    }
    printf("\n");

    printf("Prime Numbers: ");
    for (int i = 0; i < NUM_PRIMES; ++i) {
        printf("%d ", ((int *)primeResult)[i]);
    }
    printf("\n");

    // Звільнення пам'яті
    free(catalanResult);
    free(primeResult);

    return 0;
}


