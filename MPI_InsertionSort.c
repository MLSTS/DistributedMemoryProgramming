/* Untested code */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int msgtag, save, temp;
    int A[5];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    msgtag = 1010;

    if (rank == 0) {
        srand(1234);
        for (int i = 0; i < 5; i++) {
            A[i] = rand()%1000;
        }
        save = A[0];
        for (i = 1; i < 5; i++) {
            if (save < A[i]) {
                MPI_Send(&save, 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
                save = A[i];
            }
            else {
                MPI_Send(&A[i], 1, MPI_INT, 1, msgtag, MPI_COMM_WORLD);
            }
        }  
    }
    
    else {
        MPI_Recv(&save, 1, MPI_INT, rank - 1, msgtag, MPI_COMM_WORLD, &status);
        for (i = rank + 1; i < 5; i++) {
            MPI_Recv(&temp, 1, MPI_INT, rank - 1, msgtag, MPI_COMM_WORLD, &status);
            if (save < temp) {
                MPI_Send(&save, 1, MPI_INT, rank + 1, msgtag, MPI_COMM_WORLD);
                save = temp;
            }
            else {
                MPI_Send(&temp, 1, MPI_INT, rank + 1, msgtag, MPI_COMM_WORLD);
            }
        }
    }
    MPI_Finalize();
}