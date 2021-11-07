#include <stdio.h>

int main(){
      int i, j, scanned;
      scanf("%d %d", &i, &j);
      int treeMtx[i][j] = {0}
      for (int m = 0; m < i; m++){
            for(int n = 0; n < j; n++){
                  scanf("%d ", &scanned);
                  treeMtx[m][n] = scanned;
            }
            printf("\n");
      }

      for (int m = 0; m < i; m++){
            for(int n = 0; n < j; n++){
                  printf("%d ", treeMtx[m][n]);
            }
            printf("\n");
      }
}
