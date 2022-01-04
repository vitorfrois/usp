#include <stdio.h>

int rotor[25];

int main(){
      for(int i = 0; i < 26; i++){
            scanf("%d", &rotor[i]);
      }

      int b = rotor[0];
      for(int i = 0; i < 25; i++){
            rotor[i] = rotor[i+1];
      }
      rotor[25] = b;

      for(int i = 0; i < 26; i++){
            printf("%d ", rotor[i]);
      }

}
