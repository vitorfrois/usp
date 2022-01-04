#include <stdio.h>
#include <stdlib.h>

int calc_modulo(int a, int r, int m){
    int oldAux = 1, aux;
    printf("Pelo método indutivo, após sucessivas operações de módulo,\n"); 
    printf("encontra-se o resultado final da equação inicial.\n");
    printf("É preciso efetuar %u operações para encontrar o valor procurado.\n", r);
    for(int i = 0; i < r; i++){
        aux = (oldAux * a) % m;
        //printf("%u * %u(mod %u) = %u\n", oldAux, a, m, aux);
        oldAux = aux;
    }
    return aux;
}

int main(int argc, char *argv[]){
    char *p;
    unsigned int a = strtoul(argv[1], &p, 10);
    unsigned int r = strtoul(argv[2], &p, 10);
    unsigned int m = strtoul(argv[3], &p, 10);
    unsigned int resultado = calc_modulo(a, r, m);
    printf("\n\n%u^%u(mod %u) = %u\n", a, r, m, resultado);
    return 0;
}

