#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedList.h"

List *newList(){
    List *l;
    l = (List*) malloc(sizeof(List));
    l->head = NULL;
    l->size = 0;
    return l;
}

void print(List* l) {
    if(l->head == NULL){
        printf("\n");
        return;
    }
    Node *p;

    p = l->head;
    while(p != NULL) {
        printf("%s ", p->word);
        p = p->next;
    }
    printf("\n");

}

void insert(List* l, char *word) {
    if(search(l, word) == true) return;
    Node *new = (Node *)malloc(sizeof(Node)); 
    new->prev = NULL;
    new->word = word;

    if(l->head == NULL){
        new->prev = NULL;
        l->head = new;
    }else{
        new->next = l->head;
        l->head = new;
    }
}

int removeNode(List *l, char *word){
    Node *p = l->head;
    Node *prev = NULL;
    
    while(p != NULL && strcmp(word, p->word) != 0){
        prev = p;
        p = p->next;
    }
    
    if(p == NULL){
        return 0;
    }

    l->size--;

    if(prev == NULL){
        l->head = l->head->next;
        if(l->head != NULL) l->head->prev = NULL;
        free(p);
    }else {
        if(p->next == NULL){
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

bool search(List *l, char *word){
    Node *p = l->head;
    Node *prev = NULL;
    
    while(p != NULL && strcmp(word, p->word) != 0){
        prev = p;
        p = p->next;
    }
    
    if(p == NULL)
        return false;
    else
        return true;
}

void freeList(List *l) {
	if(l != NULL) {
		Node *aux = l->head;
		while(aux != NULL) {
			l->head = aux->next;
			free(aux);
			aux = l->head;
		}
		free(l);
	}else{
        printf("uai\n");
    }
}