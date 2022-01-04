#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myString.h"

char* readString(){
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
    } while(arguments = character != '\n' && character != ' ' && character != EOF && character != '\r');
    if(character == EOF)
        return "EOF";
    if(character == '\r')
        getchar();
    string[nCharsString - 1] = '\0';
    return string;
}
