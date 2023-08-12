#include <stdio.h>
#include <stdlib.h>
#include "busca_e_ordenacao.h"


int main (int argc, char* argv[]) {

	if (argc < 2) {
		printf("Informe tamanho do vetor\n");
		return 1;
	}
	int n = atoi(argv[1]);

	Record* vet = gera_vetor_rec(n, 0, (int)(n/3.0));
	if (n <= 25) imprime_vetor_rec(vet, n);

	printf("Counting sort...\n");	
	countingsort_rec(vet, n);
	if (n <= 25) imprime_vetor_rec(vet, n);

	free(vet);

	
	vet = gera_vetor_rec(n, 0, (int)(n/3.0));
	if (n <= 25) imprime_vetor_rec(vet, n);
	printf("Bucketsort...\n");	
	bucketsort(vet, n);
	if (n <= 25) imprime_vetor_rec(vet, n);
	

	return 0;
}
