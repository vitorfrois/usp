#include <stdio.h>

int main (){
      float n, result;
      int exp;
      scanf("%f %d", &n, &exp);
      //printf("%f %d", n, exp);
      result = n;
      if(exp > 0){
            for(int i = 1; i < exp; i++){
                  result = result * n;
            }
      }else if(exp == 0){
            result = 1;
      }else{
            for(int i = -1; i > exp; i--){
                  result = result * n;
            }
            //printf("\n%2.f\n", result);
            result = 1/result;
      }
      printf("%.0f", result);


}
