#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int i, j, size, rank;
	int Lsum = 0, Gsum = 0;
	int A[8][8], x[4][8];
	srand(1234);
	for (i = 0; i < 8; i++) {
	  for (j = 0; j < 8; j++) {
	    A[i][j] = rand()%1000;
	  }
  	}

  	MPI_Init(&argc, &argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &size);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  	MPI_Scatter((void *)A, 8*(8/size), MPI_INT, (void *)x , 8*(8/size), MPI_INT, 0, MPI_COMM_WORLD);

	for (i = 0; i < (8/size); i++) {
	  for (j = 0; j < 8; j++) {
	    Lsum += x[i][j];
	  }
	}

	printf("Process %d: Local Sum = %d\n", rank, Lsum);
	MPI_Reduce(&Lsum, &Gsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
	  printf("Process %d: Global Total Sum = %d\n", rank, Gsum);
  	}
	MPI_Finalize();
}
