#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int nCharsInLine = 0;
int nLettersWord = 1;
int spam = 0;
char character;
char *word;
char *tabooWord;

int main(){
      int tabooCount = 0;
      word = malloc(1 * sizeof(char));
      tabooWord = malloc(sizeof(char));
      scanf("%s\n", tabooWord);
      char tabooFirstLetter = tabooWord[0];
      char string[strlen(tabooWord)];
      while((character = getchar()) != '$'){
            if(character == tabooFirstLetter){
                  string[0] = tabooFirstLetter;
                  for(int i = 1; i < strlen(tabooWord); i++){
                        character = getchar();
                        string[i] = character;
                  }
                  string[strlen(tabooWord)] = '\0';
                  if(strcmp(string, tabooWord) != 0){
                        for(int i = strlen(tabooWord)-1; i > 0; i--){
                              ungetc(string[i], stdin);
                        }
                        nLettersWord++;
                        word = realloc(word, sizeof(char) * nLettersWord);
                        word[strlen(word)] = string[0];
                  }else{
                        tabooCount++;
                  }
            }else{
                  word = realloc(word, sizeof(char) * nLettersWord);
                  word[nLettersWord-1] = character;
                  nLettersWord++;

            }
      }
      printf("A palavra tabu foi encontrada %d vezes\nFrase: %s\n",
            tabooCount,
            word
      );
      return 0;
}
