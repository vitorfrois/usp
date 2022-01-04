#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "skiplist.h"

/* Laura Ferre Scotelari 12543436
 * 
 * Projeto 1 - Algoritmos e Estruturas de Dados
 * Dicionario de Palavras
 *
 * main.c
 *
 */
char* readLine(char delimitador, int *isEndOfInput);

int main(){
 	srand(time(0));
	
 	skiplist_t *sl = sl_create();
 	
 	char *entry;
 	char *def;
 	char *operation;
 	int isEndOfInput = 0;
	double time_taken;
    clock_t t;
 	do{
 		operation = readLine(' ', &isEndOfInput);
        t = clock();
 		if(strcmp(operation, "insercao\0") == 0){
 			
	 		entry = readLine(' ', &isEndOfInput);
	 		def = readLine('\n', &isEndOfInput);

	 		if(sl_insert(sl, entry, def)){

		 	}
			else{
		 		//printf("Nao foi possivel inserir o elemento\n");
		 		printf("OPERACAO INVALIDA\n");
			}
			/*if(entry != NULL){
				free(entry);
				entry = NULL;
			}
			if(def != NULL){
				free(def);
				def = NULL;
			}*/

		}
		else if(strcmp(operation, "alteracao\0") == 0){
					
			entry = readLine(' ', &isEndOfInput);
			char* newDef = readLine('\n', &isEndOfInput);
			
			if(sl_edit(sl, entry, newDef)){

			}
			else{
				printf("OPERACAO INVALIDA\n");
			}
			if(entry != NULL){
				free(entry);
				entry = NULL;
			}
		}
		else if(strcmp(operation, "remocao\0") == 0){
			
			entry = readLine('\n', &isEndOfInput);
			
			if(sl_remove(sl, entry)){
			}
			else{
				printf("OPERACAO INVALIDA\n");
			}
			if(entry != NULL){
				free(entry);
				entry = NULL;
			}
		}
		else if(strcmp(operation, "busca\0") == 0){
			
			entry = readLine('\n', &isEndOfInput);
			char *def = sl_search(sl, entry);
			
			if(def){
				printf("%s %s\n", entry, def);
			}
			else{
				printf("OPERACAO INVALIDA\n");
			}
			if(entry != NULL){
				free(entry);
				entry = NULL;
			}
			
		}
		else if(strcmp(operation, "impressao\0") == 0){

			char primeiroChar = getchar();
			
			//eliminando o pula-linha
			char proxChar = getchar();
			
			if(proxChar == '\r'){
				getchar();
			}
			else{
				ungetc(proxChar, stdin);
			}
			
			if(proxChar != '\n'){
				ungetc(proxChar, stdin);
			} 
			
			
			if(sl_listByChar(sl, primeiroChar)){
			}
			else{
				printf("OPERACAO INVALIDA\n");
			}

		}

 		else if(strlen(operation)>0){
 			printf("OPERACAO INVALIDA\n");
		}
		free(operation);
		t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf(" -> %s took %f seconds \n", operation, time_taken); 
 	}while(!isEndOfInput);
 

 	liberar(sl);
 	/*if(entry != NULL){
		free(entry);
		entry = NULL;
	}
	if(def != NULL){
		free(def);
		def = NULL;
	}*/
 	return 0;
 }
 
char* readLine(char delimitador, int* isEndOfInput){
	char* linha = NULL;
	char caractereLido;
	int tamanho = 0;

	//armazenando a linha, char a char at� encontrar o \n
	do{
		caractereLido = getchar();
		
		if (caractereLido == '\r') caractereLido = getchar();

		//indicando que mais um char foi pego
		tamanho++;
			
		//realocando o vetor para que ele possa receber + um char 
		linha = (char*) realloc(linha, tamanho * sizeof(char));
		
		if(caractereLido != '\n' && caractereLido != EOF && caractereLido != delimitador){
			linha[tamanho - 1] = caractereLido;
		}
		else{ //caso seja o \n, a linha acabou e devemos finalizar a string com \0
			linha[tamanho - 1] = '\0';
		}
		
		if(caractereLido == EOF){
			//printf("EOF detectado\n");
			*isEndOfInput = 1;
		}
		
	} while(caractereLido != delimitador && caractereLido != EOF);

	return linha;
}