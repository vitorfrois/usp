#include <stdio.h>
#include <math.h> //usar lm pra compilar

int main(){
	double kSinal = 1; //pow aceita somente double
	double kDenominador = 3;
	double valorDesejado, diff;
	double glSeries = 4; //a serie começa em 4
	int termoSerie = 1;
	scanf("%lf", &diff);
	while(fabs(glSeries - M_PI) > diff){
		printf("gLSeries(%d) = %.15lf\n", termoSerie, glSeries);
		double resultado = ((pow(-1,kSinal)*4)/kDenominador);
		//printf("resultado = %lf\n", resultado);
		glSeries = glSeries + resultado;
		kSinal++;
		kDenominador = kDenominador + 2;
		termoSerie++;
	}
	printf("\n|%.15lf - %.15lf| < %.15lf\n", glSeries, M_PI, diff);
	printf("Foram necessarias %d iteracoes \n", termoSerie);
	return 0;
	//o numero de iteracoes necessarias sempre é 1/diff
}
