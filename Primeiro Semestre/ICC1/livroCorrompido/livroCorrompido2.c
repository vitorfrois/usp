//livro corrompido por vitor frois

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//the readline function returns the adress of each input line
char* readLine(){
      char *word = malloc(sizeof(char));
      char character = 't';
      int nCharsInLine = 0;
      while(character != '\n'){
            character = getchar();
            word[nCharsInLine] = character;
            nCharsInLine++;
            word = realloc(word, nCharsInLine * sizeof(char));
      }
      word[nCharsInLine - 1] = '\0';
      return word;
}

int main(){
      int nLines;
      scanf("%d\n", &nLines);
      char* text[nLines];

      //stores the adresses of lines in the text array
      for (int i = 0; i < nLines; i++){
            text[i] = readLine();
      }

      //print the chosen lines
      int nLinesToPrint;
      scanf("%d", &nLinesToPrint);
      for(int i = 0, lineToPrint; i < nLinesToPrint; i++){
            scanf("%d", &lineToPrint);
            printf("%s\n", text[lineToPrint]);
      }

      for (int i = 0; i < nLines; i++){
            free(text[i]);
      }
      return 0;
}
