#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int msgtag;
    int x[8][8], y[4][8];
    int p1sum, p2sum, sum;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    msgtag = 1010;

    if (rank == 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                x[i][j] = i + j;
            }
        }
        MPI_Send(&x[0][0], 32, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        MPI_Send(&x[4][0], 32, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
        MPI_Recv(&p1sum, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);
        MPI_Recv(&p2sum, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD, &status);
        printf("Total array sum = %d\n", p1sum + p2sum);        
    }
    
    else {
        MPI_Recv(&y[0][0], 32, MPI_INT, 0, msgtag, MPI_COMM_WORLD, &status);
        sum = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                sum += y[i][j];
            }
        }
        MPI_Send(&sum, 1, MPI_INT, 0, msgtag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}