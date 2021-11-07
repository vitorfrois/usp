#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myString.h"

char* readString(int separator){
    //printf("reading string... ");
    int arguments;
    
    char* string = malloc(sizeof(char));
    char character = 'o';
    int nCharsString = 0;
    do {
        character = getchar();
        string = realloc(string, (nCharsString + 1) * sizeof(char*));
        string[nCharsString] = character;
        nCharsString++;

        if(separator == 1) arguments = character != '\n' && character != ' ' && character != EOF && character != '\r';
        else if(separator == 0) arguments = character != '\n' && character != EOF && character != '\r';
    } while(arguments);
    if(character == EOF)
        return "EOF";
    if(character == '\r')
        getchar();
    string[nCharsString - 1] = '\0';
    return string;
}