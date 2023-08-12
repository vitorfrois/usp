#include <stdio.h>
#include <stdbool.h>

int main(){
      bool lastWasChar = false; //stands for: LAST input WAS a CHAR ?
      int nChars = 0;
      int nLines = 0;
      int nWords = 0;
      char character;
      char oldChar;

      while((character = getchar()) != EOF){
            if(character == ' '){
                  lastWasChar = false;
            }else if(character == '\t'){
                  lastWasChar = false;
            }else if((character == '\n')){
                  if(oldChar != '\r')
                        nLines++;
                  lastWasChar = false;
            }else if((character == '\r')){
                  nLines++;
                  lastWasChar = false;
            }else{
                  if(lastWasChar == false)
                        nWords++;
                  lastWasChar = true;
            }
            nChars++;
            oldChar = character;
      }

      printf("Linhas\tPalav.\tCarac.\n");
      printf("%d\t%d\t%d\n", nLines, nWords, nChars);
      return 0;
}
