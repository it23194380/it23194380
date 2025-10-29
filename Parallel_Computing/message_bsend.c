#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    int rank;
    int data = 100;
    int buf_size;
    void* buffer;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    buf_size = MPI_BSEND_OVERHEAD + sizeof(int);
    buffer = malloc(buf_size);
    MPI_Buffer_attach(buffer, buf_size);

    if (rank == 0) {
        MPI_Bsend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0 buffered and sent data = %d\n", data);
    } else if (rank == 1) {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1 received data = %d\n", data);
    }

    MPI_Buffer_detach(&buffer, &buf_size);
    free(buffer);
    MPI_Finalize();
    return 0;
}
