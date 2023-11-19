#include <stdio.h>
#include <pwd.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    struct passwd *user_info;
    uid_t user_uid = getuid(); // Отримуємо UID поточного користувача.

    printf("Інформація про користувача за UID %d:\n", user_uid);
    user_info = getpwuid(user_uid);

    if (user_info != NULL) {
        printf("Ім'я користувача: %s\n", user_info->pw_name);
        printf("Повне ім'я користувача: %s\n", user_info->pw_gecos);
        printf("Домашній каталог: %s\n", user_info->pw_dir);
        printf("Шелл: %s\n", user_info->pw_shell);
    } else {
        perror("Помилка отримання інформації за UID");
        return 1;
    }

    // Отримуємо інформацію про користувача "root" за реєстраційним ім'ям.
    printf("\nІнформація про користувача root:\n");
    user_info = getpwnam("root");

    if (user_info != NULL) {
        printf("Ім'я користувача: %s\n", user_info->pw_name);
        printf("Повне ім'я користувача: %s\n", user_info->pw_gecos);
        printf("Домашній каталог: %s\n", user_info->pw_dir);
        printf("Шелл: %s\n", user_info->pw_shell);
    } else {
        perror("Помилка отримання інформації за ім'ям користувача root");
        return 1;
    }

    return 0;
}