#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/queue.h"

Queue* createQueue(int size){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = size;
    queue->top = -1;
    queue->bottom = 0;
    queue->elem = (Node**)malloc(queue->size * sizeof(Node*));
    return queue;
}
 
int qIsFull(Queue* queue){
    return queue->top == queue->size - 1;
}
 
int qIsEmpty(Queue* queue){
    return (queue->top - queue->bottom) < 0;
}

void qPush(Queue* queue, Node *newNode){
    if (qIsFull(queue))
        return;
    queue->top++;
    queue->elem[queue->top] = newNode;
}

void qPop(Queue* q){
    if (qIsEmpty(q)) return;
    
    printf("(%d, %d) ", q->elem[q->bottom]->info, q->elem[q->bottom]->prio);
    if(q->elem[q->bottom]->left != NULL) qPush(q, q->elem[q->bottom]->left);
    if(q->elem[q->bottom]->right != NULL) qPush(q, q->elem[q->bottom]->right);
    q->bottom++;
    return;
}
