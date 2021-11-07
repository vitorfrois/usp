/**
 * @file main.c
 * @author Vítor Amorim Fróis (12543440)
 * @brief O programa calcula o inverso modular de um número em certa base. Rode para ajuda.
 * @version 1.2
 * @date 2021-10-25
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//As variáveis usadas estão em Long Long Int para permitir
//a entrada de valores maiores
typedef long long int llint;

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

/**
 * @brief Calcula o inverso de a em Zm baseado no Algoritmo Estendido de Euclides
 * 
 * @param a 
 * @param m 
 */
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


int main(int argc, char* argv[]) {
    char* ptr;
    //Caso a função seja chamada de forma errada, o usuário é avisado
    if(argc != 3){
        printf("Utilização do programa:\n");
        printf("./main d a\n");
        printf("O programa busca o inverso de a em Zd,\n");
        printf("tal que ax¹ = 1 (mod n)");
        return 0;
    }
    
    inverso(strtol(argv[2], &ptr, 10), strtol(argv[1], &ptr, 10));
    
	return 0;
}
