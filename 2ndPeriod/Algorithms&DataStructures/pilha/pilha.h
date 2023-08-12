#define TamPilha 100

typedef int elem;
typedef struct pilha pilha_t;

pilha_t *create();
void destroy(pilha_t *p);
int isFull(pilha_t *p); 
int isEmpty(pilha_t *p);
int push(pilha_t *p, elem x);
int pop(pilha_t *p, elem *x);
int top(pilha_t *p, elem *x);
