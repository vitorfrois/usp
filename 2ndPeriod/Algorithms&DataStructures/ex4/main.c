#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "data.h"
#include "myString.h"

// Main
int main()
{
    int stackSize;
    char *entry;

    scanf("%d%*c%*c", &stackSize);
    
    Queue* queue = createQueue(stackSize);
    for(queue->n = 0; queue->n < stackSize; queue->n++){
        entry = readString();
        //printf("lerei: ");
        //printf("|%s|", entry);
        if(strcmp(entry, "ENTRA") == 0){
            //printf("entrou\n");
            push(queue);
        }else if(strcmp(entry, "SAI") == 0){
            //printf("eh pra sair\n");
            pop(queue);
        }
        free(entry);
        //ungetc(c, stdin);
    } 
    for(int i = 0; i <= (queue->top); i++)
        free(queue->people[i].name);
    
    free(queue->people);
    free(queue);

    return 0;
}