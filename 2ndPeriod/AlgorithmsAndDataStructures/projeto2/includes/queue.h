#ifndef QUEUE_H
#define QUEUE_H

typedef struct node{
	struct node *left, *right;
	int info, prio;
}Node;

typedef struct queue{
    int top;
    int bottom;
    int size;
    int n;
    Node **elem;
}Queue;

/**
 * @brief Create a Queue object.
 * 
 * @param size size of queue.
 * @return created Queue * 
 */
Queue* createQueue(int size);

/**
 * @brief Check if queue if full.
 * 
 * @param queue 
 * @return int 1 if full; 0 if it is not full.
 */
int qIsFull(Queue* queue);
 
/**
 * @brief Check if queue is empty.
 * 
 * @param queue 
 * @return int 1 if its empty; 0 if it is not empty.
 */
int qIsEmpty(Queue* queue);

/**
 * @brief Add an item to queue end. Increases top by 1.
 * 
 * @param queue
 * @param newNode Node to be inserted
 */
void qPush(Queue* queue, Node *newNode);
 
/**
 * @brief Remove the first item of the queue. Increases bottom by 1.
 * 
 * @param queue 
 */
void qPop(Queue* queue);

#endif