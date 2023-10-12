#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("Помилка: не вдалося виділити пам'ять для LinkedList.\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void add(LinkedList *list, int item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Помилка: не вдалося виділити пам'ять для нового вузла.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    list->size++;
}

void insert(LinkedList *list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Помилка: невірний індекс для вставки.\n");
        return;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Помилка: не вдалося виділити пам'ять для нового вузла.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

int size(LinkedList *list) {
    return list->size;
}

void removeItem(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Помилка: невірний індекс для видалення.\n");
        return;
    }

    Node *temp;
    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        Node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }

    free(temp);
    list->size--;
}

void set(LinkedList *list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Помилка: невірний індекс для зміни.\n");
        return;
    }

    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = item;
}

int get(LinkedList *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Помилка: невірний індекс для отримання.\n");
        return -1;
    }

    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void show(LinkedList *list) {
    if (list->head == NULL) {
        printf("Список пустий.\n");
        return;
    }

    printf("Список елементів: ");
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void destroyLinkedList(LinkedList *list) {
    Node *current = list->head;
    Node *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList *list = createLinkedList();

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
                list = createLinkedList();
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
                destroyLinkedList(list);
                printf("Програму завершено.\n");
                break;
            default:
                printf("Невірний вибір. Спробуйте ще раз.\n");
        }
    } while (choice != 9);

    return 0;
}

