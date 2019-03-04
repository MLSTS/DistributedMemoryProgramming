#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int Lmin, Lmax, Lsum;
    int Gmin, Gmax, Gsum;
    int rank, size;
    int A[100], x[50];
    srand(1234);
    for (int i = 0; i < 100; i++) {
        A[i] = rand()%1000;
    }

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Scatter ((void * )A, 50, MPI_INT, (void *)x, 50, MPI_INT, 0, MPI_COMM_WORLD);

    Lmin = 0;
    Lmax = 0;
    Lsum = 0;
    for (int i = 0; i < 50; i++) {
        if (x[i] < Lmin) Lmin = x[i];
        if (x[i] > Lmax) Lmax = x[i];
        Lsum += x[i];
    }
    printf("Local Process %d: Lmin=%d Lmax=%d Lsum=%d\n", rank, Lmin, Lmax, Lsum);
    MPI_Reduce(&Lmin, &Gmin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&Lmax, &Gmax, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&Lsum, &Gsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        printf("Global: Gmin=%d Gmax=%d Gsum=%d\n", Gmin, Gmax, Gsum);
    }
    MPI_Finalize();
}