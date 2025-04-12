// Nome: Victor Henrique de Sa Silva
// Número USP: 11795759
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/skiplist.h"

#define LEVEL_PCT 50        // Chance de subir um nivel 

enum bool {False, True};

struct _skiplist {
    int number_of_levels;
    node *upleft;
};

struct _node {
    elem *word, *entry;
    node *next, *down;
    int level;
};

void init_node(node *new_node, node *next, node *down, int level, elem *word, elem *entry) {
    new_node->next = next;
    new_node->down = down;
    new_node->level = level;
    new_node->word = word;
    new_node->entry = entry;
}

skiplist *create() {
    skiplist *new_skiplist = malloc(sizeof(skiplist));
    assert(new_skiplist != NULL);

    node *upleft = malloc(sizeof(node));
    assert(upleft != NULL);

    char *sentinel_value = malloc(2 * sizeof(char));
    strcpy(sentinel_value, " ");

    /* O espaço é menor do que qualquer letra, servirá de sentinela */
    init_node(upleft, NULL, NULL, 0, sentinel_value, NULL); 
    new_skiplist->upleft = upleft;
    new_skiplist->number_of_levels = 0;

    return new_skiplist;
}

int coin_flip() {
    int new_level =  0;
    while (rand() % 100 >= LEVEL_PCT) {
        new_level++;
    }

    /* O retorno é o numero de niveis em que um nó inserido estará */
    return new_level;
}

void create_level(skiplist *base) {
    /* Assertion ja feita na função insert, não há necessidade de verificar de novo */
    node *new_level = malloc(sizeof(node));
    assert(new_level != NULL);

    char *sentinel_value = malloc(2 * sizeof(char));
    strcpy(sentinel_value, " ");

    init_node(new_level, NULL, base->upleft, base->upleft->level + 1, sentinel_value, NULL);
    base->upleft = new_level;
    base->number_of_levels++;
}

char *read_Word() {
    int pos = 0, size = 32;
    char letter, *word = malloc(size * sizeof(char));
    
    /* Leitura da palavra ocorre até a que seja lido um espaço, enter ou chegue ao fim de um arquivo */
    while (True) {
        scanf("%c", &letter);
        if (letter == ' ' || letter == '\n' || feof(stdin))
            break;
        
        /* Se necessário, aumenta o número de caracteres que a palavra pode ter */
        if (pos == size) {
            size *= 2;
            word = realloc(word, size * sizeof(char));
        }
        
        if (letter != '\r') {
            word[pos] = letter;
            pos++;
        }
    }
    word = realloc(word, sizeof(char) * (pos + 1));  /* Realoca para o tamanho exato da palavra */
    word[pos] = '\0';

    return word;
}

char *read_Entry() { 
    int pos = 0, size = 50;
    char letter, *entry = malloc(size * sizeof(char));

    /* Similar à leitura das palavras, mas para apenas no enter ou fim de arquivo (Pode conter espaços) */
    while (True) {
        scanf("%c", &letter);
        if (letter == '\n' || feof(stdin)) 
            break;
        
        if (pos == size) {
            size *= 2;
            entry = realloc(entry, size * sizeof(char));
        }

        if (letter != '\r') {
            entry[pos] = letter;
            pos++;
        }
    }   
    entry = realloc(entry, (pos + 1) * sizeof(char));
    entry[pos] = '\0';

    return entry;
}

node *search(skiplist *base, elem *word) {

    int compare = -1;
    node *current_node = base->upleft;

    /* Loop responsável pela movimentação vertical na lista */
    while (current_node != NULL && compare < 0) {

       /* Loop responsável pela movimentação horizontal */ 
        while (current_node->next != NULL && compare < 0) {    
            compare = strcmp(current_node->next->word, word);
            if (compare < 0)
                current_node = current_node->next;
        }

        if (compare == 0) 
            return current_node->next;

        compare = strcmp(current_node->word, word);
        current_node = current_node->down;
    }

    return NULL;
}

void search_elem(skiplist *base, elem *word) {
    assert(base != NULL);

    node *searched = search(base, word);
    if (searched == NULL)
        printf("OPERACAO INVALIDA\n");
    else 
        printf("%s %s\n", searched->word, searched->entry);

    free(word);
}

int insert(skiplist *base, elem *new_word, elem *new_entry) {
    assert(base != NULL);
    
    node *exists = search(base, new_word);
    if (exists != NULL) {
        printf("OPERACAO INVALIDA\n");
        free(new_word);
        free(new_entry);
        return False;
    }

    /*  Decide em quanto niveis o nó será colocado
        e cria novos niveis se necessario           */
    int max_level = coin_flip();
    if (max_level > base->number_of_levels) {
        while (base->number_of_levels < max_level) {
            create_level(base);
        }
    }
    
    /* Chega no nó a partir de onde deve inserir */
    node *current_node = base->upleft;
    node *top_node = NULL;
    
    int compare = -1;
    while (current_node != NULL && compare < 0) {
        while (current_node->next != NULL && compare < 0) {
            compare = strcmp(current_node->next->word, new_word);
            if (compare < 0)
                current_node = current_node->next;
        }

        /* Se chegou no fim de um nivel onde deve ser adicionado 
          ou achou a posiçao em que deve ser inserido, insere    */
        if ((compare > 0 || current_node->next == NULL) && current_node->level <= max_level) {
            node *new_node = malloc(sizeof(node));
            assert(new_node != NULL);
            
            init_node(new_node, current_node->next, NULL, current_node->level, new_word, new_entry);
            current_node->next = new_node;
            
            if (top_node != NULL)   
                top_node->down = new_node;
            top_node = new_node;
        }

        compare = strcmp(current_node->word, new_word);
        current_node = current_node->down;
    }

    return True;
}

int remove_item(skiplist *base, elem *word) {
    assert(base != NULL);

    node *to_remove = search(base, word);
    if (!to_remove) {
        printf("OPERACAO INVALIDA\n");
        free(word);
        return False;
    }

    node *current_node = base->upleft;
    
    int compare = -1, can_go_down = 1;
    while (current_node != NULL && compare < 0) {
        while (current_node->next != NULL && compare < 0) {
            compare = strcmp(current_node->next->word, word);
            if (compare < 0)
                current_node = current_node->next;
        }

        /* Ao chegar no nível 0, libera o espaço alocado para os dados */
        if (current_node->level == 0 && compare == 0) {
            free(current_node->next->word);
            free(current_node->next->entry);
        }

        if (compare == 0) {
            node *to_free = current_node->next;
            current_node->next = to_free->next;
            free(to_free);

            /* Retira o nivel quando necessário */
            if (base->upleft->next == NULL) {
                node *sentinel_remove = base->upleft; 
                base->upleft = base->upleft->down;
                free(sentinel_remove->word);
                free(sentinel_remove);

                current_node = base->upleft;
                can_go_down = 0;                    // Nao deixa descer de novo no fim do while externo
            } else {
                can_go_down = 1;
            }
        }

        compare = strcmp(current_node->word, word);
        if(can_go_down)
            current_node = current_node->down;
    }

    free(word);
    return True;
}

int edit_entry(skiplist *base, elem *word, elem *new_entry) {
    assert(base != NULL);

    node *to_edit = search(base, word);
    if (to_edit == NULL) {              /* Retorna NULL quando o elemento não existe */
        printf("OPERACAO INVALIDA\n");
        free(word);
        free(new_entry);
        return False;
    }

    if (strcmp(to_edit->entry, new_entry) == 0) {
        free(word);
        free(new_entry);
        return True;
    }
    /* Libera aquele espaço de memoria */
    free(to_edit->entry);
    to_edit->entry = NULL;

    /* Cria a nova definição */
    int new_len = 1;
    for (int i = 0; new_entry[i] != '\0'; i++)
        new_len++;

    to_edit->entry = malloc(new_len * sizeof(char));
    strcpy(to_edit->entry, new_entry);

    elem *new_entry_pos = to_edit->entry;

    /* E coloca os blocos para apontarem para nova definição */
    while (to_edit != NULL) {
        to_edit->entry = new_entry_pos;
        to_edit = to_edit->down; 
    }

    free(word);
    free(new_entry);
    return True;
}

void destroy(skiplist *base) {
    assert(base != NULL);
    
    /* Percorre a lista removendo os elementos de cada nivel */
    while (base->upleft != NULL) {
        node *line = base->upleft->next;
        while (line != NULL) {
            node *to_free = line;
            line = line->next;

            if (to_free->level == 0) {
                free(to_free->word);
                free(to_free->entry);
            }
            free(to_free);
        }

        free(base->upleft->word);
        line = base->upleft;
        base->upleft = base->upleft->down;
        free(line);
    }

    free(base);
}

void print_words(skiplist *base, char *starts_with) {
    assert(base != NULL);

    /* Percorre a lista procurando a posição em que começam 
      as palavras iniciadas com a letra indicada pelo usuário */
    int compare = -1;
    node *current_node = base->upleft;
    while (current_node->down != NULL) {
        compare = strcmp(current_node->word, starts_with);
        while (current_node->next != NULL && compare < 0) {
            compare = strcmp(current_node->next->word, starts_with);
            if (compare < 0)
                current_node = current_node->next;
        }

        current_node = current_node->down;
    }

    /* Flag para ter controle do momento em que pode para de percorrer a lista */
    int printed = 0;
    
    compare = strcmp(current_node->next->word, starts_with);
    while (current_node != NULL) {
        if (printed && current_node->word[0] > starts_with[0])
            break;

        if (current_node->word[0] == starts_with[0]) {
            printf("%s %s\n", current_node->word, current_node->entry);
            printed = 1;
        }
        current_node = current_node->next;
    }

    if (!printed)
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", *starts_with);
    
    free(starts_with);
}