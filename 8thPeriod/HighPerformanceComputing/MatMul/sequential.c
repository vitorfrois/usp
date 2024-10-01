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

    int new_matrix[A][C];
    for(int i = 0; i < A; i++){
        for(int k = 0; k < C; k++){
            int sum = 0;
            for(int j = 0; j < B; j++)
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