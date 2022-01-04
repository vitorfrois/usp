#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"

int removeNode(List *l, Node* rem){
    int p0 = rem->data.p0;
    Node *p = l->head;
    Node *prev = NULL;
    
    while(p != NULL && p0 != p->data.p0){
        prev = p;
        p = p->next;
    }
    
    if(p == NULL){
        printf("INVALIDO\n");
        return 0;
    }
    l->size--;
    printf("%d %d\n", rem->data.p0, l->t-1);

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

Node *createNode(int p0, int t0, int tf, int r){
    Node *new = malloc(sizeof(Node));
    new->data.p0 = p0;
    new->data.t0 = t0;
    new->data.tf = tf;
    new->data.r = r;
    new->on = false;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

bool search(List *l, int p0){
    Node *aux = l->head;

    while(aux != NULL && aux->data.p0 != p0)
        aux = aux->next;

    if(aux == NULL)
        return false;
    else
        return true;    
}

void insert(List *l, int p0, int t0, int tf, int r, char mode){
    if(p0 == EOF)
        return;

    while(search(l, p0) == true)
        p0++;

    l->size++;
    //cria um novo nó a ser inserido
    Node *new = createNode(p0, t0, tf, r);

    //caso contrário, insira o nó na posição certa
    Node *aux = l->head, *prev = NULL;
    //when using the l, it should be sorted by t0
    //when in the list, should be sorted by r.
    if(mode == 't'){
        while(aux != NULL && aux->data.t0 <= new->data.t0){
            prev = aux;
            aux = aux->next;
        }
    }else if(mode == 'r'){

        while(aux != NULL && aux->data.r > new->data.r){
            prev = aux;
            aux = aux->next;
        }
        if(aux != NULL && aux->data.r == new->data.r){
            while(aux != NULL && aux->data.p0 < new->data.p0 && aux->data.r == new->data.r){
                prev = aux;
                aux = aux->next;
            }
        }
    }
    

    if(prev == NULL){
        new->next = l->head;
        if(l->head != NULL) l->head->prev = new;
        l->head = new;
    }else{
        new->next = prev->next;
        prev->next = new;
        if(new->next != NULL) new->next->prev = new;
        else l->tail = new;
        new->prev = prev;
    }
    if(l->tail == NULL){
        Node *aux = l->head;
        while(aux->next)
            aux = aux->next;
        l->tail = aux;
    }
    // printList(l, l->head);
}

List *newList(){
    List* l = malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    l->total_i = 0;
    l->t = 1;
    l->size = 0;
    //insert(l, 0, 0, 0, 0);
    return l;
}

void printNode(Node *n){
    printf("%d (tf=%d, t0=%d, p=%d) -> ", 
            n->data.p0,
            n->data.tf,
            n->data.t0,
            n->data.r
    );
}

void printList(List *l, Node* aux){
    for(int i = 0; i < l->size; i++){
        printNode(aux);
        
        if(aux->next != NULL) aux = aux->next;
        else aux = l->head;
    }
    printf("\n");
}

void run(List *waitList, bool verbose){
    List *l = newList();
    Node *aux = NULL;
    Node *insertingProcess = waitList->head;
    do{
        while(insertingProcess->data.t0 == l->t){
            insert(
                l, 
                insertingProcess->data.p0,
                insertingProcess->data.t0,
                insertingProcess->data.tf,
                insertingProcess->data.r,
                'r');
            if(verbose) printf("inserindo o nó %d\n", insertingProcess->data.p0);
            if(aux == NULL) aux = l->head;
            else if(insertingProcess->data.r >= aux->data.r){
                aux = l->tail;
                if(verbose) printf("%d != %d\n", aux->data.r, insertingProcess->data.r);
                while(aux->prev != NULL && aux->data.r <= insertingProcess->data.r){
                    if(verbose) printf("pENIS");
                    aux = aux->prev;
                }
            }

            if(insertingProcess->next != NULL) insertingProcess = insertingProcess->next;
            else break;
        }

        if(verbose) printf("\nTime = %2d - - - - - - - - - - - - - - - - - - - - - - - - - -\n", l->t);
        if(verbose) printList(l, aux);
        
        aux->data.tf--;
        l->t++;
        
        if(aux->data.tf == 0){
            Node *temp = aux;
            if(aux->next != NULL) aux = aux->next;
            else aux = l->head;
            removeNode(l, temp);
        }else{
            if(aux->next != NULL)
                aux = aux->next;
            else
                aux = l->head;
        }
    }while(l->size != 0);

    free(l);
}

void freeList(List* l){
    if(l != NULL){
        Node *aux = l->head;
        while(aux != NULL){
            l->head = l->head->next;
            free(aux);
            aux = l->head;
        }
        free(l);
    }
}