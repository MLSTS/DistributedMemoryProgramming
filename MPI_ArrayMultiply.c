#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int msgtag;
    int x[10], y[10];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    msgtag = 1010;

    if (rank == 0) {
        for (int i = 0; i < 10; i++) {
            x[i] = i * 1;
        }
        MPI_Send(&x, 10, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&y, 10, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        printf("The original array contains: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8], x[9]);
        printf("The result array contains: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", y[0], y[1], y[2], y[3], y[4], y[5], y[6], y[7], y[8], y[9]);
    }
    
    if (rank == 1) {
        MPI_Recv(&y, 10, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        for (int j = 0; j < 10; j++) {
            y[j] = j * 10;
        }
        MPI_Send(&y, 10, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}