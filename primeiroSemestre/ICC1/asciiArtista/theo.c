/************************************
 *
 *      ARTE ASCII / TRABALHO 3
 *
 *        Nome: Théo Riffel
 *        Número USP: 12547812
 *
*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arte_ascii{
    char color;
    int x;
    int y;
} arte_ascii_t;

char *read_line();
void read_fills_info();
char **fullfill_matriz_art();
char **apply_fills(char **matriz_art, int lines, int colums, int x, int y, char color, char previous_color);
void save_matriz_art();
void print_matriz_art();
void enquadra_arte();

int main(){

    char *file_name;
    int lines = 0;
    int colums = 0;

    file_name = read_line();
    printf("%s\n", file_name);

    char **matriz_art;
    matriz_art = fullfill_matriz_art(&lines, &colums, file_name);

    int qnt_fills;
    scanf(" %d", &qnt_fills);

    arte_ascii_t fills[qnt_fills];

    for(int i = 0; i < qnt_fills; i++){
        read_fills_info(fills, i);
    }

    printf("Arte inicial:\n");
    print_matriz_art(matriz_art, lines, colums);

    for(int i = 0; i < qnt_fills; i++){
        printf("cor %d: %c\n", i, fills[i].color);
        printf("x %d: %d\n", i, fills[i].x);
        printf("y %d: %d\n", i, fills[i].y);
    }

    char previous_color;
    for(int i = 0; i < qnt_fills; i++){
        previous_color = matriz_art[fills[i].x][fills[i].y];
        matriz_art = apply_fills(matriz_art, lines, colums, fills[i].x, fills[i].y, fills[i].color,  previous_color);

        printf("\nArte apó s a etapa %d:\n", i);
        print_matriz_art(matriz_art, lines, colums);
    }

    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

    save_matriz_art(matriz_art, lines, colums, file_name);
    enquadra_arte(file_name, lines, colums);

    for(int i = 0; i < lines; i++){
        free(matriz_art[i]);
    }
    free(matriz_art);

    free(file_name);

    return 0;
}

void read_fills_info(arte_ascii_t *fill, int fill_number){
    scanf(" %c", &fill[fill_number].color);
    scanf(" %d", &fill[fill_number].x);
    scanf(" %d", &fill[fill_number].y);
}

char **fullfill_matriz_art(int *lines, int *colums, char *file_name){
    FILE *file;
    file = fopen(file_name, "r");

    if(file == NULL){ //erro na abertura do arquivo
        printf("Arquivo %s nao existe.\n", file_name);
        exit(0);
    }
    else{
        printf("Arquivo %s existe.\n", file_name);
    }

    char **matriz_art = NULL;
    int number_colum = 0;
    int number_line = 0;
    char char_art = '\0';

    do{
        char_art = '\0';
        number_line++;
        matriz_art = realloc(matriz_art, number_line * sizeof(char *));
        matriz_art[number_line - 1] = NULL;
        number_colum = 0;

        while (char_art != '\n' && char_art != EOF){
            char_art = fgetc(file);
            number_colum++;
            matriz_art[number_line - 1] = realloc(matriz_art[number_line - 1], number_colum * sizeof(char));
            matriz_art[number_line - 1][number_colum - 1] = char_art;
        }

        number_colum--;
        matriz_art[number_line - 1] = realloc(matriz_art[number_line - 1], number_colum * sizeof(char));
    }
    while(char_art != EOF);

    *lines = number_line;
    *colums = number_colum;

    fclose(file);

    return matriz_art;
}

char **apply_fills(char **matriz_art, int lines, int colums, int x, int y, char color, char previous_color){
    if((x >= 0) && (y >= 0) && (x < colums) && (y < lines) && (matriz_art[y][x] == previous_color)){
        matriz_art[y][x] = color;
        apply_fills(matriz_art, lines, colums, x, y + 1, color, previous_color);
        apply_fills(matriz_art, lines, colums, x + 1, y, color, previous_color);
        apply_fills(matriz_art, lines, colums, x, y - 1, color, previous_color);
        apply_fills(matriz_art, lines, colums, x - 1, y, color, previous_color);
    }

    return matriz_art;
}

void print_matriz_art(char **matriz_art, int lines, int colums){

    for(int i = 0; i < lines; i++){
        for(int j = 0; j < colums; j++){
            printf("%c", matriz_art[i][j]);
        }
        printf("\n");
    }
}

void save_matriz_art(char **matriz_art, int lines, int colums, char *file_name){
    FILE *file;
    file = fopen(file_name, "w");

    if(file == NULL){ //erro na abertura do arquivo
        printf("Erro na abertura do arquivo %s.\n", file_name);
        exit(0);
    }

    for (int i = 0; i < lines; i++){
        for (int j = 0; j < colums; j++){
            fprintf(file, "%c", matriz_art[i][j]);
        }
    }

    fclose(file);
}

char *read_line(){

    int string_length = 0;
    char char_mensage = '\0';
    char *string = NULL;

    while (char_mensage != '\n'){

        char_mensage = getchar();
        string_length++;
        string = realloc(string, string_length * sizeof(char));
        string[string_length - 1] = char_mensage;
    }

    string[string_length - 1] = '\0';

    return string;
}

void enquadra_arte(
	char *nome_do_arquivo_da_arte,
	int  altura_do_quadro,
	int  largura_do_quadro
) {
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
