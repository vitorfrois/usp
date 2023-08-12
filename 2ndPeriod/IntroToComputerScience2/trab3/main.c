/**
 * @file main.c
 * @author Vítor Amorim Fróis (frois@usp.br)
 * @brief O SEP criado utiliza uma waitList ordenada via t0 e uma lista de processos pseudo-cíclica 
 *        ordenada via prioridade (em ordem descendente), para rodar os processos
 * @date 30-11-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"

int main(){
    int p, t0, tf, r;
    List *waitList = newList();
    bool verbose = false;
    if(verbose) printf("process   p0 t0 tf r\n");
    while(scanf("%d %d %d %d", &p, &t0, &tf, &r) != EOF){
        insert(waitList, p, t0, tf, r, 't');
        if(verbose) printf("just read %d %d %d %d\n", p, t0, tf, r);
    } 
    if(verbose) printf("just exited main while\n");
    run(waitList, verbose);
    freeList(waitList);

    return 0;
}
