#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile int handler_count = 0;

void process_handler(int signum) {
    // Затримуємо роботу на 1 секунду
    sleep(1);

    printf("Обробник завершення процесу #%d: Процес завершився\n", handler_count);
    handler_count++;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Використання: %s <кількість_обробників>\n", argv[0]);
        return 1;
    }

    int num_handlers = atoi(argv[1]);

    if (num_handlers <= 0) {
        printf("Кількість обробників повинна бути більшою за 0\n");
        return 1;
    }

    for (int i = 1; i <= num_handlers; i++) {
        // Реєструємо обробник для SIGCHLD (завершення дочірнього процесу)
        if (signal(SIGCHLD, process_handler) == SIG_ERR) {
            perror("Помилка під час реєстрації обробника");
            return 1;
        }
    }

    printf("Очікування завершення процесу...\n");

    // Безкінечний цикл для очікування завершення процесів
    while (1) {
        pause();
    }

    return 0;
}