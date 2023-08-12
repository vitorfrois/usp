/* 
 *	Counting sort original
 *	Counting sort com registros <- 
 *
 *	* limitacoes:
 *		- natural para inteiros
 *		- faz mais sentido quando há repetição das chaves
 *		- faz mais sentido quando o intervalo das chaves (K): K <= tamanho
 *
 *	O(k,n)
 *
 *
 *	Moacir A Ponti - 2021
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct rec {
	int chave;
	float valor;
	char letra;
} Registro;

void print(int *arr, int tamanho){
    for(int i = 0; i < tamanho; i++)
        printf("%d;", arr[i]);
    printf("\n");
}

void countingsort(int* v, int tamanho) {
	// 0 - encontrar chaves min e max
	int final[tamanho];
	int max, min, i;
	max = min = v[0];
	for (int i=1; i < tamanho; i++) { 
		if (v[i] > max) max = v[i]; // c+b
		if (v[i] < min) min = v[i]; // c+b
	}
	//N(2b+2c) 

	// 1 - cria vetor de contagem
	int tamContagem = max-min+1; 
	int *contagem = (int*) calloc(tamContagem, sizeof(int));
	// Kb 
	
	// 2 - conta a frequencia de cada chave
	for (i = 0; i < tamanho; i++) 
		contagem[v[i]-min]++;  // a + a
	// 2aN

	contagem[0] = 0;
	for(i = 1; i < tamContagem; i++)
		contagem[i] += contagem[i-1]; //a + b
	//K(a+b)

	// 3 - recria o vetor usando as frequencias
	// para cada chave no vetor de contagem
	for(i = 0; i < tamanho; i++)
		final[contagem[v[i]-min]++] = v[i]; //a+a+b
	//(2a+b)

	for(i = 0; i < tamanho; i++)
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
