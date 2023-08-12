#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "myString.h"

void inputProcessing(){
    char c;
    int i = 0;
    do{
        printf("I = %d; ", i++);
        scanf("%c", &c);
        if(c == '\n') printf("barra ene\n");
        if(c == '\r') printf("barra erre\n");
    }while(c == '\n' || c == '\r');
    fputc(c, stdin);
}

int stringEnd(int numSeparators, char separatorArray[], char c){
    int end = 0;
    for(int i = 0; i < numSeparators; i++)
        if(c == separatorArray[i]) end = 1;

    return end;
}

char *readString(FILE *stream, bool *reachEOF){
    //Caso a entrada seja nula, retorna
    if(!stream){
        printf("Entrada nula!\n");
        return NULL;
    }

    //Armazena os separadores em um vetor de separadores
    char separatorArray[] = {'\n', EOF, '\r'};
    int numSeparators = (int) sizeof(separatorArray);

    //Declaração de variáveis
    int currentLenght = 0, step = 20;
    char c, *string = malloc(sizeof(char) * step);
    //Lê a palavra até encontrar um separador
    do{
        c = fgetc(stream);
        if (currentLenght >= step)
        {
            step *= 2;
            string = realloc(string, (step + 1) * sizeof(char *));
        }
        string[currentLenght] = c;
        currentLenght++;
    } while (stringEnd(numSeparators, separatorArray, c) != 1);

    if(c == EOF)
        *reachEOF = true;

    //Últimos ajustes e retorna a string lida
    string[currentLenght-1] = '\0';
    string = realloc(string, (currentLenght-1) * sizeof(char *));
    return string;
}



char* readString2(int numSeparators, ...){
    //Armazena os separadores em um vetor de separadores
    va_list args;
    va_start(args, numSeparators);
    char separatorArray[numSeparators];
    for(int i = 0; i < numSeparators; i++)
        separatorArray[i] = va_arg(args, int);

    //Declaração de variáveis
    int currentLenght = 0, step = 20;
    char c, *string = malloc(sizeof(char) * step);
    //Lê a palavra até encontrar um separador
    do{
        c = getchar();
        if(currentLenght >= step){
            step *= 2;
            string = realloc(string, (step+1) * sizeof(char*));
        }
        string[currentLenght] = c;
        currentLenght++;
    }while(stringEnd(numSeparators, separatorArray, c) != 1);
    
    //Joga fora todos separadores após a palavra
    if(c == '\r')
        getchar();

    //Últimos ajustes e retorna a string lida
    string[currentLenght - 1] = '\0';
    string = realloc(string, (currentLenght+1) * sizeof(char*));
    va_end(args);
    return string;
}