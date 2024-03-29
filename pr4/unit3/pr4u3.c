#include <stdio.h>
#include <stdlib.h>

int main() {
    char var_name[256]; // Рядок для зберігання імені змінної оточення.
    
    // Попросити користувача ввести ім'я змінної оточення.
    printf("Введіть ім'я змінної оточення, яку ви бажаєте видалити: ");
    scanf("%255s", var_name); // Зчитуємо не більше 255 символів (включаючи завершуючий нульовий символ).

    if (unsetenv(var_name) == 0) {
        // Змінна оточення була видалена успішно.
        printf("Змінна оточення '%s' була видалена.\n", var_name);
    } else {
        perror("Помилка видалення змінної оточення");
        return 1;
    }

    // Виведення поточного оточення.
    extern char **environ;
    printf("\nПоточне оточення:\n");
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    return 0;
}