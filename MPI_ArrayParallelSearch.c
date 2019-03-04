#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int i, j, rank, input;
	int Lcount = 0, Gcount = 0;
	int A[100], x[50];
	srand(1234);
	for (i = 0; i < 100; i++) {
	  A[i] = rand()%1000;
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Scatter((void *)A, 50, MPI_INT, (void *)x , 50, MPI_INT, 0, MPI_COMM_WORLD);

	if (rank == 0) {
	  printf("Enter an integer: ");
	  fflush(stdout);
	  scanf("%d",&input);
  	}

  	MPI_Bcast(&input, 1, MPI_INT, 0, MPI_COMM_WORLD);

  	for (j = 0; j < 50; j++) {
    	  if(x[j] < input){
            Lcount++;
	  }
  	}

 	printf("Process %d: Less than %d Local Count = %d\n", rank, input, Lcount);
  	MPI_Reduce(&Lcount, &Gcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  	if (rank == 0) {
    	  printf("Less than %d Global Count = %d\n", input, Gcount);
  	}
	MPI_Finalize();
}
