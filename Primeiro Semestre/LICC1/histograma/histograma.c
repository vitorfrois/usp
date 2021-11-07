#include <stdio.h>
#include <string.h>

int main(){
      int size = 25;
      int histArray[size-1];
      int colorArray[4] = {'\0'};

      for (int i = 0; i < size; i++){
            scanf("%i", &histArray[i]);
            colorArray[histArray[i]]++;
      }

      int maxValue = 0, maxValueAdress = 0;
      for (int i = 0; i < 5; i++){
            if(maxValue < colorArray[i]){
                  maxValueAdress = i;
                  maxValue = colorArray[i];
            }
            maxValue < colorArray[i]? maxValue = i : maxValue;
            printf("%d: |", i);
            for(int j = 0; j < colorArray[i]; j++){
                  printf("#");
            }
            printf("\n");
      }

      for(int i = 0; i < size; i++){
            if(histArray[i] == maxValueAdress){
                  printf("%d\n", i);
            }
      }

      return 0;
}
