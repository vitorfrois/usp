#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

char matrix[34][66];

void matrixPrinter(char printThisMatriz[34][66], bool lastFrame){
      for(int i = 0; i < 34; i++){
            for(int j = 0; j < 66; j++){
                  if(printThisMatriz[i][j] == ' '){
                        printf("\033[0;44m");
                  }else if(printThisMatriz[i][j] == '@'){
                        printf("\033[0;37m");
                        printf("\033[0;47m");
                  }else if(printThisMatriz[i][j] == '#'){
                        printf("\033[0;36;44m");
                  }else if(printThisMatriz[i][j] == '~'){
                        printf("\033[0;31;44m");
                  }
                  printf("%c", printThisMatriz[i][j]);
                  printf("\033[0m");
            }
            printf("\n");
      }


      if(lastFrame == false){
            usleep(100000);
            printf("\033[A");
            for(int i = 0; i < 34; i++){
                  printf("\33[2K\r");
                  printf("\033[A");
            }
      }

}

void physics(){
      char copy[34][66];
      for(int i = 0; i < 34; i++){
            for(int j = 0; j < 66; j++){
                  copy[i][j] = matrix[i][j];
            }
      }

      for(int i = 1; i < 33; i++){
            for(int j = 1; j < 65; j++){
                  if(matrix[i][j] == '~'){
                        if(matrix[i+1][j] == ' '){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i + 1][j];
                              copy[i + 1][j] = tmp;
                        }else if(matrix[i+1][j-1] == ' '){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i + 1][j-1];
                              copy[i + 1][j-1] = tmp;
                        }else if(matrix[i+1][j+1] == ' '){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i + 1][j+1];
                              copy[i + 1][j+1] = tmp;
                        }else if(matrix[i][j-1] == ' '){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i][j-1];
                              copy[i][j-1] = tmp;
                        }else if(matrix[i][j+1] == ' '){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i][j+1];
                              copy[i][j+1] = tmp;
                        }
                  }

                  if(matrix[i][j] == '#'){
                        if(matrix[i+1][j] == ' ' || matrix[i+1][j] == '~'){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i + 1][j];
                              copy[i + 1][j] = tmp;
                        }else if(matrix[i+1][j-1] == ' ' || matrix[i+1][j-1] == '~'){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i + 1][j-1];
                              copy[i + 1][j-1] = tmp;
                        }else if(matrix[i+1][j+1] == ' ' || matrix[i+1][j+1] == '~'){
                              char tmp = copy[i][j];
                              copy[i][j] = copy[i + 1][j+1];
                              copy[i + 1][j+1] = tmp;
                        }
                  }
            }
      }

      for(int i = 1; i < 33; i++){
            for(int j = 1; j < 65; j++){
                  matrix[i][j] = copy[i][j];
            }

      }
}

int main(){
      int n_frames, frame, x, y;
      char nova_particula;
      bool lastFrame;
      for(int i = 0; i < 66; i++)
            matrix[0][i] = '@';
      for(int i = 0; i < 66; i++)
            matrix[33][i] = '@';
      for(int i = 1; i < 33; i++){
            matrix[i][0] = '@';
            matrix[i][65] = '@';
            for(int j = 1; j < 65; j++){
                  matrix[i][j] = ' ';
            }
      }

      scanf("%d", &n_frames);

      int contador = 0;
      while (contador < n_frames) {

              // `scanf` retorna EOF quando chega ao fim da entrada.
              int n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &nova_particula);

              // Se não há mais partículas a serem criadas, continue até o final
              // da simulação.
              if (n_lido == EOF) {
                      frame = n_frames;
              }

              // Calcula todos os frames até o próximo frame onde queremos criar
              // uma partícula.

              while (contador < frame) {
                      printf("frame: %d\n", contador + 1);
                      /* Seu código de imprimir a matrix */
                      lastFrame = (contador + 1 == n_frames)? true : false;
                      matrixPrinter(matrix, lastFrame);
                      /* Seu código de calcular a física */
                      physics();
                      contador++;
              }

              // Se há uma particula a ser criada, crie ela.
              if (n_lido != EOF) {
                      matrix[y+1][x+1] = nova_particula;
                      //printf("nova particula no frame %d -> (%d, %d)\n", contador+1, y, x);
              }
      }
}
