//A ESTEIRA DE PLINIO
//VITOR AMORIM FROIS

#include <stdio.h>
#include <string.h>

#define lines 32
#define collumns 64

int main(){
	char cMatrix[lines][collumns] = {'\0'};
	int xAdress, yAdress;
	int i, j;
	for(i = 0; i < lines; i++){
		for(j = 0; j < collumns; j++){
			scanf("%c", &cMatrix[i][j]);
			if(cMatrix[i][j] == '['){
				yAdress = i;
				xAdress = j;
			}
		}
	}

	int lastChar;
	int state = 0; //0 1 2
	while(state == 0){
		//printf("cMatrix[%d][%d]\n", xAdress, yAdress);
		switch(cMatrix[yAdress][xAdress]){
			case '[':
				//initial char
				xAdress += 2;
				//printf("uiuiu\n");
				break;
			case ']':
				//final char
				state = 1;
				printf("Ok.\n");
				break;
			case '>':
				lastChar = cMatrix[yAdress][xAdress];
				cMatrix[yAdress][xAdress] = '.';
				xAdress += 2;
				//printf(">\n");
				break;
			case '<':
				lastChar = cMatrix[yAdress][xAdress];
				cMatrix[yAdress][xAdress] = '.';
				xAdress -= 2;
				//printf("<\n");
				break;
			case '^':
				lastChar = cMatrix[yAdress][xAdress];
				cMatrix[yAdress][xAdress] = '.';
				yAdress -= 1;
				xAdress -= 1;
				//printf("^\n");
				break;
			case 'v':
				lastChar = cMatrix[yAdress][xAdress];
				cMatrix[yAdress][xAdress] = '.';
				yAdress += 1;
				xAdress += 1;
				//printf("v\n");
				break;
			case '#':
				//printf("#\n");
				switch(lastChar){
					case '>':
						xAdress += 2;
						break;
					case '<':
						xAdress -= 2;
						break;
					case '^':
						yAdress -= 1;
						xAdress -= 1;
						break;
					case 'v':
						yAdress += 1;
						xAdress += 1;
						break;
					default:
						//printf("uai so\n");
						//printf("o ultimo char foi %c\n", lastChar);
						state = 1;
						break;
				}
				break;
			case ' ':
				printf("Falha na esteira.\n");
				state = 1;
				break;
			case '.':
				state = 1;
				printf("Loop infinito.\n");
				break;
		}

	}

	for(int m = 0; m < lines; m++){
		for(int n = 0; n < collumns; n++){
			printf("%c", cMatrix[m][n]);
		}
	}
	printf("\n");
	return 0;
}
