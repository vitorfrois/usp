#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "data.h"

void computeCategory(People* queue){
    if(queue->isOld == 1 && queue->isSick == 1)
        queue->category = 1;
    else if(queue->isOld == 0 && queue->isSick == 1)
        queue->category = 2;
    else if(queue->isOld == 1 && queue->isSick == 0)
        queue->category = 3;
    else if(queue->isOld == 0 && queue->isSick == 0)
        queue->category = 4;
    return;
}

void dataCpy(People* a, People* b){
    //printf("strlen = %ld\n", strlen(b->name));
    //a->name = malloc(sizeof(char) * (strlen(b->name) + 1));
    strcpy(a->name, b->name);
    a->age = b->age;
    a->isOld = b->isOld;
    a->isSick = b->isSick;
    a->category = b->category;
    a->key = b->key;
}

int dataCmp(People a, People b){
    if(a.category > b.category)
        return 1;
    else if(a.category < b.category)
        return 0;
    else if(a.category == b.category){
        if(a.key > b.key)
            return 1;
        else
            return 0;
    }
    return -1;
}