#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
    int N;
    scanf("%d", &N);

    int sum = 0;
    #pragma omp parallel for num_threads(10)
    for (int i = 2; i < N; i++){
        int intern_summation = 1;
        for (int j = 2; j < i; j++){
            if (i % j == 0){
                intern_summation += j;
            }
        }
        
        if (intern_summation == i){
            #pragma omp critical
            sum += intern_summation;
        }
    }
    printf("%d", sum);
    return 0;
}