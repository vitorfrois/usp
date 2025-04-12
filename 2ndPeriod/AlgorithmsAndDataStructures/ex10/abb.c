#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "abb.h"

struct no {
	no_t *esq, *dir;
	int info;
};

arvore_t *criar() {
	arvore_t *a = (arvore_t *)malloc(sizeof(arvore_t));
	a->raiz = NULL;
	return a;
}

void finalizar(no_t *raiz) {
	if(raiz != NULL) {
		finalizar(raiz->esq);
		finalizar(raiz->dir);
		free(raiz);
	}
}

void imprimir(no_t *raiz) {
	if(raiz != NULL) {
		printf("%d(", raiz->info);
		imprimir(raiz->esq);
		printf(",");
		imprimir(raiz->dir);
		printf(")");
	} else {
		printf("null");
	}
}

int inserirVetor(no_t **raiz, Input *data, int i){
	if(i == -1){
		(*raiz) = NULL;
		return 0;
	}else{
		*raiz = (no_t *)malloc(sizeof(no_t));
		(*raiz)->info = data[i].value;
		inserirVetor(&(*raiz)->esq, data, data[i].esq);
		inserirVetor(&(*raiz)->dir, data, data[i].dir);
		return 1;
	}
}

int contagem(no_t **raiz){
	if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
		// printf("nó folha. Valor = %d\n", (*raiz)->info);
		return (*raiz)->info;
	}else if((*raiz)->esq == NULL){
		return (*raiz)->dir->info;
	}else if((*raiz)->dir == NULL){
		return (*raiz)->esq->info;
	}
	
	
	int valor = contagem(&(*raiz)->esq) + contagem(&(*raiz)->dir);
	// printf("%d\n", valor);
	if(valor == (*raiz)->info) return valor;
	else return -1;
}






