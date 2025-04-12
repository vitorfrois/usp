//compilar: mpicc modo-com.c -o modo-com
//executar: mpirun -np 2 modo-com

// exemplifica comunica��o ponto-a-ponto n�o bloqueante
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv)  {
    int my_rank, num_procs;
    int tag, src, dst, test_flag, i;
    int buffersize, sizemsgsnd, nrmsgs;

    char *buffersnd;
    char msgsnd[30], msgrcv[30], msgsync[30];

    MPI_Status  status;
    MPI_Request mpirequest_mr, mpirequest_mr_ready;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    tag = 0;
    if (my_rank == 0)
    {
        src = 1;  // determina o processo de origem de uma msg recebida como nao bloqueante
        dst = 1;  // determina o processo de destino das msgs enviadas pelo processo com rank 0

        // recebe msg com primitiva nao bloqueante standard
        MPI_Irecv(msgrcv, sizeof(msgrcv), MPI_CHAR, src, tag, MPI_COMM_WORLD, &mpirequest_mr);
        MPI_Test(&mpirequest_mr, &test_flag, &status);
        if(test_flag)
            printf("Rank 0: MPI_Test flag = %d, msgrcv=%s. \n", test_flag, msgrcv);
        else
            printf("Rank 0: MPI_Test flag = %d, nao recebeu a msg ainda. \n", test_flag);
    
        strcpy(msgsnd, "Blocking standard send");
        MPI_Send(msgsnd, strlen(msgsnd)+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);

        strcpy(msgsnd, "Blocking buffered send");
        MPI_Pack_size(strlen(msgsnd)+1, MPI_CHAR, MPI_COMM_WORLD, &sizemsgsnd);
        nrmsgs = 1; // apenas uma msg bsend sera enviada
        buffersize = sizemsgsnd + nrmsgs * MPI_BSEND_OVERHEAD;
        buffersnd = (char*) malloc(buffersize);
        MPI_Buffer_attach(buffersnd, buffersize);
        // envia a msg bsend usando o buffer criado pelo usuario
        MPI_Bsend(msgsnd, strlen(msgsnd)+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
        MPI_Buffer_detach(buffersnd, &buffersize);

        strcpy(msgsnd, "Blocking synchronous send");
        MPI_Ssend(msgsnd, strlen(msgsnd)+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);

        tag = 1; // Se este MPI_Recv abaixo usar a tag 0 entao esta msg podera ser recebida pelo MPI_Irecv
        MPI_Recv(msgsync, sizeof(msgsync), MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);

        tag = 0; // retorna para a tag = 0 usada nos sends e receives        
        strcpy(msgsnd, "Blocking ready send");
        MPI_Rsend(msgsnd, strlen(msgsnd)+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);

        if(!test_flag) {
            MPI_Wait(&mpirequest_mr, &status);
            printf("Rank 0: MPI_Wait liberou: msgrcv=%s. \n", msgrcv);
        }  
    } // fim do if (my_rank == 0)
    else   // my_rank == 1
    {
        dst = 0; // determina o destino da msg a ser enviada
        src = 0; // determina o processo de origem da msg recebida
        
        // recebe do send bloqueante standard
        MPI_Recv(msgrcv, sizeof(msgrcv), MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
        printf("Rank 1: msg 01 recebida: %s \n", msgrcv);
        fflush(0);
    
        // recebe do send bloqueante com buffer
        MPI_Recv(msgrcv, sizeof(msgrcv), MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
        printf("Rank 1: msg 02 recebida: %s \n", msgrcv);
        fflush(0);
    
        // recebe do send bloqueante sincrono
        MPI_Recv(msgrcv, sizeof(msgrcv), MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
        printf("Rank 1: msg 03 recebida: %s \n", msgrcv);
        fflush(0);
    
        // dispara previamente o MPI_IRecv para o send bloqueante ready existente no processo 0
        MPI_Irecv(msgrcv, sizeof(msgrcv), MPI_CHAR, src, tag, MPI_COMM_WORLD, &mpirequest_mr_ready);

        tag = 1;
        strcpy(msgsync, "unlock ready send");
        MPI_Send(msgsync, strlen(msgsync)+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD);
        // aguarda pelo recebimento da msg do MPI_Rsend. Ira finalizar o MPI_Irecv acima.
        MPI_Wait(&mpirequest_mr_ready, &status);
        
        printf("Rank 1: msg 04 recebida: %s \n", msgrcv);
        fflush(0);
        tag = 0;
        // send nao bloqueante
        strcpy(msgsnd, "Nonblocking standard send");  
        MPI_Isend(msgsnd, strlen(msgsnd)+1, MPI_CHAR, dst, tag, MPI_COMM_WORLD, &mpirequest_mr);
        MPI_Wait(&mpirequest_mr, &status);   
    }
    
    MPI_Finalize();
	
    exit(0);

}
