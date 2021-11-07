#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main(){
    int iterations, listSize, rotations, newItem;
    scanf("%d\n", &iterations);
    for(int i = 0; i < iterations; i++){
        node *head = NULL;
        scanf("%d\n%d", &listSize, &rotations);
        for(int j = 0; j < listSize; j++){
            scanf("%d", &newItem);
            insert(&head, newItem);
        }
        //scanf("\n\n");
        girosflin(&head, rotations);
        printList(head);
        free(head);
    }
    return 0;
}   
