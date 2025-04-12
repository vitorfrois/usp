#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

int main(){
    int nOperations, nPolynomial;
    scanf("%d", &nOperations);
    List** polynomial = (List**) malloc(sizeof(List*)); 
    for(int i = 0; i < nOperations; i++){
        scanf("%d\n", &nPolynomial);
        polynomial = (List**) realloc(polynomial, sizeof(List*) * nPolynomial); 
        for(int j = 0; j < nPolynomial; j++)         
            polynomial[j] = readPolynomial();
        
        List* result = addPolynomials(polynomial, nPolynomial);
        print(result);
        freeList(result);
        for(int j = 0; j < nPolynomial; j++)
            freeList(polynomial[j]);
    }
    free(polynomial);
    return 0;
}