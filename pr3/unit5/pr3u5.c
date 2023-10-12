#include <stdio.h>
#include <math.h>
#include <float.h>                                                              //Для DBL_MAX

typedef struct Point {
    double x;
    double y;
    double z;
    double mass;
    int exists;
} Point;

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

int main() {
    int num_points;
    printf("Введіть кількість точок: ");  
    scanf("%d", &num_points);
    Point points[num_points];

    for (int i = 0; i < num_points; i++) {
        printf("Введіть координати (x, y, z) та масу для точки %d: ", i + 1);   
        scanf("%lf %lf %lf %lf", &points[i].x, &points[i].y, &points[i].z, &points[i].mass);
        points[i].exists = 1;  
    }

    while (1) {
        int smallest_mass_point_index = -1;
        double smallest_mass = DBL_MAX;                                         

        for (int i = 0; i < num_points; i++) {                                  //Пошук точки з найменшою масою
            if (points[i].exists && points[i].mass < smallest_mass) {
                smallest_mass = points[i].mass;
                smallest_mass_point_index = i;
            }
        }

        int remaining_points = 0;                                               //Чи були об'єднані всі точки
        for (int i = 0; i < num_points; i++) {
            if (points[i].exists) {
                remaining_points++;
            }
        }

        if (remaining_points <= 1) {                                            //Одна точка, вийти з циклу                      
            break;
        }

        double closest_distance = DBL_MAX;
        int closest_point_index = -1;

        for (int i = 0; i < num_points; i++) {
            if (points[i].exists && i != smallest_mass_point_index) {
                double dist = distance(points[smallest_mass_point_index], points[i]);
                if (dist > 0 && dist < closest_distance) {
                    closest_distance = dist;
                    closest_point_index = i;
                }
            }
        }

        if (closest_point_index != -1) {                                        //Пошук найближчої точки
            points[closest_point_index].mass += smallest_mass;
            points[smallest_mass_point_index].exists = 0;

            printf("Оновлена маса точки %d: %lf\n", closest_point_index + 1, points[closest_point_index].mass);
            printf("Координати точки %d: (%lf, %lf, %lf)\n", closest_point_index + 1,
                   points[closest_point_index].x, points[closest_point_index].y, points[closest_point_index].z);
        }
    }

    int last_point_index = -1;                                                  //Остання існуючя точка
    for (int i = 0; i < num_points; i++) {
        if (points[i].exists) {
            last_point_index = i;
            break;
        }
    }

    printf("\nКоординати останньої точки: (%lf, %lf, %lf)\n", points[last_point_index].x,
           points[last_point_index].y, points[last_point_index].z);
    printf("Кінцева маса останньої точки: %lf\n", points[last_point_index].mass);

    return 0;
}
