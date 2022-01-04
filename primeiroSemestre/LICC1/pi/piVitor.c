#include <stdio.h>
#include <math.h>

int main()
{
    double denominador = 3;
    int num = 1; // numero de iterações
    double diferenca, valor; //valor = resultado da fórmula de gregory
    valor = 4;

    printf("Insira a diferença máxima de X:");
    scanf("%lf", &diferenca);

    while(fabs((M_PI - valor)) > diferenca){
        if (num % 2 == 0){
            valor = valor + (4/denominador);
        }
        else{
            valor = valor - (4/denominador);
        }
        denominador +=2;
        num++;
        printf("gLSeries(%d) = %.15lf\n", num, valor);
    }
    printf("\nNúmero de iterações:%i", num);
    return 0;
}
