#include <stdio.h>

int main(){
	int nMetro;
	scanf("%d", &nMetro);
	if(nMetro <= 5){
		switch (nMetro){
			case 0:
				printf("* Morumbi \n|\n");
			case 1:
				printf("* Butanta \n|\n");
			case 2:
				printf("* Pinheiros \n|\n");
			case 3:
				printf("* Faria Lima \n|\n");
			case 4: 
				printf("* Fradique Coutinho \n|\n");
			case 5: 
				printf("* Oscar Freire");
				break;
		}
	}else{
		switch(nMetro){
			case 6:
				printf("* Paulista \n|\n");
			case 7:
				printf("* Higienopolis-Mackenzie \n|\n");
			case 8:
				printf("* Republica \n|\n");
			case 9:
				printf("* Luz");
				break;
		}
	}
	return 0;
}
