#include <mpi.h>
#include <stdio.h>
#include <math.h>

float f(float x) {
    return x * x;
}

float trapezoid_area(float a, float b, float d) { 
    float area = 0;
    for (float x = a; x < b; x += d) {
        area += f(x) + f(x + d);
    }
    return area * d / 2.0f;
}

int main(int argc, char** argv) {
    int rank, size;
    float a = 0.0f, b = 1.0f;
    int n;
    float start, end, local_area, total_area;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the number of intervals: ");
        scanf("%d", &n);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    float d = (b - a) / n;
    float region = (b - a) / size;
    start = a + rank * region;
    end = start + region;
    local_area = trapezoid_area(start, end, d);
    MPI_Reduce(&local_area, &total_area, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (rank == 0) {
        printf("The total area under the curve is: %f\n", total_area);
        printf("Execution time: %f seconds\n", end_time - start_time);
    }
    
    MPI_Finalize();
    return 0;
}
