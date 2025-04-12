#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

int main(){
    char c;    
    node *head = NULL;
    while((c = getchar()) != EOF){
        //printf("string = |%c|\n", c);
        if(c == '\n'){
            if(isEmpty(head) == 1)
                printf("BALANCEADO\n");
            else
                printf("NÃO BALANCEADO\n");
            head = NULL;
        }
        else
            insert(&head, c);
        //printList(head);
    }
    if(isEmpty(head) == 1)
        printf("BALANCEADO\n");
    else
        printf("NÃO BALANCEADO\n");
    
    return 0;
}
