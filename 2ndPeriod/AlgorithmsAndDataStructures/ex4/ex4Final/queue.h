#ifndef QUEUE_H
#define QUEUE_H

typedef struct p {
    char* name;
    int age;
    int isOld;
    int isSick;
    int category;
    int key;
}People;

typedef struct q {
    int top;
    int bottom;
    int size;
    int n;
    People* people;
}Queue;

Queue* createStack(int size);

// Queue is full when top is equal to the last index
int isFull(Queue* queue);
 
// Queue is empty when top is equal to -1
int isEmpty(Queue* queue);

// Function to add an item to queue.  It increases top by 1
void push(Queue* queue);
 
// Function to print the queue
void print(Queue* queue);

// Function to remove an item from queue.  It decreases top by 1
void pop(Queue* queue);

// Function to sort the itens in queue by insertion method
void insertionSort(Queue* queue);

#endif