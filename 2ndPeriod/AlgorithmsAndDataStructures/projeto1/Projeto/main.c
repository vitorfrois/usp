// Nome: Victor Henrique de Sa Silva
// Número USP: 11795759
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "include/skiplist.h"

int main() {
    srand(time(NULL));

    elem *op;
    skiplist *dict = create();
    while(!feof(stdin)) {
        
        op = read_Word();
        elem *word = read_Word();
        if (strcmp("insercao", op) == 0) {
            
            elem *entry = read_Entry();
            insert(dict, word, entry);
        } else if (strcmp("alteracao", op) == 0) {
            
            elem *new_entry = read_Entry();
            edit_entry(dict, word, new_entry);
        } else if (strcmp("remocao", op) == 0) {
            
            remove_item(dict, word);                
        } else if (strcmp("impressao", op) == 0) {
            
            print_words(dict, word);
        } else if (strcmp("busca", op) == 0) {
                
            search_elem(dict, word);
        }
        free(op);
    }
    destroy(dict);

    return 0;
}