#include <stdio.h>
#include <stdlib.h>

typedef struct{
      int nPeople;
      int paths;
      int visited;
      double explored;
}lData;

char* readString(){
      char *string = malloc(sizeof(char));
      char character = ' ';
      int nCharsString = 0;
      do {
            character = getchar();
            string = realloc(string, (nCharsString + 1) * sizeof(char*));
            string[nCharsString] = character;
            nCharsString++;
      } while(character != '\n');
      string[nCharsString - 1] = '\0';
      return string;
}

void labSolver(char** matrix, lData data, int x, int y, int heigth, int lenght){
      //printf("eae boiolas\n");
      if((x >= 0) && (y >= 0) && (x < heigth) && (y < lenght)){
            if(matrix[x][y] == '.'){
                  matrix[x][y] = '*';
                  data.visited++;
            }
            if(matrix[x+1][y] != '#'){
                  labSolver(matrix, data, x+1, y, heigth, lenght);
            }else if(matrix[x][y+1] != '#'){
                  labSolver(matrix, data, x, y+1, heigth, lenght);
            }else if(matrix[x-1][y] != '#'){
                  labSolver(matrix, data, x-1, y, heigth, lenght);
            }else if(matrix[x][y-1] != '#'){
                  labSolver(matrix, data, x, y-1, heigth, lenght);
            }
      }
}


int main(){
      char* artName = readString();
      FILE* fp = fopen(artName, "r+");
      if (fp == NULL){printf("Erro!\n");}

      char** matrix;
      matrix = malloc(sizeof(char*));
      matrix[0] = malloc(sizeof(char));

      lData data;
      data.nPeople = 0;
      data.paths = 0;
      data.visited = 0;

      int M, N, x, y;

      fscanf(fp, "%d %d\n", &M, &N);
      matrix = realloc(matrix, sizeof(char*) * M);
      for(int i = 0; i < M; i++)
            matrix[i] = realloc(matrix, sizeof(char) * N);
      fscanf(fp, "%d %d\n", &x, &y);


      for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                  fscanf(fp, "%c", &matrix[i][j]);
                  if(matrix[i][j] == '#'){
                        data.nPeople++;
                  }else{
                        data.paths++;
                  }
            }
            fscanf(fp, "%*c");
      }

      labSolver(matrix, data, x, y, M, N);
      for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                  printf("%c", matrix[i][j]);
            }
            printf("\n");
      }

      data.explored = data.visited / data.paths;
      printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
      printf("Veja abaixo os detalhes da sua fuga:\n");
      printf("----Pessoas te procurando: %d\n", data.nPeople);
      printf("----Numero total de caminhos validos: %d\n", data.paths);
      printf("----Numero total de caminhos visitados: %d\n", data.visited);
      printf("----Exploracao total do labirinto: %.1lf%%\n", data.explored);


      fclose(fp);

      for(int i = 0; i < M; i++)
            free(matrix[i]);
      free(matrix);



      return 0;
}
