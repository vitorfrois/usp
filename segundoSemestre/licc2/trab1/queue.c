#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "myString.h"
#include "data.h"
#include <unistd.h>
#include <time.h>

Queue* createQueue(int size){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->top = -1;  
    queue->bottom = 0;
    queue->shell = (Shell*)malloc(queue->size * sizeof(Shell));
    return queue;
}
 
int isFull(Queue* queue){
    return queue->top == queue->size - 1;
}
 
int isEmpty(Queue* queue){
    return (queue->top - queue->bottom) < 0;
}

void push(Queue* queue, double shellSize, char** shellName){
    if (isFull(queue))
        return;

    queue->top++;
    queue->shell[queue->top].size = shellSize;
    // printf("sizeof shellname = %d\n", sizeof(*shellName));
    queue->shell[queue->top].name = malloc(strlen(*shellName) + 1);
    strcpy(queue->shell[queue->top].name, *shellName);
    //insertionSort(queue);
}

void print(Queue* queue){
    if (isEmpty(queue)){
        //printf("FILA VAZIA\n");
        return;
    }
    //printf("impressao: \n");
    for(int i = 0; i < queue->top+1; i++){       
        printf("%.3lf ", queue->shell[i].size);
        printf("%s\n", queue->shell[i].name);
    }
    //printf("queue->bottom = %d\n", queue->bottom);
    return;
}
 
void colorizedPrint(Queue* queue, int colorize, int index1, int index2){
   
    if (isEmpty(queue)){
        //printf("FILA VAZIA\n");
        return;
    }
    if(colorize == 1){
        usleep(100000);
        system("clear");
    }
    //printf("impressao: \n");
    for(int i = 0; i < queue->top+1; i++){
        printf("\033[35;45m");
        if(i == index1 && colorize == 1)
            printf("\033[33;43m");
        if(i == index2 && colorize == 1)
            printf("\033[42;32m");

        for(int iterate = 0; iterate < queue->shell[i].size*4; iterate++)    
            printf("d");

        printf("\033[0m\n");        
        //printf("%.3lf ", queue->shell[i].size);
        //printf("%s\n", queue->shell[i].name);
        if((i == index1 || i == index2) && colorize == 1)
            printf("\033[0m");
    }
    //printf("queue->bottom = %d\n", queue->bottom);
    return;
}

void insertionSort(Queue* queue, int first, int d){
    Shell aux;
    int i, j;
    for (i = (d+first+queue->bottom); i < (queue->top+1); i += d) {
        aux.name = malloc(sizeof(char) * (strlen(queue->shell[i].name) + 1));
        dataCpy(&aux, &queue->shell[i]);
        j = i - d;
        //printf("j = %d, i = %d, d = %d\n", j, i, d);

        while (j >= queue->bottom && (queue->shell[j].size > aux.size)) {
            //printf("shinji entra no while\n");
            queue->shell[j+d].name = realloc(queue->shell[j+d].name, sizeof(char) * (strlen(queue->shell[j].name) + 1));
            dataCpy(&queue->shell[j+d], &queue->shell[j]);
            j -= d;
            
            colorizedPrint(queue, 1, j, i);
            printf("subqueues = %d\n", d);
        }
        queue->shell[j+d].name = realloc(queue->shell[j+d].name, sizeof(char) * (strlen(aux.name) + 1));
        dataCpy(&queue->shell[j+d], &aux);
        free(aux.name);
    }
}

void pauloSort(Queue* queue){
    //printf("queue top = %d\n", queue->top);
    for(int subQueues = (queue->top + 1)/2; subQueues >= 1; subQueues = subQueues/2){
        //printf("subqueues = %d\n", subQueues);
        for(int first = 0; first < subQueues; first++){
            insertionSort(queue, first, subQueues);
        }
        printf("\033[0m");       
    }
}

void timeMeasure(Queue* queue, int queueSize, char* mode){
    clock_t t = clock();
    if(strcmp(mode, "paulo") == 0)
        pauloSort(queue);
    else if(strcmp(mode, "insertion") == 0)
        insertionSort(queue, 0, 1);
    else
        printf("%s is a non-identified sorting method\n", mode);
    
    
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%sSort took %f seconds to execute the sort on %d shells\n", mode, time_taken, queueSize);

}