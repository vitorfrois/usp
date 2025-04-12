#include <stdio.h>
#include <stdlib.h>

#define primeLimit    10000
#define PI_primeLimit 1229

int main(){
	int crivo[primeLimit]; 
		/*
		** vetor crivo
		** 1 -> primo
		** 0 -> não é primo
		*/
	//logo de início já é possível eliminar multiplos de 2
	//maiores que 2 da lista de primes
	for (int possivelPrimo = 2; possivelPrimo < primeLimit; possivelPrimo++)
		crivo[possivelPrimo] = 1;

	int *primes = malloc(PI_primeLimit * sizeof(int));
	int posCurrentPrime = 0;

	//o código inicia com o numero 2, primeiro primo
	int currentPrime = 2;
	primes[posCurrentPrime++] = currentPrime;
	while(posCurrentPrime < PI_primeLimit) {
		//zera todos os multiplos de currentPrime do crivo, começando 
		//por 2*currentPrime
		for (int notPrime = 2 * currentPrime; notPrime < primeLimit; notPrime += currentPrime) {
			crivo[notPrime] = 0;
		}

		//incrementa o currentPrime até encontrar o proximo primo
		currentPrime++;
		while (crivo[currentPrime] == 0) currentPrime++;
		primes[posCurrentPrime++] = currentPrime;
	}

	int nInput;
	scanf("%d\n\n", &nInput);
	int toBePrintedIndex[nInput];
	for(int i = 0; i < nInput; i++){
	    scanf("%d", &toBePrintedIndex[i]);
		printf("%d ", primes[toBePrintedIndex[i] - 1]);
	}

	return 0;
}