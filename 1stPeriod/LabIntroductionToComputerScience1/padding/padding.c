#include <stdio.h>
#include <stdlib.h>

int main(){
      int y = 0, x = 0;
      scanf("%d\n%d\n", &x, &y);

      int** matrix = calloc(x, sizeof(int*));
      for(int i = 0; i < x; i++){
            matrix[i] = calloc(y, sizeof(int));
      }

      int** auxMatrix = malloc(sizeof(int*) * x);
      for(int i = 0; i < x; i++){
            auxMatrix[i] = malloc(sizeof(int) * y);
      }

      for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                  scanf("%d", &auxMatrix[i][j]);
            }
            scanf("\n");
      };

      int borderSize = 0;
      scanf("%d", &borderSize);

      matrix = realloc(matrix, sizeof(int*) * (x+borderSize*2));
      for(int i = 0; i < x+borderSize*2; i++){
          matrix[i] = realloc(matrix[i], sizeof(int) * (y+borderSize*2));
      }

      for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                  matrix[i+borderSize][j+borderSize] = auxMatrix[i][j];
            }
      }

      for(int i = 0; i < x+borderSize*2; i++){
            for(int j = 0; j < y+borderSize*2; j++){
                  printf("%d ", matrix[i][j]);
            }
            printf("\n");
      }

      printf("\n");

      for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                  printf("%d ", auxMatrix[i][j]);
            }
            printf("\n");
      }

      for(int i = 0; i < x+borderSize*2; i++){
          free(matrix[i]);
      }
      free(matrix);

      for(int i = 0; i < x; i++){
          free(auxMatrix[i]);
      }
      free(auxMatrix);
      return 0;
}
