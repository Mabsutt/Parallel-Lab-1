#include <stdio.h>
#include <math.h>
#include <time.h>

float f(float x) {
    return x * x;
}

float trapezoid_area(float a, float b, int n) {
    float area = 0;
    float d = (b - a) / n;

    for (float x = a; x < b; x += d) {
        area += f(x) + f(x + d);
    }

    return area * d / 2.0f;
}

int main() {
    float a = 0.0f, b = 1.0f;
    int n;
    float total_area;
    
    printf("Enter the number of intervals: ");
    scanf("%d", &n);

    clock_t start_time = clock();
    total_area = trapezoid_area(a, b, n);
    clock_t end_time = clock();

    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("The total area under the curve is: %f\n", total_area);
    printf("Execution time: %f seconds\n", execution_time);
    
    return 0;
}
