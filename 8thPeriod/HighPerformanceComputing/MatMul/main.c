#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>


int main(){
    int A, B, C, seed;
    scanf("%d %d %d %d", &A, &B, &C, &seed);

    srand(seed);

    int matrix1[A][B];
    int matrix2[B][C];

    for(int i = 0; i < A; i++){
        for(int j = 0; j < B; j++){
            matrix1[i][j] = rand() % 10;
        }
    }

    for(int i = 0; i < B; i++){
        for(int j = 0; j < C; j++){
            matrix2[i][j] = rand() % 10;
        }
    }

    omp_set_nested(1);
    int new_matrix[A][C];
    int i, j, k;
    #pragma omp parallel for collapse(2) private(i, k, j) num_threads(4)
    for(i = 0; i < A; i++){
        for(k = 0; k < C; k++){
            int sum = 0;
            #pragma omp parallel for reduction(+:sum) private(j) num_threads(4)
            for(j = 0; j < B; j++)
                sum += matrix1[i][j] * matrix2[j][k];
            
            new_matrix[i][k] = sum;
        }
    }

    // for(int i = 0; i < A; i++){
    //     for(int j = 0; j < C; j++){
    //         printf("%d ", new_matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    return 0;
}