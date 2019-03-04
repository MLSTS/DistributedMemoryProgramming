#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int i, j, rank;
  	int A[100], B[100], C[100], LA[50], LB[50], LC[50];
  	srand(1234);
  	for (i = 0; i < 100; i++) {
    	  A[i] = rand()%1000;
    	  B[i] = rand()%1000;
  	}

  	MPI_Init (&argc, &argv);
  	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  	MPI_Scatter ((void *)A, 50, MPI_INT, (void *)LA , 50, MPI_INT, 0, MPI_COMM_WORLD);
  	MPI_Scatter ((void *)B, 50, MPI_INT, (void *)LB , 50, MPI_INT, 0, MPI_COMM_WORLD);

  	for (i = 0; i < 50; i++) {
    	  LC[i] = LA[i] + LB[i];
	}

  	MPI_Gather ((void *)LC, 50, MPI_INT, (void *)C , 50, MPI_INT, 0, MPI_COMM_WORLD);

  	if (rank == 0) {
	  for (j = 0; j < 100; j++) {
            printf("C[%d] = %d ", j, C[j]);
  	  }
	  printf("\n");
	}
	MPI_Finalize();
}

