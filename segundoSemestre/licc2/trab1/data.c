#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "data.h"

void dataCpy(Shell* a, Shell* b){
    //printf("strlen = %ld\n", strlen(b->name));
    //a->name = malloc(sizeof(char) * (strlen(b->name) + 1));
    strcpy(a->name, b->name);
    a->size = b->size;
}
