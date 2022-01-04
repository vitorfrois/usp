/**
 * @file main.c
 * @author Vítor Amorim Fróis (frois@usp.br)
 * @brief Projeto 2: Árvore Heap, desenvolvido baseado nas aulas do professor Manzato 
 * @date 29-11-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/myString.h"
#include "../includes/treap.h"

//Funções usadas na main
void insercao(Treap *);
void impressao(Treap *);
void remocao(Treap *);
void buscar(Treap *);


int main(){
    char *input = "s";
    Treap *t = create();
    int iterations;
    scanf("%d\n", &iterations);
    for(int i = 0; i < iterations; i++){
        input = readString();
        if(strcmp(input, "insercao") == 0) insercao(t); 
        else if(strcmp(input, "impressao") == 0) impressao(t);
        else if(strcmp(input, "remocao") == 0) remocao(t);   
        else if(strcmp(input, "buscar") == 0) buscar(t);
        else printf("opção não encontrada\n");
        free(input);
    }
    freeTree(t->root);
    free(t);

    return 0;
}

void insercao(Treap *t){
    int info, prio;
    scanf("%d %d\n", &info, &prio);
    treapInsertion(t, info, prio);
}

void impressao(Treap *t){
    char *input = readString();
    printTree(t->root, input);
    free(input);
}
 
void remocao(Treap *t){
    int info;
    scanf("%d\n", &info);
    Node** rem = search(&t->root, info);
    if(rem != NULL){
        while((*rem)->right != NULL && (*rem)->left != NULL){
            leftRotation(rem);
            rem = &(*rem)->left;
        }
        deletion(rem, info);
    }else{
        printf("Chave nao localizada\n");
    }
}
void buscar(Treap *t){
    int info;
    scanf("%d\n", &info);
    if(search(&t->root, info) == NULL) printf("0\n");
    else printf("1\n");
}
