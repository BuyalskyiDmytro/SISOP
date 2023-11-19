#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

#define DEFAULT_BUFFER_SIZE 127

int main(int argc, char* argv[]) {
    char* username;
    int bufferSize = DEFAULT_BUFFER_SIZE;

    printf("Введіть ім'я користувача: ");
    scanf("%ms", &username);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Help information...\n");
            return 0;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) {
            if (i + 1 < argc) {
                bufferSize = atoi(argv[i + 1]);
                i++;
            } else {
                printf("No buffer size provided!\n");
                return 1;
            }
        }
    }

    char* command = malloc(bufferSize * sizeof(char));

    while (1) {
        printf("[%s]$", username);
        fgets(command, bufferSize, stdin);
        command[strlen(command) - 1] = '\0';

        if (strcmp(command, "help") == 0 || strcmp(command, "-h") == 0 || strcmp(command, "--help") == 0) {
            printf("Доступні вбудовані команди:\n");
            printf("help, -h / --help \n");
            printf("buffer, -b /  --buffer встановити розмір буфера\n");
            printf("stop - завершити роботу командного процесору\n");
        } else if (strcmp(command, "buffer") == 0 || strcmp(command, "-b") == 0 || strcmp(command, "--buffer") == 0) {
            printf("Введіть новий розмір буфера: ");
            int newBufferSize;
            scanf("%d", &newBufferSize);
            getchar();
            if (newBufferSize > 0) {
                free(command);
                command = malloc(newBufferSize * sizeof(char));
            } else {
                printf("Недійсний розмір буфера.\n");
            }
        } else if (strcmp(command, "stop") == 0) {
            printf("Wait 3 seconds...\n");
            sleep(3);
            system("clear");
            free(username);
            free(command);
            exit(0);
        } else {
            system(command);
        }
    }

    // Звільнюємо виділену пам'ять для ім'я користувача та команду
    free(username);
    free(command);

    return 0;
}
