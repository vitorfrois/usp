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

void bucketsort(int *v, int n) {
	// 1- encontra min e max
	int max, min, i;
	max = min = v[0];
	for (int i=1; i < n; i++) {
		if (v[i] > max) max = v[i]; // c+b
		if (v[i] < min) min = v[i]; // c+b
	}
	// (2c+2b)n

	// 2- criar um vetor auxiliar contendo listas (buckets)
	//    cada bucket possui um ponteiro para o inicio e outro
	//    para o fim da lista
	int k = max-min+1; 
	Bucket *B = (Bucket *) calloc(k, sizeof(Bucket));	
	for(int i = 0; i < k; i++)
		B[i].begin = NULL;
	// Kb 

	// 3 - preenche os buckets com as chaves do vetor
	//     de entrada
	for (i = 0; i < n; i++) { //(c+a)
		int key = v[i]; //b
		Node *newnode = malloc(sizeof(Node));
		newnode->elem = v[i]; //b
		newnode->next = NULL; //b
		//3a

		if (B[key].begin == NULL) B[key].begin = newnode; //b
		else (B[key].end)->next = newnode; //b

		B[key].end = newnode; //b
		//3b+c+2b+a+c
	}
	//n(a+5b+2c)

	// 4 - percorre cada bucket, removendo os elementos do inicio da fila e inserindo na posicao correta
	int j; // percorre buckets
	i = 0; // percorre vetor de entrada //b
	for (j = 0; j < k; j++) { //a+c
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
	//(n+K)(a+5b+2c) 
	
	//total = 2Nc + 2Nb + Kb + Na + 5Nb + 2Nc + Na + 5Nb + 2Nc + Ka + 5Kb + 2Kc
	//		= 6Nc + 12Nb + 6Kb + 2Na + Ka + 2Kc
	// 		= n(2a+12b+6c) + K(a+6b+2c)
	//		= n + K
	free(B);
}

int main(int argc, char*argv[]) {

	int A[] = {1,2,3,3,3,3,3,3,2,2,2,1,2,1,2,1,2,3,1,2,1,3,1,2,1};
 	int n = 25;

	bucketsort(A, n);

	int i;
	for (i = 0; i < n; i++) {
		printf("%d,", A[i]);
	}
	printf("\n\n");

	return 0;
}
