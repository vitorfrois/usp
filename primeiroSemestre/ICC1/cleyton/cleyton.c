#include <stdio.h>

int main(){
      //read the values tape
      int valuesTape[511];
      for (int i = 0; i < 512; i++){
            scanf("%i", &valuesTape[i]);
      }

      int n = 0;
      int a, b, c;
      printf("Saida do programa:\n");
      while(n < 512){
            switch (valuesTape[n]){
                  case 0:
                        n = 512;
                        break;
                  case 1:
                        valuesTape[valuesTape[n+3]] = valuesTape[valuesTape[n+1]] + valuesTape[valuesTape[n+2]];
                        n = n + 4;
                        break;
                  case 2:
                        valuesTape[valuesTape[n+3]] = valuesTape[valuesTape[n+1]] * valuesTape[valuesTape[n+2]];
                        n = n + 4;
                        break;
                  case 3:
                        a = valuesTape[valuesTape[n+1]];
                        b = valuesTape[valuesTape[n+2]];
                        if(a < b)
                              {c = 1;}
                        else
                              {c = 0;}
                        valuesTape[valuesTape[n+3]] = c;
                        n = n + 4;
                        break;
                  case 4:
                        a = valuesTape[valuesTape[n+1]];
                        b = valuesTape[valuesTape[n+2]];
                        if(a == b)
                              {c = 1;}
                        else
                              {c = 0;}
                        valuesTape[valuesTape[n+3]] = c;
                        n = n + 4;
                        break;
                  case 5:
                        n = valuesTape[valuesTape[n+1]];
                        break;
                  case 6:
                        a = valuesTape[valuesTape[n+1]];
                        b = valuesTape[valuesTape[n+2]];
                        if(a != 0){
                              n = b;
                        }else{
                              n = n + 3;
                        }
                        break;
                  case 7:
                        valuesTape[valuesTape[n+2]] = valuesTape[valuesTape[n+1]];
                        n = n + 3;
                        break;
                  case 8:
                        a = valuesTape[valuesTape[n+1]];
                        printf("%c", a);
                        n = n + 2;
                        break;
                  case 9:
                        a = valuesTape[valuesTape[n+1]];
                        printf("%i", a);
                        n = n + 2;
                        break;
            }
      }

      printf("\nEstado final da fita:\n");
      for (int i = 0; i < 512; i++){
            printf("%i\n", valuesTape[i]);
      }

}
