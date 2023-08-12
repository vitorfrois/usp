#include <stdio.h>

int main(){
      int nYay, nNham;
      scanf("%d %d", &nYay, &nNham);
      int peso = nNham*3 - nYay*5;
      if(peso < -30){
            printf("P");
      }else if(peso <= 0){
            printf("B");
      }else{
            printf("R");
      }
}
