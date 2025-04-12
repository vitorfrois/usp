// Nome: Victor Henrique de Sa Silva
// Número USP: 11795759
#ifndef SKIPLIST_H
#define SKIPLIST_H

typedef char elem;
typedef struct _skiplist skiplist;
typedef struct _node node;

skiplist *create();                                          /* Cria uma estrutura de skiplist */
char *read_Word();                                           /* Leitura da palavra que será utilizada nas funções */
char *read_Entry();                                          /* Leitura da definição das palavras */
void search_elem(skiplist *base, elem *word);                /* Busca por uma palavra no dicionário */
int insert(skiplist *base, elem *new_word, elem *new_entry); /* Insere uma palavra com sua definição no dicionário */
int remove_item(skiplist *base, elem *word);                 /* Remove uma palavra do dicionário */
int edit_entry(skiplist *base, elem *word, elem *new_entry); /* Edita um verbete de uma palavra */
void destroy(skiplist *base);                                /* Destrói a estrutura da skiplist */
void print_words(skiplist *base, char *starts_with);         /* Imprime todas as palavras iniciadas por uma letra determinada */

#endif