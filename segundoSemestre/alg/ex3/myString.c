#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readString(int size){
    char* string = malloc(sizeof(char) * size);
    char character = 'o';
    int nCharsString = 0;
    do {
        character = getchar();
        if(nCharsString < size)
            string[nCharsString] = character;
        nCharsString++;
    } while(character != '\n' && character != EOF && character != '\r');
    if(character == EOF){
        ungetc(EOF, stdin);
        //printf("foi lido eof\n");
    }
    string[nCharsString - 1] = '\0';
    return string;
}

char* replaceString(char* text, char* error, char* adjust){
    int sameString = 1;
    int i, j, a, b, c;
    char finalText[100];

    int textSize = strlen(text);
    int errorSize = strlen(error);
    int adjustSize = strlen(adjust);
    int finalTextSize = textSize;
    for(i = 0; i < textSize; i++){
        if(text[i] == error[0]){
            //printf("first letter confere\b");
            //if the first letter is equal, check the entire word
            for(j = 1; j < errorSize; j++){
                //printf("(%c) = (%c)?\b", text[i+j], error[j]);
                if(text[i + j] != error[j]){
                    sameString = 0;
                }
            }
            if(sameString == 1){
                // final string will be (text[0]-text[i-1] + adjust + text[i+j]-text[textSize])
                //  string: a | b | c
                //          a: iterate until the error
                //          b: iterate the adjust
                //          c: iterate after the error

                finalTextSize -= errorSize;
                finalTextSize += adjustSize;
                for(a = 0; a < i; a++)
                    finalText[a] = text[a];
                for(b = 0; b < adjustSize; b++)
                    finalText[a+b] = adjust[b];
                for(c = 0; c < (textSize - (errorSize + a)); c++)
                    finalText[a+b+c] = text[a+errorSize+c];
                strcpy(text, finalText);
                // text = realloc(text, finalTextSize);
                    
                textSize = strlen(text);
                text[finalTextSize] = '\0'; 
                sameString = 1;
            }
        }
        sameString = 1;
    }
    return text;
}