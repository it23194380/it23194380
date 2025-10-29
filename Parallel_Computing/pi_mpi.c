#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    long long n = 10000000;
    int rank, size, count = 0, total_count = 0;
    double x, y, z, pi;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long local_n = n / size;
    srand(rank + 1);

    start = MPI_Wtime();
    for (long long i = 0; i < local_n; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;
        if (z <= 1.0) count++;
    }

    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0) {
        pi = ((double)total_count / n) * 4.0;
        printf("Estimated Pi = %f\n", pi);
        printf("Time = %f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}
