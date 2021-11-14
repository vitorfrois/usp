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
    // input = malloc(sizeof(char) * 15);
    // str1 = malloc(sizeof(char) * 50);
    // str2 = malloc(sizeof(char) * 140);
    // ch1 = malloc(sizeof(char) * 5);
    char *str1, *str2, *ch1;
    while(strcmp(input = readString(1), "EOF") != 0){
        //printf("|%s|\n", input);
        if(strcmp(input, "insercao") == 0){
            str1 = readString(1);
            str2 = readString(0);
            insertEntry(sl, str1, str2);
        }else if(strcmp(input, "alteracao") == 0){
            str1 = readString(1);
            str2 = readString(0);
            updateEntry(sl, str1, str2);
        }else if(strcmp(input, "remocao") == 0){
            str1 = readString(1);
            removeEntry(sl, str1);
        }else if(strcmp(input, "busca") == 0){
            str1 = readString(1);
            search(sl, str1, true);
        }else if(strcmp(input, "impressao") == 0){
            ch1 = readString(0); //ch1 é do tipo "c\n"
            printSkiplist(sl, ch1);
        }else{
            printf("Opção não encontrada!\n");
        }
        // free(str1);
        // free(str2);
        // free(ch1);
    }
    
    free(ch1);
    //freeList(sl);
    return 0;
}