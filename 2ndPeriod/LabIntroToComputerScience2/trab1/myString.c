#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myString.h"

char* readString(){
    //printf("reading string... ");
    char* string = malloc(sizeof(char));
    char character = 'o';
    int nCharsString = 0;
    do {
        character = getchar();
        string = realloc(string, (nCharsString + 1) * sizeof(char*));
        string[nCharsString] = character;
        nCharsString++;
    } while(character != '\r' && character != '\n' && character != EOF);
    if(character == '\r' || character == '\n')
        if((character = getchar()) != '\n')
            ungetc(character, stdin);
    string[nCharsString - 1] = '\0';
    return string;
}