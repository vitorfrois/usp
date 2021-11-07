#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int nCharsInLine = 0;
int nLettersWord = 0;
int spam = 0;
char character;
char *word;


void checkWord(){
      memset(word, 0, strlen(word));
      nLettersWord = 0;
      word = realloc(word, sizeof(char));
}

int main(){
      int nLines;
      scanf("%d", &nLines);
      char text[nLines];
      word = malloc(sizeof(char));
      int i = 0;
      while(i < nLines){
            while((character = getchar()) != EOF){
                  if((character == '\n')){
                        text[i] = word;
                        i++;
                        checkWord();
                        if(nCharsInLine > 76)
                              spam += 2;
                        nCharsInLine = 0;
                  }else{
                        word[nCharsInLine] = character;
                        word = realloc(word, nCharsInLine * sizeof(char));
                  }
                  nCharsInLine++;
            }

      }
      for(int i = 0; i < nLines; i++){
            printf("%s", text[i]);
      }
      free(word);
      return 0;
}
