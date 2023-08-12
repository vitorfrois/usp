#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "myString.h"

int main(){
    List *l = newList();
    
    int id;
    char* name;

    char* input;
    while(strcmp(input = readString(1), "EOF") != 0){
        //printf("input = |%s|\n", input);
        if(strcmp(input, "INSERE") == 0){
            scanf("%d ", &id);
            name = readString(0);
            //printf("id = %d, nome = %s\n", id, name);
            insert(l, id, name);
        }else if(strcmp(input, "IMPRIMIR") == 0){
            print(l);
        }else if(strcmp(input, "REMOVE") == 0){
            scanf("%d\n", &id);
            removeItem(l, id);
        }else{
            printf("opção não encontrada!\n");
        }
    }

    freeList(l);
    return 0;
}
