#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "data.h"
#include "myString.h"
#include <time.h>

// Main
int main()
{
    int queueSize;
    char *shellName;
    double shellSize;

    scanf("%d", &queueSize);
    
    Queue* queue = createQueue(queueSize);
    
    for(int i = 0; i < queueSize; i++){
        scanf("%lf ", &shellSize);
        shellName = readString();
        push(queue, shellSize, &shellName);
        free(shellName);
    }
    //print(queue);
    //timeMeasure(queue, queueSize, "paulo");

    pauloSort(queue);
    //print(queue, 0, -1, -1);
    
    for(int i = 0; i <= (queue->top); i++)
        free(queue->shell[i].name);
    
    free(queue->shell);
    free(queue);

    return 0;
}