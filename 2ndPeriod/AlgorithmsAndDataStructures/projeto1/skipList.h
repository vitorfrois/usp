#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_

typedef struct entry Entry;
typedef struct node Node;
typedef struct skiplist Skiplist;

Skiplist *newSkiplist();

void search(Skiplist *sl, char *word);
void insertEntry(Skiplist *sl, char *word, char *definition);
void updateEntry(Skiplist *sl, char *word, char *definition);
void removeEntry(Skiplist *sl, char *word);
void printSkiplist(Skiplist* sl, char* mode);
void freeSkipList(Skiplist* sl);

#endif