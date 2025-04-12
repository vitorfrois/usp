// para compilar: mpicc 02-split_example.c -o 02-split_example -Wall
// para rodar: mpirun -np P 02-split_example

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

    int my_rank, num_proc, collor, key, new_rank;

    MPI_Comm new_comm;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
	
	if ( !(my_rank % 2) )
		collor = 0;
	else
		collor = 1;
    
	key = (num_proc-1) - my_rank;

	// obtem identificador do grupo original
	MPI_Comm_split(MPI_COMM_WORLD, collor, key, &new_comm);
	
	MPI_Comm_rank(new_comm, &new_rank);
	printf("Original my_rank = %d, collor=%d, New my rank = %d \n", my_rank, collor, new_rank);

	MPI_Finalize();
	return(0);
}
