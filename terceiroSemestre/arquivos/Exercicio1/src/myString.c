#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "../includes/myString.h"

int stringEnd(int numSeparators, char separatorArray[], char c){
    int end = 0;
    for(int i = 0; i < numSeparators; i++)
        if(c == separatorArray[i]) end = 1;

    return end;
}

char *readFixedSizeString(FILE *fp, int stringSize){
    //Armazena os separadores em um vetor de separadores
    char separatorArray[] = {'\n', EOF, '\r'};
    int numSeparators = (int) sizeof(separatorArray);

    //Declaração de variáveis
    int currentLenght = 1;
    char c, *string = malloc(sizeof(char) * stringSize);

    //Lê a palavra até encontrar um separador
    c = getchar();
    do{
        fputc(c, fp);
        c = getchar();
        currentLenght++;
    } while (stringEnd(numSeparators, separatorArray, c) != 1);

    //Últimos ajustes e retorna a string lida
    fputc('\0', fp);
    for(int i = currentLenght; i < stringSize; i++)
        fputc('$', fp);

    // string[stringSize-1] = '\0';

    return string;
}

char *readString(){
    //Armazena os separadores em um vetor de separadores
    char separatorArray[] = {'\n', EOF, '\r'};
    int numSeparators = (int) sizeof(separatorArray);

    //Declaração de variáveis
    int currentLenght = 0, step = 20;
    char c, *string = malloc(sizeof(char) * step);

    //Lê a palavra até encontrar um separador
    do{
        c = getchar();
        if (currentLenght >= step)
        {
            step *= 2;
            string = realloc(string, (step + 1) * sizeof(char *));
        }
        string[currentLenght] = c;
        currentLenght++;
    } while (stringEnd(numSeparators, separatorArray, c) != 1);

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