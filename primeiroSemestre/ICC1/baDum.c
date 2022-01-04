#include <stdio.h>

int main(){
	//leitura de variáveis
	int n;
	scanf("%d", &n);
	
	//adiciona a variavel somaPrimos
	int somaPrimos = 0;
	if(n % 11 == 0)
		somaPrimos += 11;
	if(n % 13 == 0)
		somaPrimos += 13;
	if(n % 19 == 0)
		somaPrimos += 19;

	//switch com possiveis casos
	switch(somaPrimos){
		case 11:
			printf("BaBa\n");
			break;
		case 13:
			printf("BaDum\n");
			break;
		case 19:
			printf("BaTss\n");
			break;
		case 24:
			printf("BaDumDum\n");
			break;
		case 30:
			printf("BaDumTss\n");
			break;
		case 32:
			printf("DumDumTss\n");
			break;
		case 43:
			printf("BaDumTssTss\n");
			break;
		default:
			printf("%d\n", n);
			break;
	}
	return 0;
}

