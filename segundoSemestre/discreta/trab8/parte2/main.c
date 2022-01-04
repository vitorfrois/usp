/**
 * @file main.c
 * @author Vítor Amorim Fróis (frois@usp.br)
 * @brief O programa abaixo encripta uma mensagem inserida através
 *        do método RSA. Foram pré escolhidos números primos para o
 *        funcionamento do programa. A função calc_modulo utilizada 
 *        no trabalho 7 foi aprimorada aqui para poder trabalhar
 *        com números maiores no cálculo do módulo.
 * @date 10-12-2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef long long int llint;

typedef struct DADOS{
    llint p, q, n, phi, e, f;
}Dados;

llint calc_modulo(llint a, llint r, llint m);
llint euclides(llint a, llint b, llint* x, llint* y);
llint inverso(llint a, llint m);

int main(int argc, char *argv[]){
    //Tratamento da entrada
    char input = argv[1][0];
    llint mensagem = (llint) atoll(argv[2]);
    if(argc != 3){
        printf("'c' para codificar\n");
        printf("'d' para decodificar\n");
        printf("./main x xxxx\n");
        return 0;
    }

    //Dados do rsa
    Dados rsa;
    //p e q primos > 100 escolhidos a mão
    rsa.p = 101;
    rsa.q = 317;
    rsa.n = rsa.p * rsa.q;
    rsa.phi = (rsa.p-1)*(rsa.q-1);
    rsa.e = 129; 
    //Para calcular o módulo, a cada iteração do while, caso ele seja ímpar,
    //mais operações devem ser executadas. Assim, é bom escolher um número da
    //forma 10000000001. A cada divisão por 2, ele será sucessivamente par.
    rsa.f = inverso(rsa.e, rsa.phi);
        
    //Para codificar, roda a função calc_modulo com e escolhido;
    if(input == 'c') printf("\n\n a codificação de %u é %u\n", mensagem, calc_modulo(mensagem, rsa.e, rsa.n));
    //Para decodificar, roda com o inverso de e em Zphi, calculado com a função inverso();
    else if(input == 'd') printf("\n\n a decodificação de %u é %u\n", mensagem, calc_modulo(mensagem, rsa.f, rsa.n));
    return 0;
}

/**
 * @brief Calcula a^r(mod m) 
 */
llint calc_modulo(llint a, llint r, llint m){
    llint result = 1;
    //Checa se a é divisível por m
    a = a % m;

    //Se a for divisível, o resto é zero e não há
    //necessidade de fazer contas
    if(a == 0) return 0;
    
    //Calcula o módulo através da divisão sucessiva de r por 2
    //Assim, a eficiência do algoritmo é maior por não precisar
    //Loopar vários for
    while(r > 0){
        //Caso r for ímpar, execute
        if(r % 2 != 0)
            result = (result * a) % m;
        
        //Com o print, é possível ver o quão eficiente a função é.
        //Geralmente não foram gastos mais que 10 iterações do while
        //para resolver o problema.
        printf("a=%u r=%u m=%u res=%u\n", a, r, m, result);
        a = (a * a) % m;
        r = r / 2;
    }
    return result;
}

/**
 * @brief O algoritmo estendido de euclides (AEE) realiza\n
 * operações MDC/GCD sucessivas até encontrar gcd = 1,
 * isto é, quando b%a=0.            
 * @param a termo 1
 * @param b termo 2
 * @param x variável para armazenar coeficientes
 * @param y variável para armazenar coeficientes
 * @return o resultado do algoritmo estendido de euclides entre a e b
 */
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
        // printf("x = 0\n");
        *y = 1;
        return b;
    }
    
    llint newX, newY;
    //chamadas recursivas do algoritmo com novos valores
    int gcd = euclides(b%a, a, &newX, &newY);
    
    //encontra e retorna por referência novos valores de x e y
    *x = newY - (b/a)*newX;
    // printf("x = %lld - (%lld/%lld) * %lld = %lld\n", newY, b, a, newX, *x);
    *y = newX;
    // printf("y = %lld\n", *y);
    // printf("(%lld*%lld)+(%lld*%lld)=1\n\n", a, *x, b, *y);

    return gcd;
}

/**
 * @brief Calcula o inverso de a em Zm baseado no Algoritmo Estendido de Euclides
 * 
 * @param a 
 * @param m 
 */
llint inverso(llint a, llint m){
    llint x, y;
    int mdc = euclides(a, m, &x, &y);
    if(mdc != 1){
        // printf("\n\nO inverso de %lld em %lldZ é inexistente,\n", a, m);
        // printf("dado que os números não são primos entre si.\n");
        // printf("AEE(%lld, %lld) = %d", a, m, mdc);
        return -1;
    }else{
        //É feito um tratamento para casos em que o x é negativo,
        //considerando que o sistema Zm é circular.
        x = (x % m + m)%m;
        //printf("\n\nO inverso de %lld em %lldZ é %lld.", a, m, x);
        return x;
    }
}