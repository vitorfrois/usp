#include <stdio.h>
#include <stdlib.h>

void enquadra_arte(char *, int, int);

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

void art_printer(char** matrix, int heigth, int length){
      for(int i = 0; i < heigth; i++){
            for(int j = 0; j < length; j++){
                  printf("%c", matrix[i][j]);
            }
            printf("\n");
      }
}

void art_painter(char** matrix, char color, int x, int y, int heigth, int lenght, char oldColor){
      //printf("eae boiolas\n");
      if((x >= 0) && (y >= 0) && (x < heigth) && (y < lenght) && matrix[x][y] == oldColor){
            matrix[x][y] = color;
            art_painter(matrix, color, x+1, y, heigth, lenght, oldColor);
            art_painter(matrix, color, x-1, y, heigth, lenght, oldColor);
            art_painter(matrix, color, x, y+1, heigth, lenght, oldColor);
            art_painter(matrix, color, x, y-1, heigth, lenght, oldColor);
      }
}

void art_file_printer(char** matrix, int heigth, int length, FILE* fp){
      for(int i = 0; i < heigth; i++){
            for(int j = 0; j < length; j++){
                  fprintf(fp, "%c", matrix[i][j]);
            }
            if(i != (heigth-1))
                  fprintf(fp, "\n");
      }
}

int main(){
      char* artName = readString();
      FILE* fp = fopen(artName, "r+");
      if (fp == NULL){
            printf("Erro!\n");
      }

      char** matrix;
      matrix = malloc(sizeof(char*));
      matrix[0] = malloc(sizeof(char));

      char character;
      int nCharsLine = 0, nLines = 0, lenght, heigth;
      do{
            character = fgetc(fp);
            if(character != '\n' && character != EOF){
                  matrix[nLines] = realloc(matrix[nLines], (nCharsLine + 1) * sizeof(char));
                  matrix[nLines][nCharsLine] = character;
                  nCharsLine++;
            }else{
                  lenght = nCharsLine;
                  nCharsLine = 0;
                  nLines++;
                  matrix = realloc(matrix, (nLines+1) * sizeof(char*));
                  matrix[nLines] = NULL;
            }
      }while(character != EOF);

      heigth = nLines;

      printf("Arte inicial:\n");
      art_printer(matrix, heigth, lenght);

      int nPaintings;
      char color;
      int x, y;
      scanf("%d\n", &nPaintings);
      for(int i = 0; i < nPaintings; i++){
            scanf("%c %d %d\n", &color, &x, &y);
            //printf("old char = |%c|\n", matrix[x][y]);
            art_painter(matrix, color, x, y, heigth, lenght, matrix[x][y]);
            printf("\nArte apos a etapa %d:\n", i);
            art_printer(matrix, heigth, lenght);
            //coloring function
      }

      rewind(fp);
      art_file_printer(matrix, heigth, lenght, fp);


      for(int i = 0; i < nLines; i++)
            free(matrix[i]);
      free(matrix);
      fclose(fp);
      printf("\nArte enquadrada:\n");
      enquadra_arte(artName, heigth, lenght);

      free(artName);
      return 0;
}


void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro
){
	FILE *f_arte_ptr = fopen(nome_do_arquivo_da_arte, "r");
	if (f_arte_ptr == NULL) {
		printf(
			"Erro na abertura do arquivo, "
			"Você esqueceu de fechar o arquivo antes? "
			"Ou deu free na string com o nome sem querer?\n"
		);

		exit(EXIT_FAILURE);
	}

	int qtd_espc_comeco;
	const char *apoio;
	if (largura_do_quadro % 2 == 0) {
		qtd_espc_comeco = largura_do_quadro / 2;
		apoio           = "/\\";
	} else {
		qtd_espc_comeco = largura_do_quadro / 2 + 1;
		apoio           = "Ʌ";
	}

	for (int i = 0; i < qtd_espc_comeco; i++) printf(" ");
	printf("%s\n", apoio);

	printf("╭");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╮\n");

	for (int i = 0; i < altura_do_quadro; i++) {
		printf("|");
		for (int j = 0; j < largura_do_quadro; j++) {
			char pixel_atual = fgetc(f_arte_ptr);
			printf("%c", pixel_atual);
		}
		printf("|");

		char quebra = fgetc(f_arte_ptr);
		if (quebra != EOF) printf("%c", quebra);
	};
	fclose(f_arte_ptr);

	printf("\n╰");
	for (int i = 0; i < largura_do_quadro; i++) printf("—");
	printf("╯\n");
}
