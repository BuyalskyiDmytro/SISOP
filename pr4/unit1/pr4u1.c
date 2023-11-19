#include <stdio.h>
#include <stdlib.h>

int main() {
    char var_name[256]; // Рядок для зберігання імені змінної оточення.
    
    // Попросити користувача ввести ім'я змінної оточення.
    printf("Введіть ім'я змінної оточення: ");
    scanf("%255s", var_name); // Зчитуємо не більше 255 символів.

    char *env_var_value = getenv(var_name);

    if (env_var_value != NULL) {
        // Якщо змінна оточення знайдена, виводимо її значення.
        printf("Змінна оточення '%s' має значення: %s\n", var_name, env_var_value);
    } else {
        // Якщо змінна не знайдена, виводимо відповідне повідомлення.
        printf("Змінна оточення '%s' не знайдена.\n", var_name);
    }

    // Для виведення повного переліку змінних оточення:
    extern char **environ;
    printf("\nПовний перелік змінних оточення:\n");
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}