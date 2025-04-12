#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readString.h"
#include "data.h"

int main(){
    //variables for reading
    char** read = malloc(sizeof(char*));
    int posRead = 0;
    char c;

    wordList* data = malloc(sizeof(wordList));

    int newItem;                //1 if theres a new word. 0 if the word is repeated
    int totalWords = 0;         //counts the total of words in the text
    int newLineController = 1;  //dont let the code print a \n in the first iteration 
    int isNum = 0;              //decides if the code should read a number or a text
    int toBePrinted;            //reads the number of words that should be printed

    while ((c = getchar()) != EOF){
        if(isNum == 0){
            posRead++;
            read = realloc(read, sizeof(char*) * posRead);
            ungetc(c, stdin);
            read[posRead - 1] = readString(&isNum);
            newItem = 1;
            for(int i = 0; i < totalWords; i++){
                if(strcmp(data[i].word, read[posRead-1]) == 0){
                    newItem = 0;
                    data[i].n ++;
                }
            }
            if(newItem == 1){
                totalWords++;
                data = realloc(data, sizeof(wordList) * totalWords); 
                data[totalWords-1].word = malloc(sizeof(char) * strlen(read[posRead - 1]) + 1);
                strcpy(data[totalWords-1].word, read[posRead-1]);
                data[totalWords-1].n = 1;
            }    
        }else{
            ungetc(c, stdin);
            scanf("%d", &toBePrinted);

            //\r identifier 
            char newLineEater = getchar();
            if(newLineEater == '\r')
                newLineEater = getchar();
            else if(newLineEater == EOF)
                ungetc(EOF, stdin);

            //controls new lines when printing
            if(newLineController == 1)
                newLineController = 0;
            else
                printf("\n");

            data = insertionSort(data, totalWords);
            if(totalWords < toBePrinted)
                toBePrinted = totalWords;
            for(int i = 0; i < toBePrinted; i++){
                printf("%s ", data[i].word);
                printf("%d\n", data[i].n);
            }
            totalWords = 0;
            isNum = 0;
        }
    }

    for (int i = 0; i < totalWords; i++){
        free(data[i].word);
    }
    free(data);

    for(int i = 0; i < posRead; i++)
        free(read[i]);
    free(read);
    
    return 0;
}