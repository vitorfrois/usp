#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "skipList.h"
#define NULL_STRING " "

Skiplist *newSkiplist(){
    Skiplist* sl = malloc(sizeof(Skiplist));

	sl->lenght = 0;
	sl->level = 0;
	sl->maxlevel = 20;
    sl->header = malloc(sizeof(Node**) * sl->maxlevel);
	for(int i = 0; i < sl->maxlevel; i++){
		if(i == 0)
			sl->header[i] = createNode(i, NULL_STRING, NULL_STRING, NULL, NULL);
		else
			sl->header[i] = createNode(i, NULL_STRING, NULL_STRING, NULL, sl->header[i-1]);
	}
	sl->upleft = sl->header[0];
    return sl;
}

/**
 * @brief Create a Node object
 * 
 * @param level nível do nó
 * @param word 
 * @param definition 
 * @param next o próximo nó no mesmo nível
 * @param down nó abaixo
 * @return Node* 
 */
Node* createNode(
	//declaração extendida dos atributos da função
	int level, 
	char *word, 
	char *definition,
	Node *next,
	Node *down
){

    Node *new = malloc(sizeof(Node));
    new->level = level;
	new->data.word = malloc(sizeof(char) * strlen(word) + 1);
	new->data.definition = malloc(sizeof(char) * strlen(definition) + 1);
	strcpy(new->data.word, word);
	strcpy(new->data.definition, definition);
    new->next = next;
	new->down = down;

    return new;
}

bool search(Skiplist *sl, char *word, bool verbose){
	Node *aux;
	// age nas linhas superiores à 0
	aux = sl->upleft;

	while(aux->level != 0){
		while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0){	
			aux = aux->next;
		}
		aux = aux->down;
	}
	
	// essa parte do código age na linha 0
	while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
		aux = aux->next;
		
	if(aux->next == NULL)
		return false;

	if(strcmp(aux->next->data.word, word) == 0){
		if(verbose == true)	printf(
			"%s %s\n", 
			aux->next->data.word, 
			aux->next->data.definition
		);
		return true;
	}
	if(verbose == true)	printf("OPERACAO INVALIDA\n");
	return false;
}

void insertEntry(Skiplist *sl, char *word, char *definition){
	//verifica se o valor já está na skip list
	if(search(sl, word, false) == true){
		printf("OPERACAO INVALIDA\n");
		return;
	}

	//Inicializa variáveis
	Node *aux;

	//coinflips
	int nodeLevel = 0;
	while(rand() % 2 != 1 && nodeLevel < sl->maxlevel)
		nodeLevel++;

	Node** updates = malloc(sizeof(Node*) * (nodeLevel + 1)); //vetor de updates

	aux = sl->header[nodeLevel];

	//busca do local em que o novo nó deve ser inserido e 
	//armazenamento dos nós updates
	while(aux->level != 0){
		while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
			aux = aux->next;
		updates[aux->level] = aux;
		aux = aux->down;
	}
	
	//busca do nó no nível 0
	while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
		aux = aux->next;
	
	updates[aux->level] = aux;

	// inserção dos nós em níveis já existentes de 
	// maneira similar a uma lista encadeada
	
	// cria o novo nó a ser inserido na skip list
	int currentLevel = 0;
	Node *new;

	// cria nós em níveis acima do 0 se necessário
	while(currentLevel <= nodeLevel){

		new = createNode(currentLevel, word, definition, NULL, NULL);
		new->maxLevel = nodeLevel;
		new->next = updates[currentLevel]->next;
		if(currentLevel == 0)
			new->down = NULL;
		else
			new->down = updates[currentLevel - 1]->next;
		
		updates[currentLevel]->next = new;
		currentLevel++;
	}

	if(sl->level < nodeLevel) sl->level = nodeLevel;
	sl->upleft = sl->header[sl->level];
	
	
	free(updates);
}

void updateEntry(Skiplist *sl, char *word, char *definition){
	if(search(sl, word, false) == false){
		printf("OPERACAO INVALIDA\n");
		return;
	}

	//printf("eu quero atualizar %s\n", word);
	
	Node** updates = malloc(sizeof(Node*) * sl->maxlevel); //vetor de updates
	Node *aux = sl->upleft;
	
	while(aux->level != 0){
		while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
			aux = aux->next;
		updates[aux->level] = aux;
		aux = aux->down;
	}

	while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
		aux = aux->next;

	updates[aux->level] = aux;

	int currentLevel = 0;
	while(currentLevel <= sl->level){
		//printf("(%d/%d)\n", currentLevel, sl->level);
		if(updates[currentLevel]->next != NULL && strcmp(updates[currentLevel]->next->data.word, word) == 0)
			strcpy(updates[currentLevel]->next->data.definition, definition);
		else {
			free(updates);
			return;
		}
		
		currentLevel++;
	}

	free(updates);
}

void removeEntry(Skiplist *sl, char *word){
	//verifica se o valor já está na sl e inicialização de var
	if(search(sl, word, false) == false){
		printf("OPERACAO INVALIDA\n");
		return;
	}
	
	//printSkiplist(sl, "zero");

	Node* aux;
	aux = sl->upleft;
	Node** updates = malloc(sizeof(Node*) * sl->maxlevel); //vetor de updates
	//busca pelos nós, atualização do vetor de updates
	
	while(aux->level != 0){
		while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
			aux = aux->next;
		updates[aux->level] = aux;
		aux = aux->down;
	}

	//busca pelo nó anterior ao qual o dado será removido
	while(aux->next != NULL && strcmp(aux->next->data.word, word) < 0)
		aux = aux->next;

	updates[aux->level] = aux;

	//realiza remoção de todos os nós de cima para baixo,
	//de maneira igual a uma lista encadeada
	int currentLevel = 0;
	
	while(currentLevel <= sl->level){
		if(updates[currentLevel]->next && strcmp(updates[currentLevel]->next->data.word, word) == 0){
			//printf("removing %s/%s\n", updates[currentLevel]->next->data.word, word);
			Node* rem = updates[currentLevel]->next;
			updates[currentLevel]->next = rem->next;
			free(rem->data.word);
			free(rem->data.definition);
			free(rem);
			
		}else{
			break;
		}
		currentLevel++;
	}	

	//remove o nível quando não existe adjacente a upleft, 
	//diminuindo nível da skip list	
	// while(sl->header[sl->level]->next != NULL && sl->header[sl->level]->down != NULL){
	// 	sl->level--;
	// }

	free(updates);
}

void printSkiplist(Skiplist* sl, char *ch1){

    Node *aux = sl->upleft;

	//busca pelo caractere ch1 verticalmente
	while(aux->level != 0){
		while(aux->next != NULL && strncmp(aux->next->data.word, ch1, 1) < 0)
			aux = aux->next;

		aux = aux->down;
	}

	//busca pelo caractere no nível 0
	while(aux->next != NULL && strncmp(aux->next->data.word, ch1, 1) < 0)
		aux = aux->next;

	if(strncmp(aux->next->data.word, ch1, 1) > 0){
		printf("NAO HA PALAVRAS INICIADAS POR %c", ch1[0]);
		return;
	}

	
	//imprime todas palavras até que a primeira letra seja diferente
	//do caractere definido
	while(aux != NULL && strncmp(aux->next->data.word, ch1, 1) == 0){
		aux = aux->next;
        printf("%s %s\n", aux->data.word, aux->data.definition);
	}

}

void freeList(Skiplist* sl){
	//verifica se o valor já está na sl e inicialização de var
	if(sl == NULL)
		return;

	int level = sl->maxlevel - 1;

	Node *aux = sl->header[level];
	Node *rem;

	while(level != 0){
		aux = sl->header[level];
		rem = aux;
		while(aux && aux->next != NULL){
			aux = aux->next;
			free(rem->data.word);
			free(rem->data.definition);
			free(rem);
			rem = aux;
		}

		free(rem->data.word);
		free(rem->data.definition);
		free(rem);

		level--;
		aux = sl->header[level];
		// "TRAGA-ME LEAKS NO VALGRIND E CORRIGI-LOS-EI"
	}

	rem = aux;
	while(aux->next != NULL){
		aux = aux->next;
		free(rem->data.word);
		free(rem->data.definition);
		free(rem);
		rem = aux;
	}

	// ultimo nó
	free(rem->data.word);
	free(rem->data.definition);
	free(rem);

	free(sl->header);
	free(sl);
}