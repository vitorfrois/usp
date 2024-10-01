#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
    long vector_size;
    scanf("%ld", &vector_size);

    long *vector = (long*) malloc(vector_size * sizeof(long));

    for(long i = 0; i < vector_size; i++)
        vector[i] = i;
    vector[(long) (vector_size/2)] = vector_size;

    int num_threads = 16;
    long reductedVector[num_threads];
    long block_size = (long) vector_size / num_threads;
    long j, max_value = vector[0];
    // clock_t start = clock();
    #pragma omp parallel private(j, max_value) num_threads(num_threads)
    {   
        int thread_num = omp_get_thread_num();
        long begin = (long) (thread_num * block_size);
        long end;
        if (thread_num + 1 != num_threads)
            end = (long) ((thread_num + 1) * block_size);
        else
            end = vector_size;

        max_value = vector[begin];
        for (long j = begin; j < end; j++)
            max_value = max_value > vector[j]? max_value : vector[j];

        reductedVector[thread_num] = max_value;
    }
    #pragma omp barrier

    max_value = 0;
    int i;
    #pragma omp parallel for num_threads(4) private(i) reduction(max:max_value)
    for(i = 0; i < vector_size; i++)
        max_value = max_value > vector[i]? max_value : vector[i];

    printf("%d", max_value);
    return 0;
}