#include <mpi.h>
#include <stdio.h>
#include<stdlib.h>

#define TAM 17
 
int main(int argc, char **argv)
{
    int rank, size,rec_size,rec_size_resto, i;
	int *vetor_env,*vetor_rec,*vetor_sizes,*vetor_dsp;
	int root = 0;
 
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    rec_size=TAM/size;
    rec_size_resto=rec_size+TAM%size;
	
	// ultimo processo recebe o resto.
    if(rank == size-1)
	{
		vetor_rec=(int*)malloc(rec_size_resto*sizeof(int));
	}
	else
	{
		vetor_rec=(int*)malloc(rec_size*sizeof(int));
	}

    if(rank == root)
	{
	    vetor_env=(int*)malloc(TAM*sizeof(int));
		vetor_dsp=(int*)malloc(size*sizeof(int));
		vetor_sizes=(int*)malloc((size)*sizeof(int));

        for(i=0;i<TAM;i++)
        {
            vetor_env[i]=i;
        }
        for(i=0;i<(size-1);i++){
            vetor_sizes[i]=rec_size; // amount of items in this slot
            vetor_dsp[i]=i*rec_size; // shift in relation to start address
        }
        vetor_sizes[size-1]=rec_size_resto;
        vetor_dsp[size-1]=i*rec_size;
		
		// para depuracao apenas
        for(i=0;i<size;i++)
        {
            printf("vetor_sizes[%d] = %d, vetor_dsp[%d] = %d\n", i, vetor_sizes[i], i, vetor_dsp[i]);
            fflush(0);
        }
    }
    
    MPI_Scatterv (vetor_env,vetor_sizes,vetor_dsp,MPI_INT,vetor_rec,rec_size_resto,MPI_INT,root,MPI_COMM_WORLD);
    
    if(rank == size-1)
	{
        for(i=0;i<rec_size_resto;i++)
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
    }
    else
	{
        for(i=0;i<rec_size;i++)
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
    }
    free(vetor_rec);
	if (rank == root)
	{
		free(vetor_env);
		free(vetor_dsp);
		free(vetor_sizes);
	}
	
    MPI_Finalize();
}
