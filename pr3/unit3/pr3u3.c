#include <stdio.h>
#include <stdlib.h>
int **matrix;  // Вказівник на матрицю
int rows = 0;  // Кількість рядків
int cols = 0;  // Кількість стовпців

void createMatrix() {                                                           // Функція для створення матриці та заповнення нулями
    printf("Введіть кількість рядків: ");
    scanf("%d", &rows);
    
    printf("Введіть кількість стовпців: ");
    scanf("%d", &cols);
    
    matrix = (int **)malloc(rows * sizeof(int *));                              // Виділяємо пам'ять для матриці
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {                                        // Заповнюємо матрицю нулями
            matrix[i][j] = 0;
        }
    }
    
    printf("Матриця створена та заповнена нулями.\n");
}

void deleteMatrix() {                                                           // Функція для видалення матриці та звільнення пам'яті
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    rows = 0;
    cols = 0;
    
    printf("Матриця видалена.\n");
}

void resizeMatrix(int newRows, int newCols) {                                   // Функція для зміни розмірів матриці зі збереженням значень
    int **newMatrix = (int **)malloc(newRows * sizeof(int *));
    
    for (int i = 0; i < newRows; i++) {
        newMatrix[i] = (int *)malloc(newCols * sizeof(int));
        for (int j = 0; j < newCols; j++) {
            if (i < rows && j < cols) {
                newMatrix[i][j] = matrix[i][j];                                 // Зберігаємо існуюче значення, якщо воно існує
            } else {
                newMatrix[i][j] = 0;                                            // Заповнюємо нові елементи нулями
            }
        }
    }
    
    for (int i = 0; i < rows; i++) {                                            // Звільняємо пам'ять початкової матриці
        free(matrix[i]);
    }
    free(matrix);
    
    matrix = newMatrix;                                                         // Оновлюємо вказівник на нову матрицю
    rows = newRows;                                                             // Функція для встановлення значення в елемент матриці
    cols = newCols;
    
    printf("Розміри матриці змінені.\n");
}

void setMatrixValue(int row, int col, int value) {                              // Функція для встановлення значення в елемент матриці
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        matrix[row][col] = value;
        printf("Значення встановлено.\n");
    } else {
        printf("Невірні номери рядка або стовпця.\n");
    }
}

void matrixInfo() {                                                             // Функція для виведення інформації про матрицю
    printf("Кількість рядків: %d\n", rows);
    printf("Кількість стовпців: %d\n", cols);
}

void displayMatrix() {                                                          // Функція для відображення матриці
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void saveMatrixToFile(char *filename) {                                         // Функція для збереження матриці у файл
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Помилка при відкритті файлу.\n");
        return;
    }

    fprintf(file, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Матриця збережена у файлі.\n");
}

void loadMatrixFromFile(char *filename) {                                       // Функція для завантаження матриці з файлу
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Помилка при відкритті файлу.\n");
        return;
    }

    fscanf(file, "%d %d", &rows, &cols);                                        // Читаємо розміри матриці

    matrix = (int **)malloc(rows * sizeof(int *));                              // Виділяємо пам'ять для нової матриці
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    printf("Матриця завантажена з файлу.\n");
}

void performOperations() {                                                      // Функція для виконання операцій над елементами матриці
    char operation;
    int row, col;
    int value;
    
    printf("Виберіть операцію:\n1.+ \n2.- \n3.*\n4./\n");
    scanf(" %c", &operation);
    printf("Введіть номер рядка: ");
    scanf("%d", &row);
    printf("Введіть номер стовпця: ");
    scanf("%d", &col);
    printf("Введіть значення для операції: ");
    scanf("%d", &value);
    
    if (row >= 0 && row < rows && col >= 0 && col < cols) {                     // Перевірка наявності вказаних рядка та стовпця в матриці
        switch (operation) {
            case '1':
                matrix[row][col] += value;
                break;
            case '2':
                matrix[row][col] -= value;
                break;
            case '3':
                matrix[row][col] *= value;
                break;
            case '4':
                if (value != 0) {
                    matrix[row][col] /= value;
                } else {
                    printf("Ділення на нуль недопустиме.\n");
                }
                break;
            default:
                printf("Невірна операція. Будь ласка, виберіть ще раз.\n");
        }
    } else {
        printf("Невірні номери рядка або стовпця.\n");
    }
}

int main() {
    char choice;
    
    do {
        printf("\nВиберіть функцію:\n");
        printf("1. Створити матрицю\n");
        printf("2. Видалити матрицю\n");
        printf("3. Змінити розмір матриці\n");
        printf("4. Інформація про матрицю\n");
        printf("5. Показати матрицю\n");
        printf("6. Дії над елементами матриці\n");
        printf("7. Встановити значення елемента матриці\n");
        printf("8. Зберегти матрицю у файл\n");
        printf("9. Завантажити матрицю з файлу\n");
        printf("x. Вийти\n");
        
        scanf(" %c", &choice);
        
        switch (choice) {
            case '1':
                createMatrix();
                break;
            case '2':
                deleteMatrix();
                break;
            case '3': {
                int newRows, newCols;
                printf("Введіть нову кількість рядків: ");
                scanf("%d", &newRows);
                
                printf("Введіть нову кількість стовпців: ");
                scanf("%d", &newCols);
                
                resizeMatrix(newRows, newCols);
                break;
            }
            case '4':
                matrixInfo();
                break;
            case '5':
                displayMatrix();
                break;
            case '6':
                performOperations();
                break;
            case '7': {
                int row, col, value;
                printf("Введіть номер рядка: ");
                scanf("%d", &row);
                printf("Введіть номер стовпця: ");
                scanf("%d", &col);
                printf("Введіть значення: ");
                scanf("%d", &value);
                
                setMatrixValue(row, col, value);
                break;
            }
            case '8': {
                char filename[100];
                printf("Введіть ім'я файлу для збереження: ");
                scanf("%s", filename);
                saveMatrixToFile(filename);
                break;
            }
            case '9': {
                char filename[100];
                printf("Введіть ім'я файлу для завантаження: ");
                scanf("%s", filename);
                loadMatrixFromFile(filename);
                break;
            }
            case 'x': 
                deleteMatrix();                                                 // Видаляємо матрицю перед виходом
                printf("Програма завершена.\n");
                break;
            default:
                printf("Невірний вибір. Будь ласка, спробуйте знову.\n");
        }
    } while (choice != 'x');
    return 0;
}