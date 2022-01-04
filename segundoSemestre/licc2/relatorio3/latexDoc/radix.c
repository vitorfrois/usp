#include <stdio.h>
#include <stdlib.h>

void print(int *arr, int n){
    for(int i = 0; i < n; i++)
        printf("%d;", arr[i]);
    printf("\n");
}

void counting(int* original, int n, int exp, int base) {
    //Nao e preciso calcular min e max, pois min sera 0 e max o exp
	// 1 - cria vetor de contagem
	int contagem[base];
    for(int i = 0; i < base; i++) contagem[i] = 0; //
    int final[n];
	// Kb 
	
	// 2 - conta a frequencia de cada chave
	int i;
	for (i = 0; i < n; i++) 
		contagem[(original[i]/exp)%base]++;    // 4a
	// 4aN
    print(contagem, base);

    for(i = 1; i < base; i++)
        contagem[i] += contagem[i-1]; //K(a+b)

	// 3 - recria o vetor usando as frequencias para cada chave no vetor de contagem
    for(i = n-1; i >= 0; i--)
        final[--contagem[(original[i]/exp)%base]] = original[i]; //b + a+a+a
    //N(3a+b)
    
	for(i = 0; i < n; i++)
        original[i] = final[i];  //Na

    //Total = Kb + 4Na + Ka + Kb + N3a + Nb
    //      = N(7a+b) + K(a+2b)
    //      = N + K
}

void radixsort(int v[], int n){
    int max = v[0];
	for (int i=1; i < n; i++)
		if (v[i] > max) max = v[i]; // c+b
    //n(c+b)
    int base = n;

    for (int exp = 1; max / exp > 0; exp *= base) //log_n(c)
        counting(v, n, exp, base); //counting
    //log_n(c) * (N+K)
}


int main(){
    int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
    int n = sizeof(arr) / sizeof(arr[0]);
     
    radixsort(arr, n);
    for(int i = 0; i < n; i++)
        printf("%d;", arr[i]);
    return 0;
}