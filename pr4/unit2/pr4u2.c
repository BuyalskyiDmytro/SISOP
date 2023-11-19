#include <stdio.h>
#include <stdlib.h>

int main() {
    char var_name[100];
    char var_value[100];

    // Введення ім'я змінної
    printf("Введіть ім'я змінної оточення: ");
    fgets(var_name, sizeof(var_name), stdin);
    var_name[strcspn(var_name, "\n")] = '\0';  // Видалення символу нового рядка

    // Введення значення змінної
    printf("Введіть значення для змінної %s: ", var_name);
    fgets(var_value, sizeof(var_value), stdin);
    var_value[strcspn(var_value, "\n")] = '\0';  // Видалення символу нового рядка

    // Встановлення значення змінної оточення
    if (setenv(var_name, var_value, 1) == 0) {
        printf("Змінну оточення %s було успішно встановлено на %s.\n", var_name, var_value);
    } else {
        perror("Помилка встановлення змінної оточення");
        return 1;
    }

    // Виведення усіх змінних оточення
    extern char **environ;
    printf("Усі змінні оточення:\n");
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}
