#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // Якщо команди передані через командний рядок, виконуємо їх послідовно
        for (int i = 1; i < argc; i++) {
            system(argv[i]);
        }
    } else {
        // Якщо команди не передані через командний рядок, просимо користувача ввести їх у консолі
        char command[256];
        while (1) {
            printf("Введіть команду (або 'exit' для виходу): ");
            fgets(command, sizeof(command), stdin);

            // Перевірка на виход
            if (strcmp(command, "exit\n") == 0) {
                break;
            }

            // Видалення символу нового рядка
            size_t len = strlen(command);
            if (len > 0 && command[len - 1] == '\n') {
                command[len - 1] = '\0';
            }

            // Виконуємо команду
            system(command);
        }
    }

    return 0;
}