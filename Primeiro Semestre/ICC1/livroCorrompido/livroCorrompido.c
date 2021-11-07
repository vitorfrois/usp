#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int nCharsInLine = 0;
int nLettersWord = 0;
int spam = 0;
char character;
char *text;


int main(){
      int nLines;
      scanf("%d", &nLines);
      printf("cringe");
      text = malloc(sizeof(char));
      printf("cringe");
      char* page[nLines];

      for(int i = 0; i < nLines; i++){
            printf("penis");
            while((character = getchar()) != '\n'){
                  text[nCharsInLine] = character;
                  nCharsInLine++;
                  text = realloc(text, nCharsInLine * sizeof(char));
            }
            nCharsInLine = 0;
            strcpy(page[i], text);
      }

      for(int i = 0; i < nLines; i++){
            printf("%s\n", page[i]);
      }

      free(text);
      return 0;
}
