#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"


List *newList(){
    List *l;
    l = (List*) malloc(sizeof(List));
    l->first = NULL;
    l->last = NULL;
}

void print(List* l) {
    if(l->first == NULL)
        printf("VAZIA");

    Node *p = l->first;
	
    //start from the beginning
    while(p != NULL) {
        printf("%d, %s; ",p->data.id, p->data.name);
        p = p->next;
    }
    printf("\n");
}

void insert(List* l, int id, char* name) {
    //create a link
    Node *new = (Node*) malloc(sizeof(Node));

    new->data.id = id;
    new->data.name = name;
    new->next = NULL;
    new->prev = NULL;
	
    Node *aux, *prev;
    prev = NULL;
    aux = l->first;

    while(aux != NULL && new->data.id > aux->data.id){
        prev = aux;
        aux = aux->next;
    }
    
    if(aux != NULL && (new->data.id == aux->data.id)){
        printf("INVALIDO\n");
        free(new);
        return;
    }

    if(prev == NULL){
        new->next = l->first;
        if(l->first != NULL) l->first->prev = new;
        l->first = new;
    }else {
        new->next = prev->next;
        prev->next = new;
        if(new->next != NULL) new->next->prev = new;
        else l->last = new;
        new->prev = prev;
    }
}

int removeItem(List *l, int id){
    Node *p = l->first;
    Node *prev = NULL;
    
    while(p != NULL && id != p->data.id){
        prev = p;
        p = p->next;
    }
    
    if(p == NULL){
        printf("INVALIDO\n");
        return 0;
    }

    if(prev == NULL){
        l->first = l->first->next;
        if(l->first != NULL) l->first->prev = NULL;
        free(p);
    }else {
        if(p->next == NULL){
            l->last = p->next;
            prev->next = NULL;
            free(p);
        }else{
            prev->next = p->next;
            p->next->prev = prev;
            free(p);
        }
    }
    return 1;
}

void freeList(List* l){
    if(l != NULL){
        Node *aux = l->first;
        while(aux != NULL){
            l->first = l->first->next;
            free(aux);
            aux = l->first;
        }
        free(l);
    }
}