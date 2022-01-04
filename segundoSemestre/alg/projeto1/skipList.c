#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>
#include "skipList.h"

#define NULL_STRING " \0"
#define MAX_AMT_LEVEL 42069

struct entry{
    char *word, *definition;
};

struct node{
    int level, maxLevel;
    Entry *data;
    struct node *next, *down;
};

struct skiplist{
    int level;
    int maxlevel;
    Node **header;
};

static Entry *_createEntry(char *word, char *definition) {
	Entry *newEntry = malloc(sizeof(Entry));

	newEntry->word = word;
	newEntry->definition = definition;

	return newEntry;
}

static void _freeEntry(Entry *data){
	free(data->word);
	free(data->definition);
	free(data);
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
static Node *_createNode(int level, Entry *data, Node *next, Node *down){
	Node *new = malloc(sizeof(Node));

	new->level = level;
	new->data = data;
	new->next = next;
	new->down = down;

	return new;
}

static void _freeNode(Node *node){
	_freeEntry(node->data);
	free(node);
}

static void _printEntry(Entry *data){
	printf("%s %s\n", data->word, data->definition);
}

static int _getRandNum(int max){
	int num = 0;
	while(rand() % 2 != 1 && num < max)
		num++;

	return num;
}

static Node *_getUpLeft(Skiplist *sl){
	return sl->header[sl->level];
}

static Node *_getNodeData(Skiplist *sl, char *word){
	Node *curNode = _getUpLeft(sl);
	while(curNode != NULL){
		while(curNode->next != NULL && strcmp(curNode->next->data->word, word) < 0){
			curNode = curNode->next;
		}

		if(curNode->next != NULL && strcmp(curNode->next->data->word, word) == 0)
			return curNode->next;

		curNode = curNode->down;
	}

	return NULL;
}

Skiplist *newSkiplist(){
	Skiplist* sl = malloc(sizeof(Skiplist));

	sl->level = 0;
	sl->maxlevel = MAX_AMT_LEVEL;
	sl->header = malloc(sizeof(Node**) * sl->maxlevel);

	Entry *baseEntry = _createEntry(NULL_STRING, NULL_STRING);

	sl->header[0] = _createNode(0, baseEntry, NULL, NULL);
	for(int i = 1; i < sl->maxlevel; i++)
		sl->header[i] = _createNode(i, baseEntry, NULL, sl->header[i - 1]);

	return sl;
}

void search(Skiplist *sl, char *word){
	Node *searchedNode = _getNodeData(sl, word);

	if(searchedNode != NULL)
		_printEntry(searchedNode->data);
	else
		printf("OPERACAO INVALIDA\n");
}

void insertEntry(Skiplist *sl, char *word, char *definition){
	//verifica se o valor já está na skip list
	if(_getNodeData(sl, word) != NULL){
		printf("OPERACAO INVALIDA\n");

		free(word);
		free(definition);

		return;
	}

	int nodeLevel = _getRandNum(sl->maxlevel - 1);

	Node **updates = malloc(sizeof(Node*) * (nodeLevel + 1)); //vetor de updates

	//busca do local em que o novo nó deve ser inserido e 
	//armazenamento dos nós updates
	Node *curNode = sl->header[nodeLevel];
	while(curNode != NULL){
		while(curNode->next != NULL && strcmp(curNode->next->data->word, word) < 0)
			curNode = curNode->next;

		updates[curNode->level] = curNode;
		curNode = curNode->down;
	}

	// inserção dos nós em níveis já existentes de 
	// maneira similar a uma lista encadeada
	
	// cria o novo nó a ser inserido na skip list
	int currentLevel = 1;

	Entry *insertedEntry = _createEntry(word, definition);
	Node *newNode = _createNode(0, insertedEntry, updates[0]->next, NULL);
	updates[0]->next = newNode;

	// cria nós em níveis acima do 0 se necessário
	while(currentLevel <= nodeLevel){
		newNode = _createNode(
			currentLevel,
			insertedEntry,
			updates[currentLevel]->next,
			newNode
		);

		updates[currentLevel]->next = newNode;
		currentLevel++;
	}

	if(sl->level < nodeLevel) sl->level = nodeLevel;

	free(updates);
}

void updateEntry(Skiplist *sl, char *word, char *newDefinition){
	Node *searchedNode = _getNodeData(sl, word);

	if(searchedNode == NULL) {
		printf("OPERACAO INVALIDA\n");
		free(newDefinition);
	}else{
		free(searchedNode->data->definition);
		searchedNode->data->definition = newDefinition;
	}
}

void removeEntry(Skiplist *sl, char *word){
	Node *searchedNode = _getNodeData(sl, word);

	//verifica se o valor já está na sl e inicialização de var
	if(searchedNode == NULL){
		printf("OPERACAO INVALIDA\n");

		return;
	}

	//printSkiplist(sl, "zero");

	Node **updates = malloc(sizeof(Node *) * (searchedNode->level + 1)); //vetor de updates
	//busca pelos nós, atualização do vetor de updates
	Node *curNode = sl->header[searchedNode->level];
	while(curNode != NULL){
		while(curNode->next != NULL && strcmp(curNode->next->data->word, word) < 0)
			curNode = curNode->next;

		updates[curNode->level] = curNode;
		curNode = curNode->down;
	}

	//realiza remoção de todos os nós de cima para baixo,
	//de maneira igual a uma lista encadeada
	int currentLevel = 0;
	while(currentLevel < searchedNode->level){
		Node* rem = updates[currentLevel]->next;
		updates[currentLevel]->next = rem->next;

		free(rem);

		currentLevel++;
	}
	updates[searchedNode->level]->next = searchedNode->next;
	_freeNode(searchedNode);

	while(sl->level > 0 && sl->header[sl->level]->next == NULL)
		sl->level--;

	free(updates);
}

void printSkiplist(Skiplist* sl, char *ch1){
	Node *curNode = _getUpLeft(sl);

	//busca pelo caractere ch1 verticalmente
	while(curNode->level != 0){
		while(curNode->next != NULL && strncmp(curNode->next->data->word, ch1, 1) < 0)
			curNode = curNode->next;

		curNode = curNode->down;
	}

	//busca pelo caractere no nível 0
	while(curNode->next != NULL && strncmp(curNode->next->data->word, ch1, 1) < 0)
		curNode = curNode->next;

	if(strncmp(curNode->next->data->word, ch1, 1) > 0){
		printf("NAO HA PALAVRAS INICIADAS POR %c", ch1[0]);
		return;
	}

	
	//imprime todas palavras até que a primeira letra seja diferente
	//do caractere definido
	while(curNode != NULL && strncmp(curNode->next->data->word, ch1, 1) == 0){
		curNode = curNode->next;
		printf("%s %s\n", curNode->data->word, curNode->data->definition);
	}
}

void freeSkipList(Skiplist* sl){
	//verifica se o valor já está na sl e inicialização de var
	if(sl == NULL)
		return;

	int level = sl->maxlevel - 1;
	while(level > 0){
		Node *curNode = sl->header[level];
		while(curNode && curNode->next != NULL){
			Node *nextNode = curNode->next;
			free(curNode);

			curNode = nextNode;
		}
		free(curNode);

		level--;
	}

	Node *curNode = sl->header[0]->next;
	free(sl->header[0]->data);
	free(sl->header[0]);

	while(curNode && curNode->next != NULL){
		Node *nextNode = curNode->next;
		_freeNode(curNode);

		curNode = nextNode;
	}
	_freeNode(curNode);

	free(sl->header);
	free(sl);
}