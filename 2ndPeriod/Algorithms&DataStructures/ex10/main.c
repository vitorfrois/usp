#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int main(){
    int treeSize; 
    scanf("%d", &treeSize);
    Input data[treeSize];
    for(int i = 0; i < treeSize; i++)
        scanf("%*d %d %d %d", 
            &data[i].value, 
            &data[i].esq, 
            &data[i].dir);
    
    arvore_t *a = criar();
    inserirVetor(&a->raiz, data, 0);
    // em_ordem(a->raiz);
    // printf("\n");
    if(contagem(&a->raiz) == (data[0].value)) printf("VERDADEIRO");
    else printf("FALSO");
    
    finalizar(a->raiz);
    free(a);
    return 0;
}