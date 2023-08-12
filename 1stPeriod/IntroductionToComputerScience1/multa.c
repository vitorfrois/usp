#include <stdio.h>

int main(){
	float multa, velocidade;
	float limite = 80.00;
	scanf("%f", &velocidade);
	if (velocidade > 80){
		multa = 2*(velocidade - limite);
		printf("Limite de velocidade excedido! Multado no valor de R$%.2f!\n", multa);
	}
	else{
		printf("Velocidade dentro do limite permitido.\n");
	}
}
