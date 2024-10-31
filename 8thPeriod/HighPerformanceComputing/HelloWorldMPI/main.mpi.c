#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MESSAGE "Hello, World from process X!"

int main(int argc, char* argv[]){
    int npes, rank, source, dest, messageTag, messageLenght, ret;
    char *bufferReceive;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    messageLenght = strlen(MESSAGE) + 1;
    bufferReceive = (char *) malloc(messageLenght);
    messageTag = 1;

    if (rank == 0){
        source = dest = 1;
        for(int i = 1; i < npes; i++) {
            MPI_Recv(
                bufferReceive, 
                messageLenght,
                MPI_CHAR,
                i,
                messageTag,
                MPI_COMM_WORLD,
                &status
            );
            printf("Message received: ");
            printf(bufferReceive);
            printf("\n");

        }
    } else {
        source = rank;
        dest = 0;
        char message[messageLenght];
        sprintf(message, "Hello, World from process %d!", source);
        MPI_Send(message, messageLenght, MPI_CHAR, dest, messageTag, MPI_COMM_WORLD);
    }

    free(bufferReceive);
    fflush(0);
    ret = MPI_Finalize();
    if (ret == MPI_SUCCESS)
        return 0;
    else    
        return 1;
}