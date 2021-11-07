#include <stdio.h>
#include <time.h>


int main(){
	//x²-y²=p
	//declaração de variáveis
	float tempo; //quero medir quanto tempo demora;
	time_t t_ini, t_fim;
	int p;
	int tP = 0;
	int contador = 0;
	int array[20];
	//leitura do número
	scanf("%d", &p);
	t_ini = time(NULL);
	//garante que o número inserido é maior que 1
	if(p < 2){
		//printf("Insira um número maior que 1");
		return 0;
	}	
	//checagem: é primo ou nem?
	//testa a equação para x e y até 4000	
	for(int m = 1; m<1000000; m++){
		for(int n = 1; n<1000000; n++){
			if(m*m - n*n == p){ 
				array[contador] = m;
				contador++;
				array[contador] = n;	
			}
		}
	}
	//printa os resultados
	t_fim = time(NULL);
	tempo = difftime(t_fim, t_ini);
	printf("%d\n", contador);
	for(int u = 0; u<=contador; u = u + 2){
	printf("%d %d\n", array[u], array[u+1]);
	}
	printf("Tempo gasto para execução do programa: %fs", tempo);
	return 0;
}
