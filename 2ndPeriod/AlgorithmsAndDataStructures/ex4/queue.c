#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "myString.h"
#include "data.h"

// function to create a queue of given size. It initializes size of
// queue as 0
Queue* createQueue(int size){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->top = -1;
    queue->bottom = 0;
    queue->people = (People*)malloc(queue->size * sizeof(People));
    return queue;
}
 
// Queue is full when top is equal to the last index
int isFull(Queue* queue){
    return queue->top == queue->size - 1;
}
 
// Queue is empty when top is equal to -1
int isEmpty(Queue* queue){
    return (queue->top - queue->bottom) < 0;
}

// Function to add an item to queue.  It increases top by 1
void push(Queue* queue){
    char c;
    if (isFull(queue))
        return;
    queue->top++;
    queue->people[queue->top].key = queue->n;
    queue->people[queue->top].name = readString();
    int age, disease;
    scanf("%d ", &age);
    queue->people[queue->top].age = age;
    if(age >= 60)
        queue->people[queue->top].isOld = 1;
    else
        queue->people[queue->top].isOld = 0;
    scanf("%d%c", &disease, &c);
    if(c == '\r')
        c = getchar();

    queue->people[queue->top].isSick = disease;
    computeCategory(&(queue->people[queue->top]));
    insertionSort(queue);

}
 
void print(Queue* queue){
   
    if (isEmpty(queue)){
        //printf("FILA VAZIA\n");
        return;
    }
    printf("impressao: \n");
    for(int i = 0; i < queue->top+1; i++){
        printf("%s ", queue->people[i].name);
        printf("%d ", queue->people[i].age);
        printf("%d\n", queue->people[i].isSick);
    }
    printf("queue->bottom = %d\n", queue->bottom);
    return;
}

// Function to remove an item from queue.  It decreases top by 1
void pop(Queue* queue){
    //print(queue);
    if (isEmpty(queue)){
        printf("FILA VAZIA\n");
        return;
    }
    printf("%s ", queue->people[queue->bottom].name);
    printf("%d ", queue->people[queue->bottom].age);
    printf("%d\n", queue->people[queue->bottom].isSick);

    queue->bottom++;
    return;
}

void insertionSort(Queue* queue){
    People aux;
    int i, j;
    for (i = 1+queue->bottom; i < queue->top+1; i++) {
        aux.name = malloc(sizeof(char) * (strlen(queue->people[i].name) + 1));
        dataCpy(&aux, &queue->people[i]);
        j = i - 1;

        while (j >= queue->bottom && dataCmp(queue->people[j], aux)) {
            queue->people[j+1].name = realloc(queue->people[j+1].name, sizeof(char) * (strlen(queue->people[j].name) + 1));
            dataCpy(&queue->people[j+1], &queue->people[j]);
            j--;
        }
        queue->people[j+1].name = realloc(queue->people[j+1].name, sizeof(char) * (strlen(aux.name) + 1));
        dataCpy(&queue->people[j+1], &aux);
        free(aux.name);
    }
}