#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "myString.h"

int main(){
    int nOperations, nPolynomial;
    scanf("%d\n", &nOperations);
    char *input;
    for(int i = 0; i < nOperations; i++){
        input = readString();
        List* num1 = readNumber();
        List* num2 = readNumber();
        if(strcmp(input, "SUM") == 0){
            List* result = addNumbers(num1, num2);
            print(result, 1);
        }else if(strcmp(input, "BIG") == 0){
            printf("%d\n", big(num1, num2));
        }else if(strcmp(input, "SML") == 0){
            printf("%d\n", big(num2, num1));
        }else if(strcmp(input, "EQL") == 0){
            printf("%d\n", eql(num1, num2));
        }
    }
    return 0;
}