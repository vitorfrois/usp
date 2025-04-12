#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myString.h"

int main(){
    char c;
    char *text, *error, *adjust;
    int textSize, finalTextSize;
    char finalText[100];
    
    while((c = getchar()) != EOF){
        ungetc(c, stdin);
        //printf("|%c|\n", c);
        text = readString(100);
        error = readString(20);
        adjust = readString(20);
        //printf("|%s|;|%s|;|%s|;\n", text, error, adjust);
        text = replaceString(text, error, adjust);

        printf("%s", text);
        printf("\n");

        textSize = strlen(text) + 1;
        for(int i = 0; i < textSize; i++)
            text[i] = '\0';

        finalTextSize = strlen(finalText) + 1;
        for(int i = 0; i < finalTextSize; i++)
            finalText[i] = '\0';
        //printf("pera la ne\n");
    };
    free(text);
    free(error);
    free(adjust);

    return 0;
}