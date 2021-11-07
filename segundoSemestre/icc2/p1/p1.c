#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

unsigned int* search_and_count(int** matriz, int* vetor, int m, int z) {
	int i, j, k, k2, el;
	unsigned int* con = calloc(z, sizeof(unsigned int));
	for (k = 0; k < z; k++) {
	    el = vetor[k];
	    for(i = 0; i < m; i++){
		for(j = 0; j < m; j++){
		    if (matriz[i][j] == el){
			k2 = 0;
			while (k2 < z) {
			    if (vetor[k2] == el) {
				    con[k2]++;
			    }
			    k2++;
			}
		    }
		}   
	    }
	}
	return con;
}

int** alloc_matrix(int m) {
	int **mat = malloc(sizeof(int*)*m);
	srand(m);
	
	int in = 0;
	// aloca matriz ordenada
	for (int i = 0; i < m; i++) {
		mat[i] = malloc(sizeof(int)*m);
	    	for (int j = 0; j < m; j++) {
			if (i == j) in+= (rand()%3)+1;
			else in += rand()%3;
			mat[i][j] = in;
		}
	}
	// desordena matriz triangular superior
	for (int i = 0; i < m-2; i++) {
	    	for (int j = i+1; j < m-1; j++) {
			int swaps = (int)((m-j)/2.0)+1;
			for (int t = 1; t <= swaps; t++) {
				int a = (rand()%(m-j))+j;
				int b = (rand()%(m-j))+j;
				int tmp = mat[i][a];
				mat[i][a] = mat[i][b];
				mat[i][b] = tmp;
			}
		}

	}
	return mat;
}

int* alloc_vec(int z) {
	int *vet = malloc(sizeof(int)*z);
	srand(z);
	vet[0] = rand()%2;
	for (int i = 1; i < z; i++) {
		vet[i] = vet[i-1]+(rand()%9)+1;
	}
	return vet;
}


int main (int argc, char* argv[]) {

	int m;
	int z;
	scanf("%d", &m);
	scanf("%d", &z);

	int** mat = alloc_matrix(m);
	int* vet = alloc_vec(z);

	unsigned int* c = search_and_count(mat, vet, m, z);

	for (int i = 0; i < z; i++) printf("%hu ", c[i]);
	printf("\n");

	for (int i = 0; i < m; i++) free(mat[i]);
	free(mat);
	free(vet);

	return 0;
}

