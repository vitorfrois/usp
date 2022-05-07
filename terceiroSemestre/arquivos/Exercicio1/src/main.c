#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/myString.h"
#include "../includes/person.h"
#include "../includes/funcoesFornecidas.h"

#define WRITE 1
#define PRINT 2
#define READ 3
#define SKIPSIZE 238

int main(){
    int command;
    scanf("%d", &command);
    char pathname[30], filename[15];
    strcpy(pathname, "binarios/");
    scanf("%s", filename);
    strcat(pathname, filename);
    FILE *fp;
    if(command == WRITE){
        fp = fopen(pathname, "w+");
        int nInputs;
        scanf("%d", &nInputs);
        for(int i = 0; i < nInputs; i++)
            inputPerson(fp);
        fclose(fp);
        binarioNaTela(pathname);
    }else if(command == PRINT){
        fp = fopen(pathname, "r+");
        if(fp == NULL){
            printf("Falha no processamento do arquivo");
            exit(0);
        }
        int numRecords = numRecordsCalculator(fp);
        for(int i = 0; i < numRecords; i++)
            printPerson(fp);
        fclose(fp);
    }else if(command == READ){
        fp = fopen(pathname, "r+");
        if(fp == NULL){
            printf("Falha no processamento do arquivo");
            exit(0);
        }
        int rrn;
        scanf("%d", &rrn);
        fseek(fp, rrn * SKIPSIZE, SEEK_SET); 
        printPerson(fp);
        fclose(fp);
    }
}