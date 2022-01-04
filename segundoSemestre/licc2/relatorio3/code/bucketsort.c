#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int elem;
	struct node *next;
} Node;

typedef struct bucket {
	Node *begin;
	Node *end;
} Bucket; 

void bucketsort(int *v, int N) {
	int i;

	// aritmetica -a
	// atribuicao -b
	// comparacao -c

	// 1- encontra min e max
	int max, min;
	max = min = v[0];
	for (int i=1; i < N; i++) {
		if (v[i] > max) max = v[i]; // c+b
		if (v[i] < min) min = v[i]; // c+b
	}
    printf("min=%d;max=%d\n", min, max);

	// (2c+2b)N

	// 2- criar um vetor auxiliar contendo listas (buckets)
	//    cada bucket possui um ponteiro para o inicio e outro
	//    para o fim da lista
	int tam_c = max-min+1; 
	Bucket *B = (Bucket *) calloc(tam_c, sizeof(Bucket));	
	// Kb 

	// 3 - preenche os buckets com as chaves do vetor
	//     de entrada
	for (i = 0; i < N; i++) { //(c+a)
		int key = v[i]-1; //b
		Node *newnode = malloc(sizeof(Node));
		newnode->elem = v[i]; //b
		newnode->next = NULL; //b
		//3a

		if (B[key].begin == NULL) //c
			B[key].begin = newnode; //b
		else 
			(B[key].end)->next = newnode; //b

		B[key].end = newnode; //b
		//3b+c+2b+a+c
	}
	//N(a+5b+2c)

	// 4 - percorre cada bucket, removendo os elementos
	//     do inicio da fila e inserindo na posicao correta
	int j; // percorre buckets
	i = 0; // percorre vetor de entrada //b
	for (j = 0; j < tam_c; j++) { //a+c
		Node *pos;
		pos = B[j].begin; //b
		while (pos != NULL) { //c
			v[i] = pos->elem; //b
			i++; //a+b
			Node *del = pos; //b
			pos = pos->next; //b
			B[j].begin = pos; //b
			free(del); 
		}
	}
	//(N+K)(a+5b+2c) 

	// (2c+2b)N
	// Kb 
	//N(a+5b+2c)
	//(N+K)(a+5b+2c) 
	//total = 2Nc + 2Nb + Kb + Na + 5Nb + 2Nc + Na + 5Nb + 2Nc + Ka + 5Kb + 2Kc
	//		= 6Nc + 12Nb + 6Kb + 2Na + Ka + 2Kc
	// 		= N(2a+12b+6c) + K(a+6b+2c)
	//		= N + K
	free(B);
}

int main(int argc, char*argv[]) {

	int A[] = {1,2,3,3,3,3,3,3,2,2,2,1,2,1,2,1,2,3,1,2,1,3,1,2,1};
 	int N = 25;

	bucketsort(A, N);

	int i;
	for (i = 0; i < N; i++) {
		printf("%d,", A[i]);
	}
	printf("\n\n");

	return 0;
}
