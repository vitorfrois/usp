#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    int npes, rank, messageTag, messageLenght, ret;
    int bufferReceive;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    messageLenght = sizeof(int);
    messageTag = 1;

    if (rank == 0){
        int message = 0;
        int dest = 1;
        MPI_Send(
            &message, 
            messageLenght, 
            MPI_INT, 
            dest, 
            messageTag, 
            MPI_COMM_WORLD
        );

        MPI_Recv(
            &bufferReceive, 
            messageLenght,
            MPI_INT,
            npes - 1,
            messageTag,
            MPI_COMM_WORLD,
            &status
        );
        printf("Process %d: Final token value is %d.", rank, bufferReceive);
    } else {
        int message;
        MPI_Recv(
            &message, 
            messageLenght,
            MPI_INT,
            rank - 1,
            messageTag,
            MPI_COMM_WORLD,
            &status
        );

        message += 1;
        int dest = (rank == npes - 1)? 0 : rank + 1;

        MPI_Send(
            &message, 
            messageLenght, 
            MPI_INT, 
            dest, 
            messageTag, 
            MPI_COMM_WORLD
        );
    }

    fflush(0);
    ret = MPI_Finalize();
    if (ret == MPI_SUCCESS)
        return 0;
    else    
        return 1;
}