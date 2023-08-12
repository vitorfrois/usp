#include <stdio.h>
#include <time.h>
#include <string.h>

int main(){
	//time.h methods
	struct tm *data_hora_atual;
	time_t segundos;
	time(&segundos);
	data_hora_atual = localtime(&segundos);

	int j = 2;
	int mDay = data_hora_atual->tm_mday;
	int wDay = data_hora_atual->tm_wday;

	//defining values
	//int mDay = data_hora_atual->tm_mday;
	//int wDay = data_hora_atual->tm_wday;
	int nMonth = data_hora_atual->tm_mon+1;
	int year = data_hora_atual->tm_year+1900;
	char cMonth[10];



	switch (nMonth){
		case 1:
			strcpy(cMonth, "Janeiro");
			break;
		case 2:
			strcpy(cMonth, "Fevereiro");
			break;
		case 3:
		 	strcpy(cMonth, "Março");
			break;
		case 4:
			strcpy(cMonth, "Abril");
			break;
		case 5:
			strcpy(cMonth, "Maio");
			break;
		case 6:
			strcpy(cMonth, "Junho");
			break;
		case 7:
			strcpy(cMonth, "Julho");
			break;
		case 8:
			strcpy(cMonth, "Agosto");
			break;
		case 9:
			strcpy(cMonth, "Setembro");
			break;
		case 10:
			strcpy(cMonth, "Outubro");
			break;
		case 11:
			strcpy(cMonth, "Novembro");
			break;
		case 12:
			strcpy(cMonth, "Dezembro");
			break;
	}

	printf("      %9s %d         \n", cMonth, year);
	printf(" Do  Se  Te  Qu  Qu  Se  Sa \n");
	for(int e = 1; e < j; e++){
		printf("      ");
	}
	printf("  ");
	for(int i = 1; i < 31; i++){
		if(i == mDay){
			printf("\033[0;30m"); //torna a letra preta
			printf(" \033[47m"); //torna o fundo branco
			printf("%2d", i); // imprime o dia
			printf("\033[0m "); //reseta formatação das letras
		}else{
			printf(" %2d ", i);
		}
		if(j < 6){
			j++;
		}else{
			printf("\n");
			j = 0;
		}
	}
	printf("\n");
	return 0;
}
