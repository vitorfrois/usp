#include <stdio.h>
#define capValue 32767

void media(double numArray[]){
      double sum = 0;
      for(int i = 0; i < 10; i++){
            sum += numArray[i];
      }
      double result = sum/10;
      printf("%.2lf ", result);
}

void moda(double numArray[]){
      int modaArray[capValue] = {'\0'};
      int mostFrequent = 0, mostFrequentFrequency = 0;
      for(int i = 0; i < 10; i++){
            modaArray[(int)numArray[i]]++;
            if(modaArray[(int)numArray[i]] > mostFrequentFrequency){
                  mostFrequent = (int)numArray[i];
                  mostFrequentFrequency = modaArray[(int)numArray[i]];
            }
      }
      printf("%d ", mostFrequent);
}

void biggest(double numArray[]){
      int biggestNum = -capValue;
      for(int i = 0; i < 10; i++){
            numArray[i] > biggestNum?
                  biggestNum = numArray[i]:
                  biggestNum;
      }
      printf("%d ", biggestNum);
}

void smallest(double numArray[]){
      int smallestNum = capValue;
      for(int i = 0; i < 10; i++){
            numArray[i] < smallestNum?
                  smallestNum = numArray[i]:
                  smallestNum;
      }
      printf("%d ", smallestNum);
}

int main (){
      double numArray[10];
      for(int i = 0; i < 10; i++){
            scanf("%lf", &numArray[i]);
      }
      biggest(numArray);
      smallest(numArray);
      media(numArray);
      moda(numArray);
}
