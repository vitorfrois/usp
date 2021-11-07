#include <stdio.h>

int main(){
      int size;
      scanf("%d", &size);
      int numArray[size];
      int zeros = 0;

      for(int i = 0; i < size; i++){
            scanf("%d", &numArray[i]);
            if(numArray[i] == 0){
                  zeros++;
                  //printf("zeros = %d\n", zeros);
            }
            if(numArray[i] != 0 && zeros > 0){
                  for(int sub = 1; sub < zeros+1; sub++){
                        //printf("numArray[%d] = %d\n", i - zeros*sub, numArray[i - zeros*sub]);
                        //printf("sub = %d; zeros = %d; i = %d\n", sub, zeros, i);
                        if(numArray[i - zeros - sub] != 0){
                              numArray[i - zeros - sub] = 0;
                        }else{
                              for(int m = 1; m < size; m++){
                                    //printf("numArray[%d] = %d\n", i - zeros-sub-m, numArray[i - zeros - sub - m]);
                                    if(numArray[i - zeros - sub - m] != 0){
                                          numArray[i - zeros - sub - m] = 0;
                                          break;
                                    }
                              }
                        }

                  }
                  zeros = 0;
            }
            if(numArray[i] == 0 && i == size-1){
                  //printf("penis");
                  numArray[i-1] = 0;
            }
      }

      int sum = 0;
      for(int i = 0; i < size; i++){
            //printf("numArray[%d] = %d\n", i, numArray[i]);
            sum += numArray[i];
      }
      printf("%d", sum);
      return 0;

}
