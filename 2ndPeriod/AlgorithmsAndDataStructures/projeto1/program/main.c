#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "myString.h"
#include "skipList.h"

int main(){
    Skiplist *sl = newSkiplist();
    srand(time(NULL));
    char *input;
    while(strcmp(input = readString(1), "EOF") != 0){
        char *str1 = NULL, *str2 = NULL, *ch1 = NULL;
        if(strcmp(input, "insercao") == 0){
            str1 = readword(stdin, ' ');
            str2 = readline(stdin);
            insertEntry(sl, str1, str2);
        }else if(strcmp(input, "alteracao") == 0){
            str1 = readword(stdin, ' ');
            str2 = readline(stdin);
            updateEntry(sl, str1, str2);
        }else if(strcmp(input, "remocao") == 0){
            str1 = readline(stdin);
            removeEntry(sl, str1);
        }else if(strcmp(input, "busca") == 0){
            str1 = readline(stdin);
            search(sl, str1, true);
        }else if(strcmp(input, "impressao") == 0){
            ch1 = readline(stdin); //ch1 é do tipo "c\n"
            printSkiplist(sl, ch1);
        }else{
            printf("Opção não encontrada!\n");
        }

        free(input);
        free(str1);
        free(str2);
        free(ch1);
    }

    freeList(sl);
    return 0;
}