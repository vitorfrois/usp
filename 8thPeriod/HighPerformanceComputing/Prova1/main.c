#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 2
#define T N

int main(){
	char linebreak;
	int A[N][N];
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			scanf("%d", &A[i][j]);
		}
	}

	omp_set_num_threads(T);
	int soma_colunas[N], i, j;
	#pragma omp parallel shared(soma_colunas) private(i, j)
	{
		j = omp_get_thread_num();
		soma_colunas[j] = 0;
		for(i = 0; i < N; i++)
			soma_colunas[j] += A[i][j];
	}

	printf("%d", soma_colunas[0]);
	printf("%d", soma_colunas[1]);
	
	double media = 0;
	#pragma omp parallel shared(soma_colunas)
	{
		#pragma omp for reduction(+:media)
		for(i = 0; i < N; i++){
			printf("media: %d", media);
			media += soma_colunas[i];
		}
	}

	media = media / N;

	printf("%d", media);

	return 0;
}
