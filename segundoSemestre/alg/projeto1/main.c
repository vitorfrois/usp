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

    int line = 1;
    char *input;
    double time_taken;
    clock_t t, totalTime = 0;
    while(strcmp(input = readString(1), "EOF") != 0){
        //printf("%d:", line++);
        char *str1, *str2, *ch1; 
        t = clock();

        if(strcmp(input, "insercao") == 0){
            str1 = readword(stdin, ' ');
            str2 = readline(stdin);

            // printf("inserindo '%s': '%s'\n", str1, str2);
            insertEntry(sl, str1, str2);
        }else if(strcmp(input, "alteracao") == 0){
            str1 = readword(stdin, ' ');
            str2 = readline(stdin);

            updateEntry(sl, str1, str2);
            free(str1);
        }else if(strcmp(input, "remocao") == 0){
            str1 = readline(stdin);

            removeEntry(sl, str1);
            free(str1);
        }else if(strcmp(input, "busca") == 0){
            str1 = readline(stdin);

            search(sl, str1);
            free(str1);
        }else if(strcmp(input, "impressao") == 0){
            ch1 = readline(stdin); //ch1 é do tipo "c\n"

            printSkiplist(sl, ch1);
            free(ch1);
        }else{
            printf("Opção não encontrada!\n");
        }

        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf(" -> %s took %f seconds \n", input, time_taken); 

        free(input);
    }

    freeSkipList(sl);

    return 0;
}