/**
 * @file main.c
 * @author Vítor Amorim Fróis (frois@usp.br)
 * @brief Binary Search Tree (BST) desenvolvido baseado nas aulas do professor Manzato 
 * @date 29-11-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myString.h"
#include "abb.h"


int main(){
    char *input = "s";
    int reachEOF = 0;
    BST *a = create();
    while(reachEOF == 0){
        input = readString(&reachEOF);
        if(strcmp(input, "insercao") == 0){
            int number;
            scanf("%d\n", &number);
            insert(&a->root, number);
        }else if(strcmp(input, "impressao") == 0){
            free(input);
            input = readString(&reachEOF);
            printTree(a->root, input);
        }
        else
            printf("opção não encontrada\n");
            free(input);
    }
    freeTree(a->root);
    free(a);

    return 0;
}