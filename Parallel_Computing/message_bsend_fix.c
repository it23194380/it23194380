#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, data = 100;
    void* buffer;
    int bufsize;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bufsize = MPI_BSEND_OVERHEAD + sizeof(int);
    buffer = malloc(bufsize);
    MPI_Buffer_attach(buffer, bufsize);

    if (rank == 0) {
        MPI_Bsend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Rank 0 sent buffered message = %d\n", data);
    } else if (rank == 1) {
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank 1 received message = %d\n", data);
    }

    MPI_Buffer_detach(&buffer, &bufsize);
    free(buffer);
    MPI_Finalize();
    return 0;
}
