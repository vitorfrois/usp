#ifndef QUEUE_H
#define QUEUE_H

typedef struct s {
    char* name;
    double size;
}Shell;

typedef struct q {
    int top;
    int bottom;
    int size;
    int subQueues;
    Shell* shell;
}Queue;

// function to create a queue of given size. It initializes size of
// queue as 0
Queue* createQueue(int size);

// Queue is full when top is equal to the last index
int isFull(Queue* queue);
 
// Queue is empty when top is equal to -1
int isEmpty(Queue* queue);

// Function to add an item to queue.  It increases top by 1
void push(Queue* queue, double shellSize, char** shellName);
 
// Function to print the queue
// colorize: 
//           1 to print all iterations with system(clear) and colors
//           0 to print as usual 
// index1: 
//           number of index to be printed in red
// index2: 
//           number of index to be printed in green
void colorizedPrint(Queue* queue, int colorize, int index1, int index2);

//Function to print the queue the simple way
void print(Queue* queue);

// Function to remove an item from queue.  It decreases top by 1
void pop(Queue* queue);

// Function to sort the itens in queue by insertion method
void insertionSort(Queue* queue, int d, int first);

// pauloSort
void pauloSort(Queue* queue);

// Function to measure time in both paulo and insertion sort
// queueSize: size of the queue for printing purpouses
// mode: "paulo" for pauloSort and "insertion" for insertionSort
void timeMeasure(Queue* queue, int queueSize, char* mode);

#endif