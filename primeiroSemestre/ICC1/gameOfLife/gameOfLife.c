#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int a = 2;
//a variavel a define o tamanho da borda da matriz, usada para tornar
//a simulação circular

int neumann(int i, int j, int height, int length, char matrix[height+(a*2)][length+(a*2)]){
      int nbhd = 0;
      matrix[i+1][j] == 'x'? nbhd += 1 : nbhd;
      matrix[i+2][j] == 'x'? nbhd += 1 : nbhd;
      matrix[i][j+1] == 'x'? nbhd += 1 : nbhd;
      matrix[i][j+2] == 'x'? nbhd += 1 : nbhd;
      matrix[i][j-1] == 'x'? nbhd += 1 : nbhd;
      matrix[i][j-2] == 'x'? nbhd += 1 : nbhd;
      matrix[i-1][j] == 'x'? nbhd += 1 : nbhd;
      matrix[i-2][j] == 'x'? nbhd += 1 : nbhd;
      return nbhd;
}

int moore(int i, int j, int height, int length, char matrix[height+(a*2)][length+(a*2)]){
      int nbhd = 0;
      matrix[i+1][j+1] == 'x'? nbhd += 1 : nbhd;
      matrix[i+1][j] == 'x'? nbhd += 1 : nbhd;
      matrix[i+1][j-1] == 'x'? nbhd += 1 : nbhd;
      matrix[i][j+1] == 'x'? nbhd += 1 : nbhd;
      matrix[i][j-1] == 'x'? nbhd += 1 : nbhd;
      matrix[i-1][j+1] == 'x'? nbhd += 1 : nbhd;
      matrix[i-1][j] == 'x'? nbhd += 1 : nbhd;
      matrix[i-1][j-1] == 'x'? nbhd += 1 : nbhd;
      return nbhd;
}

void matrixPrinter(int height, int length, char matrix[height+(2*a)][length+(2*a)]){
      for(int i = a; i < height+a; i++){
            for(int j = a; j < length+a; j++){
                  if(matrix[i][j] == '.'){
                        printf("\033[0;30;40m");
                  }else{
                        int r = rand()%7;
                        printf("\033[0;%d;%dm", 31+r, 41+r);
                  }
                  printf("%c", matrix[i][j]);
                  printf("%c", matrix[i][j]);
                  printf("\033[0m");
            }
            printf("\n");
      }
      usleep(100000);
      system("clear");
}

void physics(int height, int length, bool mooreBool, char matrix[height+(a*2)][length+(a*2)]){
      char copy[height+(a*2)][length+(a*2)];

      for(int i = 0; i < height+(2*a); i++){
            for(int j = 0; j < length+(2*a); j++){
                  copy[i][j] = matrix[i][j];
            }
      }

      int nbhd;
      for(int i = a; i < height+a; i++){
            for(int j = a; j < length+a; j++){
                  if(mooreBool == true)
                        nbhd = moore(i, j, height, length, matrix);
                  else
                        nbhd = neumann(i, j, height, length, matrix);

                  if(matrix[i][j] == 'x')
                        if(nbhd < 2 || nbhd > 3)
                              copy[i][j] = '.';

                  if(matrix[i][j] == '.' && nbhd == 3)
                        copy[i][j] = 'x';
            }
      }

      for(int i = 0; i < height+(2*a); i++){
            for(int j = 0; j < length+(2*a); j++){
                  matrix[i][j] = copy[i][j];
            }
      }
      matrixPrinter(height, length, matrix);
}

void borders(int height, int length, char matrix[height+(2*a)][length+(2*a)]){
      for(int i = a; i < height+a; i++){
            matrix[i][0] = matrix[i][length];
            matrix[i][1] = matrix[i][length+1];
            matrix[i][length+(2*a)-1] = matrix[i][3];
            matrix[i][length+(2*a)-2] = matrix[i][2];
      }

      for(int j = a; j < length+a; j++){
            matrix[0][j] = matrix[height][j];
            matrix[1][j] = matrix[height+1][j];
            matrix[height+(2*a)-1][j] = matrix[3][j];
            matrix[height+(2*a)-2][j] = matrix[2][j];
      }
      matrix[height+(2*a)-2][length+(2*a)-2] = matrix[2][2];
      matrix[1][length+(2*a)-2] = matrix[height+(2*a)-3][2];
      matrix[height+(2*a)-2][1] = matrix[2][length+(2*a)-3];
      matrix[1][1] = matrix[height+(2*a)-3][length+(2*a)-3];
}



void checkError(char mode, char checkThis){
      bool error;
      if(checkThis != '.' && checkThis != 'x')
            error = true;
      if(mode != 'M' && mode != 'N')
            error = true;
      if(error == true){
            printf("Dados de entrada apresentam erro.");
            exit(0);
      }
}

int main(){
      int nFrames;
      int height, length;
      bool mooreBool; //(neumann or moore)
      scanf("%d %d\n", &height, &length);

      char matrix[height+(a*2)][length+(a*2)];
      scanf("%d\n", &nFrames);
      char tmp, mode;
      scanf("%c\n", &mode);
      mode == 'M'? mooreBool = true : false;

      for(int i = a; i < height+a; i++){
            for(int j = a; j < length+a; j++){
                  scanf("%c", &matrix[i][j]);
            }
            scanf("%c", &tmp);
      }

      checkError(mode, matrix[2][2]);

      borders(height, length, matrix);

      for(int x = 0; x < 10000; x++){
            //printf("frame %d\n", x+1);
            physics(height, length, mooreBool, matrix);
            borders(height, length, matrix);
      }
      matrixPrinter(height, length, matrix);
      return 0;
}
