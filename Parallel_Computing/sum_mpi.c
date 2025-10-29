#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    long long n = 10000000;
    int rank, size;
    long long local_sum = 0, total_sum = 0;
    long long start_i, end_i;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_i = rank * (n / size) + 1;
    end_i = (rank + 1) * (n / size);

    start = MPI_Wtime();
    for (long long i = start_i; i <= end_i; i++) {
        local_sum += i;
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    end = MPI_Wtime();

    if (rank == 0) {
        printf("Total sum = %lld\n", total_sum);
        printf("Time = %f seconds\n", end - start);
    }

    MPI_Finalize();
    return 0;
}
