#include <stdio.h>
#include <stdlib.h>

int main(){
      double* stack = malloc(sizeof(double));
      int stackTop = 0;
      char character;
      double number;
      while((character = getchar()) != EOF){
            if(character < 58 && character > 47){
                  ungetc(character, stdin);
                  scanf("%lf", &number);
                  stackTop++;
                  stack = realloc(stack, sizeof(double) * stackTop);
                  stack[stackTop-1] = number;
            }else{
                  if(character == '+'){
                        stack[stackTop-2] = stack[stackTop-2] + stack[stackTop-1];
                        stack = realloc(stack, sizeof(double) * --stackTop);
                  }else if(character == '/'){
                        stack[stackTop-2] = stack[stackTop-2] / stack[stackTop-1];
                        stack = realloc(stack, sizeof(double) * --stackTop);
                  }else if(character == '-'){
                        stack[stackTop-2] = stack[stackTop-2] - stack[stackTop-1];
                        stack = realloc(stack, sizeof(double) * --stackTop);
                  }else if(character == '*'){
                        stack[stackTop-2] = stack[stackTop-2] * stack[stackTop-1];
                        stack = realloc(stack, sizeof(double) * --stackTop);
                  }
            }
      }
      printf("Resultado: %lf\n", stack[0]);
      free(stack);
      return 0;
}
