#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inverso.h"

llint euclides(llint a, llint b, llint* x, llint* y){
    // Considere a equação 
    // (a*x)+(b*y)=1
    // a e b são divisores do número A em AX⁻¹≃(mod m)
    // com m sendo o módulo passado.
    // Quando o AEE=1 e a=0, os valores de x e y para 
    // encontrar a equação podem ser obtidos recursivamente
    // sabendo que: 
    // --> novo x = y - (b / a) * x
    // --> novo y = x
    
    if(a == 0){
        *x = 0;
        printf("x = 0\n");
        *y = 1;
        return b;
    }
    
    llint newX, newY;
    //chamadas recursivas do algoritmo com novos valores
    int gcd = euclides(b%a, a, &newX, &newY);
    
    //encontra e retorna por referência novos valores de x e y
    *x = newY - (b/a)*newX;
    printf("x = %lld - (%lld/%lld) * %lld = %lld\n", newY, b, a, newX, *x);
    *y = newX;
    printf("y = %lld\n", *y);
    printf("(%lld*%lld)+(%lld*%lld)=1\n\n", a, *x, b, *y);

    return gcd;
}

void inverso(llint a, llint m){
    llint x, y;
    int mdc = euclides(a, m, &x, &y);
    if(mdc != 1){
        printf("\n\nO inverso de %lld em %lldZ é inexistente,\n", a, m);
        printf("dado que os números não são primos entre si.\n");
        printf("AEE(%lld, %lld) = %d", a, m, mdc);
    }else{
        //É feito um tratamento para casos em que o x é negativo,
        //considerando que o sistema Zm é circular.
        if(x < 0)
            printf("Houve um tratamento para tornar o coeficiente %lld positivo.\n", x);
        x = (x % m + m)%m;
        printf("\n\nO inverso de %lld em %lldZ é %lld.", a, m, x);
    }
}
