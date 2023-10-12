#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int *arr;
    int capacity;
    int size;
} ArrayList;

ArrayList *createArrayList() {
    ArrayList *list = (ArrayList *)malloc(sizeof(ArrayList));
    if (list == NULL) {
        printf("Помилка: не вдалося виділити пам'ять для ArrayList.\n");
        exit(EXIT_FAILURE);
    }

    list->arr = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    if (list->arr == NULL) {
        printf("Помилка: не вдалося виділити пам'ять для масиву.\n");
        exit(EXIT_FAILURE);
    }

    list->capacity = INITIAL_CAPACITY;
    list->size = 0;
    return list;
}

void add(ArrayList *list, int item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->arr = (int *)realloc(list->arr, list->capacity * sizeof(int));
        if (list->arr == NULL) {
            printf("Помилка: не вдалося виділити пам'ять для масиву.\n");
            exit(EXIT_FAILURE);
        }
    }
    list->arr[list->size] = item;
    list->size++;
}

void insert(ArrayList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Помилка: невірний індекс для вставки.\n");
        return;
    }

    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->arr = (int *)realloc(list->arr, list->capacity * sizeof(int));
        if (list->arr == NULL) {
            printf("Помилка: не вдалося виділити пам'ять для масиву.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = list->size; i > index; i--) {
        list->arr[i] = list->arr[i - 1];
    }

    list->arr[index] = item;
    list->size++;
}

int size(ArrayList *list) {
    return list->size;
}

void removeItem(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Помилка: невірний індекс для видалення.\n");
        return;
    }

    for (int i = index; i < list->size - 1; i++) {
        list->arr[i] = list->arr[i + 1];
    }

    list->size--;
}

void set(ArrayList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Помилка: невірний індекс для зміни.\n");
        return;
    }

    list->arr[index] = item;
}

int get(ArrayList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Помилка: невірний індекс для отримання.\n");
        return -1;
    }

    return list->arr[index];
}

void show(ArrayList *list) {
    if (list->size == 0) {
        printf("Список пустий.\n");
        return;
    }

    printf("Список елементів: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->arr[i]);
    }
    printf("\n");
}

void destroyArrayList(ArrayList *list) {
    free(list->arr);
    free(list);
}

int main() {
    ArrayList *list = createArrayList();

    int choice, item, index;

    do {
        printf("\nМеню:\n");
        printf("1. Створити\n");
        printf("2. Додавання\n");
        printf("3. Вставка\n");
        printf("4. Кількість\n");
        printf("5. Видалення\n");
        printf("6. Змінити\n");
        printf("7. Інфо\n");
        printf("8. Show\n");
        printf("9. Вихід\n");
        printf("Виберіть опцію: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list = createArrayList();
                printf("Список створено.\n");
                break;
            case 2:
                printf("Введіть елемент для додавання: ");
                scanf("%d", &item);
                add(list, item);
                printf("Елемент додано в кінець списку.\n");
                break;
            case 3:
                printf("Введіть індекс для вставки: ");
                scanf("%d", &index);
                printf("Введіть елемент для вставки: ");
                scanf("%d", &item);
                insert(list, index, item);
                printf("Елемент вставлено в середину списку.\n");
                break;
            case 4:
                printf("Кількість елементів у списку: %d\n", size(list));
                break;
            case 5:
                printf("Введіть індекс для видалення: ");
                scanf("%d", &index);
                removeItem(list, index);
                printf("Елемент видалено.\n");
                break;
            case 6:
                printf("Введіть індекс для зміни: ");
                scanf("%d", &index);
                printf("Введіть новий елемент: ");
                scanf("%d", &item);
                set(list, index, item);
                printf("Елемент змінено.\n");
                break;
            case 7:
                printf("Введіть індекс для інформації: ");
                scanf("%d", &index);
                printf("Значення елемента за індексом %d: %d\n", index, get(list, index));
                break;
            case 8:
                show(list);
                break;
            case 9:
                destroyArrayList(list);
                printf("Програму завершено.\n");
                break;
            default:
                printf("Невірний вибір. Спробуйте ще раз.\n");
        }
    } while (choice != 9);

    return 0;
}
