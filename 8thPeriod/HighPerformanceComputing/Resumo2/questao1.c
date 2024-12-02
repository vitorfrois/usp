#include <stdio.h>

long long num_passos = 1e7;
double passo;

int main(){
    int i;
    double x, pi, soma=0.0;

    passo = 1.0/(double) num_passos;
    
    #pragma omp parallel for simd reduction(+:soma)
    for(int i = 0; i < num_passos; i++){
        x = (i + 0.5)*passo;
        soma = soma + 4.0/(1.0 + x*x);
    }

    pi = soma * passo;

    printf("O valor de Pi é %f\n", pi);
    return 0;
}