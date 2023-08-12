#include <stdio.h>

void changeCalculator(int i, int coins[], int divider, int change, int* dividerReturn, int* changeReturn);

int main(){
      int coins[6];
      int change;
      scanf("%d", &change);
      int divider = 100;
      for(int i = 0; i < 6; i++){
            changeCalculator(i, coins, divider, change, &divider, &change);
      }
      printf("O valor consiste em %d moedas de 1 real\n", coins[0]);
      printf("O valor consiste em %d moedas de 50 centavos\n", coins[1]);
      printf("O valor consiste em %d moedas de 25 centavos\n", coins[2]);
      printf("O valor consiste em %d moedas de 10 centavos\n", coins[3]);
      printf("O valor consiste em %d moedas de 5 centavos\n", coins[4]);
      printf("O valor consiste em %d moedas de 1 centavo\n", coins[5]);
      return 0;
}

void changeCalculator(int i, int coins[], int divider, int change, int* dividerReturn, int* changeReturn){
      coins[i] = change/divider;
      *changeReturn -= coins[i] * divider;
      if (i == 0) *dividerReturn = 50;
      if (i == 1) *dividerReturn = 25;
      if (i == 2) *dividerReturn = 10;
      if (i == 3) *dividerReturn = 5;
      if (i == 4) *dividerReturn = 1;
}
