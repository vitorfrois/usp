#include <stdio.h>
#include <stdlib.h>

void* matrixCalloc(int x, int y, int padding){
      int** matrix = calloc(x+padding, sizeof(int*));
      for(int i = 0; i < x+padding; i++)
            matrix[i] = calloc(y+padding, sizeof(int));
      return matrix;
}

void* matrixMalloc(int x, int y, int padding){
      int** matrix = malloc((x+padding) * sizeof(int*));
      for(int i = 0; i < x+padding; i++)
            matrix[i] = malloc((y+padding) * sizeof(int));
      return matrix;
}

void matrixScanner(int x, int y, int** matrix){
      for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                  scanf("%d", &matrix[i][j]);
            }
            scanf("\n");
      }
}

void matrixPrinter(int x, int y, int** matrix){
      for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                  printf("%d ", matrix[i][j]);
            }
            printf("\n");
      }
}

void matrixFree(int x, int** matrix){
      for(int i = 0; i < x; i++){
          free(matrix[i]);
      }
      free(matrix);
}

int main(){
      int x, y;
      scanf("%d\n%d\n", &y, &x);

      int** auxMatrix = matrixMalloc(x, y, 0);
      matrixScanner(x, y, auxMatrix);

      int borderSize;
      scanf("%d", &borderSize);
      int padding = 2*borderSize;

      int** matrix = matrixCalloc(x, y, padding);

      for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                  matrix[i+borderSize][j+borderSize] = auxMatrix[i][j];
            }
      }

      matrixPrinter(x+padding, y+padding, matrix);
      printf("\n");
      matrixPrinter(x, y, auxMatrix);

      matrixFree(x+padding, matrix);
      matrixFree(x, auxMatrix);
      return 0;
}
