#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Функція для виведення значення змінної оточення або повідомлення, якщо змінної немає.
void getEnvironmentVariable(char *var_name) {
    char *value = getenv(var_name);
    if (value != NULL) {
        printf("Змінна оточення %s = %s\n", var_name, value);
    } else {
        printf("Змінна оточення %s не знайдена\n", var_name);
    }
}

// Функція для встановлення значення змінної оточення та виведення нового значення.
void setEnvironmentVariable(char *var_name, char *new_value) {
    if (setenv(var_name, new_value, 1) == 0) {
        printf("Змінна оточення %s встановлена на %s\n", var_name, new_value);
    } else {
        perror("Помилка встановлення змінної оточення");
    }
}

// Функція для видалення змінної оточення.
void deleteEnvironmentVariable(char *var_name) {
    if (unsetenv(var_name) == 0) {
        printf("Змінна оточення %s видалена\n", var_name);
    } else {
        perror("Помилка видалення змінної оточення");
    }
}

// Функція для очищення всього оточення.
void clearEnvironment() {
    if (clearenv() == 0) {
        printf("Оточення було повністю очищено\n");
    } else {
        perror("Помилка очищення оточення");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Вивести інформацію про поточне оточення.
        extern char **environ;
        printf("Поточне оточення:\n");
        for (int i = 0; environ[i] != NULL; i++) {
            printf("%s\n", environ[i]);
        }
    } else if (argc == 2) {
        // Опція -h або --help: вивести довідку.
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            printf("Довідка:\n");
            printf("-h або --help: вивести цю довідку\n");
            printf("-i <змінна> або --info <змінна>: вивести значення змінної оточення\n");
            printf("-s <змінна=значення> або --set <змінна=значення>: встановити значення змінної оточення\n");
            printf("-a <змінна> -v <значення> або --assign <змінна> --value <значення>: встановити значення змінної оточення\n");
            printf("-d <змінна> або --del <змінна>: видалити змінну оточення\n");
            printf("-c або --clear: очистити оточення\n");
        }
    } else if (argc == 3) {
        // Опція -i <змінна> або --info <змінна>: вивести значення змінної оточення.
        if (strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--info") == 0) {
            getEnvironmentVariable(argv[2]);
        }
    } else if (argc == 4) {
        // Опція -s <змінна=значення> або --set <змінна=значення>: встановити значення змінної оточення.
        if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--set") == 0) {
            char *var_value = strchr(argv[2], '=');
            if (var_value != NULL) {
                *var_value = '\0';
                setEnvironmentVariable(argv[2], var_value + 1);
            }
        }
    } else if (argc == 5) {
        // Опція -a <змінна> -v <значення> або --assign <змінна> --value <значення>: встановити значення змінної оточення.
        if ((strcmp(argv[1], "-a") == 0 && strcmp(argv[3], "-v") == 0) ||
            (strcmp(argv[1], "--assign") == 0 && strcmp(argv[3], "--value") == 0)) {
            setEnvironmentVariable(argv[2], argv[4]);
        }
    } else if (argc == 3) {
        // Опція -d <змінна> або --del <змінна>: видалити змінну оточення.
        if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--del") == 0) {
            deleteEnvironmentVariable(argv[2]);
        }
    } else if (argc == 2) {
        // Опція -c або --clear: очистити оточення.
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--clear") == 0) {
            clearEnvironment();
        }
    }

    return 0;
}