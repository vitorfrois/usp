#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char* insensitiveReadLine();
char* textFilter(char*);
bool palindromeCheck(char*);

int main(){
      char* text = insensitiveReadLine();
      if(palindromeCheck(text) == true){
            printf("Palindromo direto\n");
            exit(1);
      }

      //retirar '/' e ' '
      text = textFilter(text);
      text = realloc(text, sizeof(char) * strlen(text)+1);

      if(palindromeCheck(text) == true){
            printf("Palindromo indireto\n");
      }else{
            printf("Nao eh um palindromo\n");
      }
      free(text);
      return 0;
}

char* insensitiveReadLine(){
      char *text = malloc(sizeof(char));
      char character = 't';
      int nCharsInLine = 1;
      while((character = getchar()) != '\n'){
            if(character > 64 && character < 91)
                  character += 32;
                  //transforma qualquer caractere minusculo em maiusculo
            text[nCharsInLine-1] = character;
            nCharsInLine++;
            text = realloc(text, nCharsInLine * sizeof(char));
      }
      if(text[nCharsInLine-2] == '.'){
            text[nCharsInLine - 2] = '\0';
      }else{
            text[nCharsInLine - 1] = '\0';
      }
      return text;
}

char* textFilter(char* text){
      char *newText = malloc(sizeof(char));
      int nCharsInLine = 1;
      for(int i = 0; i < strlen(text); i++){
            bool alfanum = (
                  (text[i] > 96 && text[i] < 123) ||
                  (text[i] > 47 && text[i] < 57)
            );
            if(alfanum == true){
                  newText[nCharsInLine-1] = text[i];
                  nCharsInLine++;
                  newText = realloc(newText, nCharsInLine * sizeof(char));
            }
      }
      newText[nCharsInLine] = '\0';
      free(text);
      return newText;
}

bool palindromeCheck(char* text){
      size_t lenght = strlen(text);
      for(int i = 0; i < lenght/2; i++){
             if(text[i] != text[lenght-i-1]){
                  return false;
             }
      }
      return true;
}
