#ifndef ABB_H
#define ABB_H
typedef struct no no_t;

typedef struct arvore {
	no_t *raiz;
} arvore_t;

typedef struct input{
	int value, esq, dir;
} Input;

arvore_t *criar();
void finalizar(no_t *raiz);
void imprimir(no_t *raiz);
int inserirVetor(no_t **raiz, Input *data, int i);
int contagem(no_t ** raiz);
#endif