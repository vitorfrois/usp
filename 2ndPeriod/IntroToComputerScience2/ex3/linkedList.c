#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "linkedList.h"
#define ALPHABET_LETTERS 26

List *newList(){
    List *l = (List*) malloc(sizeof(List));
    l->index = (Node**) malloc(sizeof(Node*) * ALPHABET_LETTERS);
    l->head = NULL;
    l->tail = NULL;
    l->indexed = false;
}

void print(List* l) {
    if(l->head == NULL)
        printf("VAZIA");

    Node *p = l->head;
	
    //start from the beginning
    while(p != NULL) {
        printf("%s; ",p->word);
        p = p->next;
    }
    printf("\n");
}

void printHeader(List* l) {
    if(l->head == NULL)
        printf("VAZIA");

    Node *p = l->head;
	
    //start from the beginning
    for(int i = 0; i < 3; i++){
        printf("%s\n",p->word);
        p = p->next;
    }
}

Node **indexIt(List *l){
    //print(l);
    l->indexed = true;
    Node *aux = l->head;
    int i = 0;
    int nElem = 0;
    char currentLetter;
    while(i < ALPHABET_LETTERS && aux != NULL){
        while(((aux->word[0] - 97) != i) && i < ALPHABET_LETTERS)
            i++;
        //printf("i = %d\n", i);
        if(i >= ALPHABET_LETTERS)
            break;
        
        l->index[i] = aux;
        nElem++;
        currentLetter = aux->word[0];
        while(aux != NULL && (currentLetter == aux->word[0]))
            aux = aux->next;        
    }
    printf("%d\n", nElem);
    return l->index;
}

void insert(List* l, char* word) {
    //create a link
    Node *new = (Node*) malloc(sizeof(Node));
    new->word = word;
    new->next = NULL;
    new->prev = NULL;
	
    Node *aux, *prev;
    prev = NULL;
    aux = l->head;

    //aaabbbc
    while(aux != NULL && new->word[0] > aux->word[0]){
        prev = aux;
        aux = aux->next;
    }
    
    if(aux != NULL && (new->word == aux->word)){
        printf("INVALIDO\n");
        free(new);
        return;
    }

    if(prev == NULL){
        new->next = l->head;
        if(l->head != NULL) l->head->prev = new;
        l->head = new;
    }else {
        //  a   b   c
        new->next = prev->next;
        prev->next = new;
        if(new->next != NULL) new->next->prev = new;
        else l->tail = new;
        new->prev = prev;
    }
}

int removeItem(List *l, char *word){
    Node *p = l->head;
    Node *prev = NULL;
    
    while(p != NULL && strcmp(word, p->word) != 0){
        prev = p;
        p = p->next;
    }
    
    if(p == NULL){
        printf("INVALIDO\n");
        return 0;
    }

    if(prev == NULL){
        l->head = l->head->next;
        if(l->head != NULL) l->head->prev = NULL;
        free(p);
    }else {
        if(p->next == NULL){
            l->tail = p->next;
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

/**
 * @brief Search for word in Linked List l
 * 
 * @param l 
 * @param word 
 * @return int -1 if list isnt indexed; -2 if word wasnt found; else, return number of nodes travelled until find the word
 */
int search(List *l, char *word){
    if(l->indexed == false)
        return -1;
    

    int i = 0;
    while(i < 26){
        if((l->index[i] != NULL) && (l->index[i]->word[0] == word[0]))
            break;
        i++;
    }
    if(l->index[i] != NULL){
        Node *aux = l->index[i];
        int nodesTravelled = 0;
        while((word[0] == aux->word[0]) && aux->next != NULL){
            if(strcmp(word, aux->word) == 0)
                break;
            nodesTravelled++;
            aux = aux->next;
        }
        if(strcmp(word, aux->word) == 0) return nodesTravelled; 
        else return -2;
    }else
        return -2;
    
}

void freeList(List* l){
    if(l != NULL){
        free(l->index);
        Node *aux = l->head;
        while(aux != NULL){
            l->head = l->head->next;
            free(aux->word);
            free(aux);
            aux = l->head;
        }
        free(l);
    }
}