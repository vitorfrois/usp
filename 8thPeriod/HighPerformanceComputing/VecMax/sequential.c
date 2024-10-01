#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// typedef long long unsigned int int;

int main(){
    long vector_size;
    scanf("%ld", &vector_size);

    long *vector = (long*) malloc(vector_size * sizeof(long));
    for(int i = 0; i < vector_size; i++)
        vector[i] = i;
    vector[(long) (vector_size/2)] = vector_size;

    long max_value = vector[0];

    long num_threads = omp_get_num_threads();
    long i = 0;
    #pragma omp parallel for num_threads(4) private(i) reduction(max:max_value)
    for(i = 0; i < vector_size; i++)
        max_value = max_value > vector[i]? max_value : vector[i];

    printf("%ld", max_value);
    free(vector);
    return 0;
}