#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FAIL -1
#define DEBUG 0

typedef struct {
	int key; // campo chave - ordenacao e busca
	float value1;
	char value2;
} Record;

// tipo para lista encadeada
typedef struct node {
	Record elem;
	struct node* next;
} Node;

// tipo para fila (com fim e inicio da lista)
typedef struct bucket {
	Node* begin;
	Node* end;
} Bucket;


int* gera_vetor (int tam, int min, int max);

int* gera_vetor_ordenado(int tam, int min, int max);

Record* gera_vetor_rec(int tam, int min, int max);

void mergesort (int* v, int ini, int fim);

void quicksort(int* v, int ini, int fim, int (*eep)());

void imprime_vetor(int*v, int N);

void imprime_vetor_rec(Record* v, int N);

void max_heapify(int* v, int p, int N);

void build_maxheap(int* v, int N);

void heapsort(int* v, int N);

void countingsort_rec(Record* v, int N);

void bucketsort(Record* v, int N);
