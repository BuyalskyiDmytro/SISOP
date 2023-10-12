#include <stdio.h>
#include <math.h>

int main() {
    int n;

    printf("Введіть кількість елементів у масиві: ");
    scanf("%d", &n);

    double arr[n];
    printf("Введіть елементи масиву:\n");
    for (int i = 0; i < n; i++) {
        printf("Елемент %d: ", i + 1);
        scanf("%lf", &arr[i]);
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    double average = sum / n;

    int count_above_average = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count_above_average++;
        }
    }

    double sum_mod_after_negative = 0;
    int found_negative = 0;
    for (int i = 0; i < n; i++) {
        if (found_negative) {
            sum_mod_after_negative += fabs(arr[i]);
        } else if (arr[i] < 0) {
            found_negative = 1;
        }
    }

    printf("Кількість елементів, які більші за середнє значення: %d\n", count_above_average);
    printf("Сума модулів елементів після першого від'ємного елемента: %.2lf\n", sum_mod_after_negative);

    return 0;
}