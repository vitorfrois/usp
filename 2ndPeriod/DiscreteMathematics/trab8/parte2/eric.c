#include <stdio.h>
#include <stdlib.h>
typedef long long int llint;


/* 
    Cálculo do máximo divisor comum,  
    usando o algoritimo de Euclides estendido
    @param n numerador 
    @param d denominador 
*/
llint algEuclides(llint n ,llint d, llint *i, llint *j) {
  
    //Caso base
    if(n % d == 0){ 
        *i=0; *j=1;
        
        printf("\n|----CASO BASE----|\n");
        printf("O MDC é %lld\n",d);
        printf("Inicio do calculo de * e j\n");
        printf("Definindo i=0 e j=1\n\n");

        return d;
    }
        
    printf("\v----NOVO PASSO----\n");
    printf("n=%lld, d=%lld, r=%lld\n", n, d, (n % d));

    //Retorno da recurção e cálculo de i e j
    printf("----RETORNANDO COM----\n");
    
    llint novo_i, novo_j;
    llint mdc = algEuclides(d%n, n, &novo_i, &novo_j);
    *i = novo_j - (d/n)*novo_i;
    *j = novo_i;

    printf(" i = %lld , j = %lld\n",i ,j);
    return mdc;    
}

llint inverso(llint n, llint d){
    llint i, j;
    int mdc = algEuclides(n, d, &i, &j);
    if(mdc != 1){
        printf("não são primos entre si\n");
        return -1;   
    }else{
        i = (i % d + d)%d;
        return i;
    }

}