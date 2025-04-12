#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void printList(node* head) {
    node *ptr = head;
    printf("|");
    //start from the beginning
    while(ptr != NULL) {
        printf("%c",ptr->data);
        ptr = ptr->next;
    }
    printf("|\n");
}

int isEmpty(node *head) {
   return head == NULL;
}

int checkCondition(char a, char b){
    return  (a == '[' && b == ']') ||
            (a == '(' && b == ')') ||
            (a == '{' && b == '}') ||
            (a == '"' && b == '"');
}

void insert(node** head, char data) {
    if(data == ' ' || data == '\n' || data == EOF || data == '\r')
        return;

    node *new = (node*) malloc(sizeof(node));

    new->data = data;
    new->next = NULL;
	
    //point it to old first node
    if(*head == NULL){
        *head = new;
        return;
    }
    node* aux = *head;
    
    if(aux->next == NULL){
        if(checkCondition(aux->data, data)){
            free(aux->next);
            free(aux);
            free(new);
            *head = NULL;
        }

        aux->next = new;
        return;
    }


    while(aux->next->next != NULL)
        aux = aux->next;

    // aux | next | NULL
    //
    int condition = checkCondition(aux->next->data, new->data);

    if(condition){
        free(aux->next->next);
        aux->next = NULL;
        free(new);
    }else{
        aux->next->next = new;
    }
}

