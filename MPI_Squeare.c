#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int msgtag;
    int x, y;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    msgtag = 1010;

    if (rank == 0) {
        x = 10;
        MPI_Send(&x, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&y, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        printf("The square of %d is %d\n", x, y);
    }
    
    if (rank == 1) {
        MPI_Recv(&y, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        y *= y;
        MPI_Send(&y, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}