#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readString.h"

char* readString(int* isNum){
    char *string = malloc(sizeof(char));
    char character = 'o';
    int nCharsString = 0;
    do {
        character = getchar();
        string = realloc(string, (nCharsString + 1) * sizeof(char));
        string[nCharsString] = character;
        nCharsString++;
    } while(character != ' ' && character != '\n' && character != '\r' && character != EOF);
    string[nCharsString - 1] = '\0';
    if(character == '\r')
        character = getchar();

    if(character == '\n' || character == '\r' || character == EOF){
        *isNum = 1;
        ungetc(character, stdin);
    }
    return string;
}