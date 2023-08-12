#include <stdio.h>
#include <stdlib.h>

void print(int *arr, int n){
    for(int i = 0; i < n; i++)
        printf("%d;", arr[i]);
    printf("\n");
}

void countingsort(int* v, int n) {
	// 0 - encontrar chaves min e max
	int final[n];
	int max, min, i;
	max = min = v[0];
	for (int i=1; i < n; i++) { 
		if (v[i] > max) max = v[i]; // c+b
		if (v[i] < min) min = v[i]; // c+b
	}
	//N(2b+2c) 

	// 1 - cria vetor de contagem
	int k = max-min+1; 
	int *contagem = (int*) calloc(k, sizeof(int));
	// Kb 
	
	// 2 - conta a frequencia de cada chave
	for (i = 0; i < n; i++) 
		contagem[v[i]-min]++;  // a + a
	// 2aN

	contagem[0] = 0;
	for(i = 1; i < k; i++)
		contagem[i] += contagem[i-1]; //a + b
	//K(a+b)

	// 3 - recria o vetor usando as frequencias para cada chave no vetor de contagem
	for(i = 0; i < n; i++)
		final[contagem[v[i]-min]++] = v[i]; //a+a+b
	//(2a+b)

	for(i = 0; i < n; i++)
        v[i] = final[i]; //b
	//Nb

	// total = 2cN+2bN+Kb+2aN+aK+bK+2aN+bN+bN
	//       = 4Na + 4Nb + 2Nc + Ka + 2Kb 
	//       = 10N + 3K
	free(contagem);
}

int main() {

	int arr[] = { 17, 45, 75, 90, 28, 24, 2, 66 };
    int n = sizeof(arr) / sizeof(arr[0]);

	countingsort(arr, n);

	printf("Ordenado: ");
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;

}
