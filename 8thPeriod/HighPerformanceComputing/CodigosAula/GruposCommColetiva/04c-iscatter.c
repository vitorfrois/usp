#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define TAM 12
 
int main( int argc, char **argv )
{
    int rank, size,rec_size, i,*vetor_env,*vetor_rec, root=0, test_flag;
 
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Request request;
    MPI_Status status;

    rec_size=TAM/size;
    vetor_rec=(int*)malloc(rec_size*sizeof(int));

    if(rank == root)
    {
		vetor_env=(int*)malloc(TAM*sizeof(int));
		for(i=0;i<TAM;i++)
        {
            vetor_env[i]=i;
        }
        sleep(1);
    }

    MPI_Iscatter(vetor_env,rec_size,MPI_INT,vetor_rec,rec_size,MPI_INT,root,MPI_COMM_WORLD, &request);

    // faz qq outra coisa enquanto nao terminou...
	i=0;
	do {
		i++;
		MPI_Test(&request, &test_flag, &status);
	}
	while (!test_flag);

    //MPI_Wait(&request, &status); // agora espera terminar a comm coletiva nao bloqueante
	printf("Process %d fez outra coisa em %d iteracoes. \n", rank, i);

    for(i=0;i<rec_size;i++)
    {
        printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
    }

    if(rank == root)
    {
		free(vetor_env);
	}
    free(vetor_rec);
    
    MPI_Finalize();
}
