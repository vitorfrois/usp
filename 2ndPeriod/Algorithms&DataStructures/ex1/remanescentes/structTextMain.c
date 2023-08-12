#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readString(int* isNum){
      char *string = malloc(sizeof(char));
      char character = 'o';
      int nCharsString = 0;
      do {
            character = getchar();
            string = realloc(string, (nCharsString + 1) * sizeof(char));
            string[nCharsString] = character;
            nCharsString++;
      } while(character != ' ' && character != '\n' && character != '\r');
      string[nCharsString - 1] = '\0';
      if(character == '\n'){
        ungetc('\n', stdin);
        *isNum = 1;
      }
      return string;
}

typedef struct {
    int n;
    char* word;
}wordList;

typedef struct{
    int nTexts;
    int* nWords;
    int* toBePrinted;
    wordList* data;
}textList;

void dataCpy(wordList* a, wordList* b){
    a->word = malloc(sizeof(char) * strlen(b->word) + 1);
    strcpy(a->word, b->word);
    a->n = b->n;
}

int dataCmp(wordList* a, wordList* b){
    if(a->n > b->n)
        return 1;
    else if(a->n < b->n)
        return 0;
    else if(a->n == b->n){
        if(strcmp(a->word, b->word) == 1)
            return 1;
        else
            return 0;
    }
    return -1;
}

int main(){
    
    char** read = malloc(sizeof(char*));
    char c;
    int posRead = 0;
    textList* texts = malloc(sizeof(textList));
    texts->data = malloc(sizeof(wordList));
    texts->nWords = malloc(sizeof(int));
    int totalWords = 0;
    int newItem;
    texts->toBePrinted = malloc(sizeof(int));
    texts->nTexts = 1;
    int isNum = 0;
    while ((c = getchar()) != EOF){
        if(isNum == 0){
            posRead++;
            read = realloc(read, sizeof(char*) * posRead);
            ungetc(c, stdin);
            read[posRead - 1] = readString(&isNum);
            newItem = 1;
            for(int i = 0; i < totalWords; i++){
                if(strcmp(texts[texts->nTexts - 1].data[i].word, read[posRead-1]) == 0){
                    newItem = 0;
                    texts[texts->nTexts - 1].data[i].n ++;
                }
            }
            if(newItem == 1){
                totalWords++;
                texts[texts->nTexts - 1].data = realloc(texts[texts->nTexts - 1].data, sizeof(wordList) * totalWords); 
                texts[texts->nTexts - 1].data[totalWords-1].word = malloc(sizeof(char) * strlen(read[posRead - 1]) + 1);
                strcpy(texts[texts->nTexts - 1].data[totalWords-1].word, read[posRead-1]);
                texts[texts->nTexts - 1].data[totalWords-1].n = 1;
            }    
        }else{
            totalWords = 0;
            ungetc(c, stdin);
            texts->nTexts++;
            texts->nWords = realloc(texts->nWords, sizeof(int) * texts->nTexts);
            texts[texts->nTexts - 1].nWords = &totalWords; 
            texts[texts->nTexts - 1].toBePrinted = realloc(texts[texts->nTexts - 1].toBePrinted, sizeof(int) * texts->nTexts);
            scanf("%d\n", &texts[texts->nTexts - 1].toBePrinted[texts->nTexts-1]);
            isNum = 0;
        }
    }
    printf("nTexts = %d\n", texts[texts->nTexts].nTexts);
    for(int i = 0; i < texts->nTexts; i++){
        printf("%d\n", texts->toBePrinted[i]);
    }

    wordList aux;
    int i, j;
    for (i = 1; i < totalWords; i++) {
        dataCpy(&aux, &texts->data[i]);
        j = i - 1;
        
        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && dataCmp(&texts->data[j], &aux)) {
            dataCpy(&texts->data[j+1], &texts->data[j]);
            j--;
        }
        dataCpy(&texts->data[j+1], &aux);
    }    

    for(int i = 0; i < totalWords; i++){
        printf("%s ", texts->data[i].word);
        printf("%d\n", texts->data[i].n);
    }   

    for (int i = 0; i < totalWords; i++){
        free(texts->data[i].word);
    }
    free(texts->data);

    for(int i = 0; i < posRead; i++)
        free(read[i]);
    free(read);
    
    return 0;
}