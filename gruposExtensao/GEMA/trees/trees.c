#include <stdio.h>

int main(){
      int i, j; //i = linhas j = colunas
      scanf("%d %d \n", &i, &j);
      float treeMtx[i][j], input;
      for (int m = 0; m < i; m++){
            for(int n = 0; n < j; n++){
                  scanf("%f", &input);
                  treeMtx[m][n] = input;
            }
      }


      float newResult, result, pattern = 0;
      for (int p = 0; p < j; p++){
            for(int o = 0; o < i-1; o++){
                  newResult = treeMtx[o][p] - treeMtx[o+1][p];
                  if(o == 0)
                        result = newResult;
                  //printf("Result = %d, newResult = %d\n", result, newResult);
                  if(newResult == result && result < 2 && result > -2)
                        pattern++;
                  result = newResult;
            }
            //printf("pattern = %d\n", pattern);
            if(pattern == j-1)
                  printf("S\n");
            else
                  printf("N\n");
            pattern = 0;
      }
}
