#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define T 4

int main(int argc, char *argv[]){
    int nthreads;
    scanf("%d", &nthreads);

    #pragma omp parallel num_threads(nthreads)
    {
        printf("Hello, World!\n");
    }

    return 0;
}