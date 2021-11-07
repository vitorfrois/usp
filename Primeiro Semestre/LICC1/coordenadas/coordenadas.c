#include <stdio.h>

int main(){
      int x = 0, y = 0;
      char commandsArray[6];
      for (int i = 0; i < 6; i++){
            scanf("%c", &commandsArray[i]);
      }
      for (int i = 0; i < 6; i++){
            switch(commandsArray[i]){
                  case 'W':
                        y++;
                        break;
                  case 'A':
                        x--;
                        break;
                  case 'S':
                        y--;
                        break;
                  case 'D':
                        x++;
                        break;
                  default:
                        printf("Valor não identificado");
                        break;
            }
      }
      printf("%d %d\n", x, y);
}
