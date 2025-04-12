#include <stdbool.h>
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
 * skiplists.c
 *
 */
#define MAX_LV 100
#define BASE_ENTRY "1\0"

typedef struct word word_t;
typedef struct node node_t;

struct word{
	char *entry;
	char *def;
};

struct node{
	word_t *w;
	int lv;
	node_t *next;
	node_t *down;
};

struct skiplist{
	word_t *base_word;
	node_t *upLeft; //onde comecamos na lista
};

bool strs_is_in_order(char *lStr, char *rStr){
	int result = strcmp(lStr, rStr);

	return (result <= 0);
}

bool strs_are_equal(char *lStr, char *rStr){
	int result = strcmp(lStr, rStr);

	return (result == 0);
}

// OK
// /-> marca como função de uso exclusivo da biblio, e não do usuário
static word_t *_createWord(char *entry, char *def){
	word_t *nova_palavra = (word_t*) malloc(sizeof(word_t));

	nova_palavra->entry = entry;
	nova_palavra->def = def;

	return nova_palavra;
}

// OK
static void _freeWord(word_t *w){
	free(w->entry);
	free(w->def);
	free(w);
}

// OK
static node_t *_createNode(word_t *word, int lv, node_t *next, node_t *down){
	//alocando memoria para o novo no
	node_t* newNode = (node_t *) malloc(sizeof(node_t));

	newNode->w = word;
	newNode->lv = lv;
	newNode->next = next;
	newNode->down = down;
	
	return newNode;
}

// OK
static void _freeNode(node_t *n){
	_freeWord(n->w);
	free(n);
}

// OK
static int _getMaxLvUp(){
	//para saber quantos niveis o novo elemento deve
	//"subir", devemos sortear um numero aleatorio e
	//verificar se ele e par ou impar
	
	//par: sobe
	//imapr: nao faz nada
	
	int amtlvs = 0;
	int num = rand() % 100;
	int res = num % 2;
    
    int flagSobe = 0;
    
	while(res == 0 && flagSobe == 0 && amtlvs < MAX_LV){
		num = rand() % 100;
		res = num % 2;
		
		amtlvs++;
	}

	return amtlvs;
}

// OK
skiplist_t *sl_create(){
	skiplist_t *sl = (skiplist_t*) malloc(sizeof(skiplist_t));

	sl->base_word = _createWord(BASE_ENTRY, NULL);
	sl->upLeft = _createNode(sl->base_word, 0, NULL, NULL);

	return sl;
}

void liberar(skiplist_t *sl){

	node_t *sentinel = sl->upLeft;
	node_t *rem;

	//descendo ate o ultimo nivel
	while(sentinel->lv != 0){
		sentinel = sentinel->down;
	}
	
	// percorrendo todos os elementos no nivel 0
	while(sentinel != NULL){
		
		//ignorando os primeiros elementos
		if(strcmp(sentinel->w->entry, "1") == 0) sentinel = sentinel->next;
		
		rem = sentinel;
		//avancando na lista
		sentinel = sentinel->next;
		
		sl_remove(sl, rem->w->entry);

		rem = NULL;
	}
	
	//falta apagar os nos sentinelas de cada nivel
	sentinel = sl->upLeft;

	while(sentinel->lv != 0){

		rem = sentinel;
		//descendo para o proximo nivel
		sentinel = sentinel->down;

		free(rem);	
		rem = NULL;
	}
	
	free(sl->base_word);
	free(sl);
}

// OK
static node_t **_getPrevs(skiplist_t *sl, char *insertedEntry, int maxLvUp){

	node_t **prevs = (node_t **) malloc(MAX_LV * sizeof(node_t *));

	for(int newLv = sl->upLeft->lv + 1; newLv <= maxLvUp; newLv++){

		prevs[newLv] = _createNode(sl->base_word, newLv, NULL, sl->upLeft);			

		//criando o novo upLeft
		//esse upLeft criado passa a ser o novo upLeft
		sl->upLeft = prevs[newLv];
	}

	//primeiro tem que andar o maximo possivel nesse level e depois descer
	node_t *sentinel = sl->upLeft;


	// itera de lv em lv
	while(sentinel != NULL){
		// itera dentro de cada lv
		while(sentinel->next != NULL && !strs_is_in_order(insertedEntry, sentinel->next->w->entry)){

			sentinel = sentinel->next;
		}

		if(sentinel->lv <= maxLvUp) prevs[sentinel->lv] = sentinel;
		
		sentinel = sentinel->down;
	}

	return prevs;
}

static node_t *_searchNode(skiplist_t *sl, char *searchedEntry){
	node_t *prev = NULL;
	node_t *sentinel = sl->upLeft;

	// itera de lv em lv
	while(sentinel != NULL){

		// itera dentro de cada lv
		while(sentinel != NULL && !strs_is_in_order(searchedEntry, sentinel->w->entry)){

			prev = sentinel;
			sentinel = sentinel->next;
		}

		if(sentinel == NULL || !strs_are_equal(searchedEntry, sentinel->w->entry)){
			sentinel = prev->down;
		}
		else{
			return sentinel;
		}
	}

	return NULL;
}

// OK
/*bool*/int sl_insert(skiplist_t *sl, char *insertedEntry, char *insertedDef){
	word_t *insertedWord = _createWord(insertedEntry, insertedDef);
	
	if(_searchNode(sl, insertedWord->entry)){
		_freeWord(insertedWord);

		return 0; //se o elemento estiver na lista, nao ha nada que deve ser feito
	}

	int maxLvUp = _getMaxLvUp();
	node_t **prevs = _getPrevs(sl, insertedEntry, maxLvUp);

	node_t *newNode = _createNode(insertedWord, 0, prevs[0]->next, NULL);
	prevs[0]->next = newNode;
	for(int lv = 1; lv <= maxLvUp; lv++){
		newNode = _createNode(insertedWord, lv, prevs[lv]->next, newNode);
		prevs[lv]->next = newNode;
	}
	free(prevs);

	return 1;
}

char *sl_search(skiplist_t *sl, char *searchedEntry) {
	node_t *searchedNode = _searchNode(sl, searchedEntry);

	if(searchedNode != NULL){
		return searchedNode->w->def;
	}
	else{
		return NULL;
	}
}

int sl_remove(skiplist_t *sl, char *removedEntry){
	node_t *removedNode = _searchNode(sl, removedEntry);

	if(removedNode == NULL) return 0; //se nao estiver na lista nao e possivel apagar

	node_t **prevs = _getPrevs(sl, removedEntry, removedNode->lv);
	for(int lv = 0; lv <= removedNode->lv; lv++){
		prevs[lv]->next = prevs[lv]->next->next;
	}
	free(prevs);

	while (removedNode->down != NULL) {
		node_t *curNode = removedNode;

		removedNode = removedNode->down;
		free(curNode);
	}

	_freeNode(removedNode);

	return 1;
}

int sl_edit(skiplist_t *sl, char *editedEntry, char *newDef) {
	node_t *editedNode = _searchNode(sl, editedEntry);

	if(editedNode == NULL) return 0; //se nao estiver na lista nao e possivel editar

	free(editedNode->w->def);
	editedNode->w->def = newDef;

	return 1;
}

int sl_listByChar(skiplist_t *sl, char initialChar){
	node_t* sentinel = sl->upLeft;
	
	while(sentinel->down != NULL){
		// itera dentro de cada lv
		while(sentinel->next != NULL && sentinel->next->w->entry[0] < initialChar){
			sentinel = sentinel->next;
		}

		sentinel = sentinel->down;
	}

	while(sentinel->next != NULL && sentinel->next->w->entry[0] < initialChar){
		sentinel = sentinel->next;
	}

	if (sentinel->next == NULL || sentinel->next->w->entry[0] != initialChar) return 0;

	sentinel = sentinel->next;

	while (sentinel != NULL && sentinel->w->entry[0] == initialChar) {
		printf("%s %s\n", sentinel->w->entry, sentinel->w->def);
		sentinel = sentinel->next;

	}

	return 1;
}