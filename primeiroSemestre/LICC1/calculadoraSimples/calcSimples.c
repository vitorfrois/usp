#include <stdio.h>

int main(){
      float a, b;
      char operation;
      scanf("%f %c %f", &a, &operation, &b);
      switch (operation){
            case '+':
                  printf("%.6f", a+b);
                  break;
            case '-':
                  printf("%.6f", a-b);
                  break;
            case '*':
                  printf("%.6f", a*b);
                  break;
            case '/':
                  printf("%.6f", a/b);
                  break;
            case '%':
                  printf("%.6f", (a/b)*100);
                  break;
            default:
                  printf("Caractere não reconhecido.");
                  break;

      }

}
