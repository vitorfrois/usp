#include <stdio.h>
#include <stdlib.h>

int main(){
	//define and read vaariables
	int n, pA, pB, q;
	scanf("%d %d", &n, &pA);
	scanf("%d %d", &pB, &q);

	//seed definition
	int semente = 0;
	scanf("%d", &semente);
	srand(semente);

	//check if its possible to multiply matrix
	if(pA != pB || semente == 0){
		printf("Valores invalidos para a multiplicacao.");
		return 0;
	}
	int p = pA;

	//definicao de matrizes
	int matrizA [n][pA];
	int matrizB [pB][q];
	
	//colocar valores aleatorios nas matrizes
	for(int iA = 0; iA < n; iA++){
		for(int jA = 0; jA < p; jA++){
			matrizA[iA][jA] = rand()%50 - 25;
		}
	}

	for(int iB = 0; iB < pB; iB++){
		for(int jB = 0; jB < q; jB++){
			matrizB[iB][jB] = rand()%50 - 25;
		}
	}
	
	//zerar a matriz C
	int matrizC [n][q];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < q; j++){
			matrizC[i][j] = 0;
		}
	}

	//calcular a multiplicacao A*B
	for(int i = 0; i < n; i++){
		for(int j = 0; j < q; j++){
			for(int k = 0; k < p; k++){
				matrizC[i][j] += (matrizA[i][k] * matrizB[k][j]);
			}
		}
	}

	//print the c matrix
	for(int i = 0; i < n; i++){
		printf("Linha %d: ", i);
		for(int j = 0; j < q; j++){
			printf("%d ", matrizC[i][j]);
		}
		printf("\n");
	}
}
