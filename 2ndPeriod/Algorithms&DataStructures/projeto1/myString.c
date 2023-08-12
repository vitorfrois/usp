#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myString.h"

char *readline(FILE *stream) {
    if(!stream) return NULL;

    int lenght = 20;
    char *str = malloc(sizeof(char) * lenght);
    int char_cnt = 0;

    while(1) {
        if (char_cnt == lenght) {
            lenght *= 2;
            str = realloc(str, sizeof(char) * lenght);
        }

        char c = fgetc(stream);

        if (c == '\r') continue;

        if (c == '\n' || c == EOF) {
            str[char_cnt] = '\0';
            break;
        }

        str[char_cnt] = c;
        char_cnt++;
    }

    str = realloc(str, sizeof(char) * (char_cnt + 1));

    return str;
}

char *readword(FILE *stream, char sep) {
    if(!stream) return NULL;

    int lenght = 20;
    char *str = malloc(sizeof(char) * lenght);
    int char_cnt = 0;

    while(1) {
        if (char_cnt == lenght) {
            lenght *= 2;
            str = realloc(str, sizeof(char) * lenght);
        }

        char c = fgetc(stream);

        if (c == '\r') continue;

        if (c == sep || c == '\n' || c == EOF) {
            str[char_cnt] = '\0';
            break;
        }

        str[char_cnt] = c;
        char_cnt++;
    }

    str = realloc(str, sizeof(char) * (char_cnt + 1));

    return str;
}

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

        if(separator == 1) arguments = (character != '\n' && character != ' ' && character != EOF && character != '\r');
        else if(separator == 0) arguments = (character != '\n' && character != EOF && character != '\r');
    } while(arguments);
    
    if(character == EOF) {
        free(string);
        return "EOF";
    }
    if(character == '\r')
        getchar();
    string[nCharsString - 1] = '\0';
    return string;
}
