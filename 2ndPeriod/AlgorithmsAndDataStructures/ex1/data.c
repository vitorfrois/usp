#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

void dataCpy(wordList* a, wordList* b){
    a->word = malloc(sizeof(char) * strlen(b->word) + 1);
    strcpy(a->word, b->word);
    a->n = b->n;
}

int dataCmp(wordList* a, wordList* b){
    if(a->n < b->n)
        return 1;
    else if(a->n > b->n)
        return 0;
    else if(a->n == b->n){
        if(strcmp(a->word, b->word) > 0)
            return 1;
        else
            return 0;
    }
    return -1;
}

wordList* insertionSort(wordList* data, int totalWords){
    wordList aux;
    int i, j;
    for (i = 1; i < totalWords; i++) {
        dataCpy(&aux, &data[i]);
        j = i - 1;

        while (j >= 0 && dataCmp(&data[j], &aux)) {
            dataCpy(&data[j+1], &data[j]);
            j--;
        }
        dataCpy(&data[j+1], &aux);
    }
    return data;
}