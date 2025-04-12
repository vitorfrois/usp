// para compilar: mpicc 01-group_comm.c -o 01-group_comm -Wall
// para rodar: mpirun -np P 01-group_comm

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{

	int my_rank, par, imp, i, new_rank;
	int num_proc;
	int vet_par[10], vet_imp[10];

	MPI_Group grupo_velho, grupo_par, grupo_impar;
	MPI_Comm comm_par, comm_impar, communicator;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

	vet_par[0] = vet_imp[0] = 0;  // processo com rank 0 pertence aos dois grupos
	for (par = 1, imp = 1, i = 1; i < num_proc; i++) 
	{
		if ( !(i % 2) )
			vet_par[par++] = i;
		else
			vet_imp[imp++] = i;
	}
	
	printf("par = %d imp = %d \n", par, imp);
	
	// obtem identificador do grupo original
	MPI_Comm_group(MPI_COMM_WORLD, &grupo_velho);
	
	// cria um novo grupo dos ranks pares
	MPI_Group_incl(grupo_velho, par, vet_par, &grupo_par);

	// cria um novo grupo dos ranks ímpares
	MPI_Group_incl(grupo_velho, imp, vet_imp, &grupo_impar);

	// cria os novos comunicadores dos novos grupos par e ímpar
	MPI_Comm_create(MPI_COMM_WORLD, grupo_par, &comm_par);
	MPI_Comm_create(MPI_COMM_WORLD, grupo_impar, &comm_impar);

	if (my_rank == 0)   
	{
	    MPI_Comm_rank(comm_par, &new_rank);
	    printf("my_rank original= %d, vindo do grupo par com new_rank = %d \n", my_rank, new_rank);

	    MPI_Comm_rank(comm_impar, &new_rank);
	    printf("my_rank original=%d, vindo do do grupo ímpar com new_rank = %d \n", my_rank, new_rank);
	}
	else  
	{
	    if ( !(my_rank % 2) )
            communicator = comm_par;
	    else
            communicator = comm_impar;
	
	    MPI_Comm_rank(communicator, &new_rank);
	
	    printf("my_rank original= %d e new_rank = %d \n", my_rank, new_rank);
	}
	 
	MPI_Finalize();
	return(0);
}
