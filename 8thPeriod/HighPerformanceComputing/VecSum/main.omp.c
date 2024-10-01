#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(){
    int vector_size, seed, num_threads;
    num_threads = omp_get_num_threads();
    scanf("%d %d", &vector_size, &seed);
    srand(seed);

    int vector[vector_size];
    for (int i = 0; i < vector_size; i++)
        vector[i] = rand() % 10;
    
    int sum = 0, i;
    #pragma omp parallel for num_threads(num_threads) private(i) reduction(+:sum)
    for (i=0; i<vector_size; i++)
        sum += vector[i];
    
    printf("%d", sum);
    return 0;
}