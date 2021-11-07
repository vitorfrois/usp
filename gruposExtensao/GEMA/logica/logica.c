#include <stdio.h>

int main(){
      int numberCards, inputN;
      int evenCount = 0;
      int oddCount = 0;
      int feijoada = 0;
      scanf("%d", &numberCards);
      int positiveNumbers[numberCards];
      int negativeNumbers[numberCards];
      for(int i = 0; i < numberCards; i++){
            scanf("%d", &inputN);
            if(inputN > 0){
                  inputN % 2 == 0? evenCount++ : feijoada++;
            }else{
                  inputN % 2 != 0? oddCount++ : feijoada++;
            }
      }
      evenCount > 0 && oddCount > 0? printf("%d", 2) :
      printf("%d", numberCards); 
}
