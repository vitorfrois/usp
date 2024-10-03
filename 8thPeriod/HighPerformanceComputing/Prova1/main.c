#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define N 2
#define T N

int main(){
	char linebreak;
	int A[N][N];
	omp_set_num_threads(T);

	// Leitura da matriz
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &A[i][j]);
		}
	}

	// Soma das colunas
	int soma_colunas[N], i, j;
	#pragma omp parallel shared(soma_colunas) private(i, j)
	{
		j = omp_get_thread_num();
		soma_colunas[j] = 0;
		for(i = 0; i < N; i++)
			soma_colunas[j] += A[i][j];
	}
	#pragma omp barrier

	// Média da matriz
	double media = 0;
	#pragma omp parallel for reduction(+:media) private(i) num_threads(T)
	for(i = 0; i < N; i++)
		media += soma_colunas[i];
	
	media = media / (N*N);
	
	// Média dos valores da matriz
	int medial[N], soma_diferenca[N];
	double dsvpdr[N];
	#pragma omp parallel
	{
		#pragma omp single
		{
			for(j = 0; j < N; j++){
				#pragma omp task 
				{
					medial[j] = 0;
					for(i = 0; i < N; i++)
						if (A[i][j] < media) 
							medial[j] += 1;
				}
				#pragma omp task
				{
					soma_diferenca[j] = 0;
					for(i = 0; i < N; i++)
						soma_diferenca[j] += pow(A[i][j] - soma_colunas[j], 2);
					dsvpdr[j] = sqrt(soma_diferenca[j] / N);
				}
			}
		}
	}

	for(i = 0; i < N; i++)
		printf("(%d) dsvpdr = %f; medial = %d\n", i, dsvpdr[i], medial[i]);
	
	return 0;
}
