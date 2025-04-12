#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 14
 
int main( int argc, char **argv){
    int rank, size,rec_size,rec_size_resto, i, root = 0;
	int *vetor_env,*vetor_rec,*vetor_sizes,*vetor_dsp;

    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );

    rec_size=TAM/size;
    rec_size_resto=rec_size+TAM%size;

    if(rank==size-1)
    {
		vetor_rec=(int*)malloc((rec_size_resto+2)*sizeof(int));
	}
	else
	{
		vetor_rec=(int*)malloc((rec_size+2)*sizeof(int));
	}

    if(rank == root)
    {
		printf("MPI_Scatterv sem sobreposicao. \n");
		
		vetor_env=(int*)malloc(TAM*sizeof(int));
		vetor_dsp=(int*)malloc(size*sizeof(int));
		vetor_sizes=(int*)malloc((size)*sizeof(int));

        for(i=0;i<TAM;i++)
        {
            vetor_env[i]=i;
        }
        for(i=0;i<(size-1);i++)
		{
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

    if(rank==size-1)
    {
        for(i=0;i<rec_size_resto;i++)
        {
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
            fflush(0);
        }
    }
    else
    {
        for(i=0;i<rec_size;i++)
        {
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
            fflush(0);
        }
    }

    
    MPI_Barrier(MPI_COMM_WORLD);
    //
    // Abaixo tem o codigo que faz sobreposicao dos dados enviados pelo scatterv().
    // Neste caso todos os processos, a excecao do primeiro e do ultimo mandam dois 
	// elementos a mais, sendo um antes e outro depois da faixa de dados do processos.
    // O processo 0 manda apenas 1 dado a mais, sendo este dado aquele que vem 
	// depois da faixa de valores.
    // Faz isso porque nao ha um valor na posicao -1 do vetor.
    // o processo (size-1) também manda apenas 1 dado a mais, sendo este dado aquele 
	// que vema antes da faixa de valores deste processo. Faz isso porque nao ha um 
	// valor na posicao size do vetor.
    //
    if(rank == root)
    {
		printf("\n MPI_Scatterv com sobreposicao. \n");
        fflush(0);

        for(i=1; i<(size-1); i++)
        {
            vetor_sizes[i] = rec_size+2; // amount of items in this slot
            vetor_dsp[i] = (i*rec_size)-1; // shift in relation to start address
        }

        vetor_sizes[0] = rec_size+1;
        vetor_dsp[0] = 0;
        
        vetor_sizes[size-1] = rec_size_resto+1;
        vetor_dsp[size-1] = (i*rec_size)-1;

        // para depuracao apenas
        for(i=0;i<size;i++)
        {
            printf("vetor_sizes[%d] = %d, vetor_dsp[%d] = %d\n", i, vetor_sizes[i], i, vetor_dsp[i]);
            fflush(0);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
	
    MPI_Scatterv (vetor_env,vetor_sizes,vetor_dsp,MPI_INT,vetor_rec,(rec_size_resto+1),MPI_INT,root,MPI_COMM_WORLD);

    if (rank == root)
    {
        for(i=0;i<(rec_size+1);i++)
        {
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
            fflush(0);
        }
    }
    else if (rank==(size-1))
    {
        for(i=0;i<(rec_size_resto+1);i++)
        {
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
            fflush(0);
        }
    }
    else {
        for(i=0;i<(rec_size+2);i++)
        {
            printf("Rank :%d recebeu %d\n",rank, vetor_rec[i]);
            fflush(0);
        }
    }
    
    free(vetor_rec);
    
	if(rank == root)
    {
		free(vetor_env);
		free(vetor_dsp);
		free(vetor_sizes);
    }
	
    MPI_Finalize();
}
