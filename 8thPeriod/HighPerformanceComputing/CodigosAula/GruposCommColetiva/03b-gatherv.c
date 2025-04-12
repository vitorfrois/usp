#include <mpi.h>
#include <stdio.h>
#include<stdlib.h>

// TAM precisa ser multiplo de size, pois o codigo nao esta pronto para diferentes blocos;
// apenas o MPI_Gatherv. Falta atribuir o resto aos processos (ou ao ultimo).
//
#define TAM 16

int main( int argc, char **argv )
{
    int rank, size,rec_size,i,*vetor_env,*vetor_rec,*vetor_sizes,*vetor_dsp, root = 0;
//    int rec_size_resto;
 
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
	
    rec_size=TAM/size;
    //rec_size_resto=rec_size+TAM%size;
	
    vetor_env=(int*)malloc(rec_size*sizeof(int));

    if(rank == root)
    {
		vetor_rec=(int*)malloc(TAM*sizeof(int));
		vetor_dsp=(int*)malloc(size*sizeof(int));
		vetor_sizes=(int*)malloc(size*sizeof(int));

        for(i=0;i<size;i++)
		{
            vetor_sizes[i]=rec_size;
            vetor_dsp[i]=i*rec_size;
        }

		// para depuracao apenas
        for(i=0;i<size;i++)
        {
            printf("vetor_sizes[%d] = %d, vetor_dsp[%d] = %d\n", i, vetor_sizes[i], i, vetor_dsp[i]);
            fflush(0);
        }
		
    }

    for(i=0;i<rec_size;i++)
    {
        vetor_env[i]=(rank*rec_size)+i;
    }
    
    MPI_Gatherv (vetor_env,rec_size,MPI_INT,vetor_rec,vetor_sizes,vetor_dsp,MPI_INT,root,MPI_COMM_WORLD);

    if(rank == root)
    {
        for(i=0;i<TAM;i++)
        {
            printf("recebeu %d\n",vetor_rec[i]);
        }
		free(vetor_rec);
		free(vetor_dsp);
		free(vetor_sizes);
    }
    
    free(vetor_env);

    MPI_Finalize();
    
}
