#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int data;
    struct NODE* next;
} node;

void printList(node* head) {
   node *ptr = head;
	
   //start from the beginning
   while(ptr != NULL) {
      printf("%d ",ptr->data);
      ptr = ptr->next;
   }
   printf("\n");
}

void insert(node** head, int data) {
    //create a link
    node *new = (node*) malloc(sizeof(node));

    new->data = data;
    new->next = NULL;
	
    //point it to old first node
    if(*head == NULL){
        *head = new;
        return;
    }
    node* aux = *head;
    while(aux->next != NULL)
        aux = aux->next;
    
    aux->next = new;
}

void girosflin(node** head, int rotations){
    for(int i = 0; i < rotations; i++){
        if(*head == NULL)
            return;

        node* aux = *head;
        while(aux->next->next != NULL)
            aux = aux->next;

        aux->next->next = *head;
        *head = aux->next;

        aux->next = NULL;
    }
}

