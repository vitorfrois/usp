/**
 * @file main.c
 * @author Vítor Amorim Fróis (frois@usp.br)
 * @brief Busca Indexada com Lista Encadeada
 * @date 05-12-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"
#include "myString.h"
enum INPUT{
    EXIT, READ, INDEX, SEARCH 
} input;

int main(){ 
    int input = -1;
    char c;
    List *l = newList();
    bool reachEOF;

    do{
        scanf("%d\n", &input);
        if(input == READ){
            //Read fileName and open it
            char *fileName = readString(stdin, &reachEOF);
            FILE *fp = fopen(fileName, "r");
            if(!fp) printf("Arquivo invalido!");
            reachEOF = false;
            while(!reachEOF)
                insert(l, readString(fp, &reachEOF));
            
            l->indexed = false;
            fclose(fp);
            free(fileName);
            printHeader(l);
        }else if(input == INDEX){
            l->index = indexIt(l);
        }else if(input == SEARCH){
            char *word = readString(stdin, &reachEOF);
            int nodesTravelled = search(l, word);
            if(nodesTravelled == -1) printf("Vetor de indices nao atualizado.\n");
            else if(nodesTravelled == -2) printf("Palavra nao existe na lista.\n");
            else printf("%d\n", nodesTravelled);
            free(word);
        }        
    }while(input != EXIT);
    freeList(l);
    return 0;
}