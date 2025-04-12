
/* Laura Ferre Scotelari 12543436
 * 
 * Projeto 1 - Algoritmos e Estruturas de Dados
 * Dicionario de Palavras
 * 
 * skiplists.h
 */
 

#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_

typedef struct skiplist skiplist_t;

skiplist_t *sl_create();
void sl_free(skiplist_t *sl);

int sl_insert(skiplist_t *sl, char *insertedEntry, char *insertedDef);
int sl_remove(skiplist_t *sl, char *removedEntry);

char *sl_search(skiplist_t *sl, char *searchedEntry);
int sl_edit(skiplist_t *sl, char *editedEntry, char *newDef);

int sl_listByChar(skiplist_t *sl, char chr);

void liberar(skiplist_t *sl);

#endif