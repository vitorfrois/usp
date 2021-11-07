#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

void matrixPrinter(int x, int y, char** matrix, int padding){
    for(int i = padding; i < x+padding; i++){
        for(int j = padding; j < y+padding; j++){
            if(matrix[i][j] != '.' && matrix[i][j] != '*' && matrix[i][j] != 'X'){
                printf("%d", matrix[i][j]);
            }else{
                printf("%c", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void matrixFree(int heigth, char** matrix){
      for(int i = 0; i < heigth; i++){
          free(matrix[i]);
      }
      free(matrix);
}

void* mallocAndFill(char** matrix, int heigth, int lenght, int padding){
    char** paddedMatrix = malloc((heigth+padding) * sizeof(char*));
    for(int i = 0; i < heigth+padding; i++)
        paddedMatrix[i] = malloc((lenght+padding) * sizeof(char));

    for(int i = 0; i < heigth+padding; i++){
        for(int j = 0; j < lenght+padding; j++){
            paddedMatrix[i][j] = '.';
        }
    }

    for(int i = 0; i < heigth; i++){
        for(int j = 0; j < lenght; j++){
                paddedMatrix[i+1][j+1] = matrix[i][j];
        }
    }
    
    return paddedMatrix;
}