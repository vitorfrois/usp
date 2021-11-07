#include <stdio.h>

int rotor[3][26];
int nCicles[3] = {'\0'};

//function to move the rotor
void rotorCicle(int a){
      int b = rotor[a][0];
      for(int i = 0; i < 25; i++){
            rotor[a][i] = rotor[a][i+1];
      }
      rotor[a][25] = b;
      nCicles[a]++;
      if(nCicles[a] == 26){
            nCicles[a] = 0;
            if(a < 2)
                  rotorCicle(a+1);
      }
}

int main(){
      scanf("%*[^\r\n]s"); // ignore the entire line
      for(int j = 0; j < 3; j++){
            for(int i = 0; i < 26; i++){
                  scanf("%d", &rotor[j][i]);
            }
      }
      scanf("%*[\r\n]s"); //ignore \n
      scanf("%*[^\r\n]s");
      scanf("%*[\r\n]s");

      int character;
      //reading and decoding characters "while" loop
      while((character = getchar()) != EOF){
            if(character >= 65 && character <= 90){
                  character -= 65;
                  character = rotor[2][rotor[1][rotor[0][character]]] + 65;
                  rotorCicle(0);
                  printf("%c", character);
            }else if(character >= 97 && character <= 122){
                  character -= 97;
                  character = rotor[2][rotor[1][rotor[0][character]]] + 97;
                  rotorCicle(0);
                  printf("%c", character);
            }else{
                  printf("%c", character);
            }
      }
      return 0;
}
