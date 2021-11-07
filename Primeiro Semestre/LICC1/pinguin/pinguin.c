#include <stdio.h>
#include <string.h>

int main(){
	//definicao e leitura de variaveis
	int nRounds, nJogadores, posicaoPingu;
	scanf("%d %d %d", &nRounds, &nJogadores, &posicaoPingu);
	if(nJogadores == posicaoPingu) //caso o n de jogadores seja igual a posicao do pinguin,
		posicaoPingu = 0; 	  //e necessario tratar o dado para nao passar direto
	//definicao de variaveis usadas na iteracao
	int n = 1, i = 1;
	int j, k;
	while(i < nRounds + 1){ //o iterador i conta o número de cada rodada
		for(j = 0; j < 3; j++){ //o iterador j decide se a frase da rodada é:
						//"pinguins" (0)
						//"no gelo" (1)
						//"uhuu!"" (2)
			for(k = 0; k < n; k++){ //o iterador k decide quantas vezes cada frase deve aparecer
				if(posicaoPingu == i%nJogadores){
					switch (j){
						case 0:
							if(n > 1){ //caso haja mais de um pinguin
								     //printa a palavra no plural
								printf("%d pinguins", n);
							}else{
								printf("%d pinguim", n);
							}
							break;
						case 1:
							printf("no gelo");
							break;
						case 2:
							printf("uhuu!");
							break;
					}
					printf("\n");
				}
				i++; // adiciona nova rodada
				if(i > nRounds) //se o numero de rodadas for igual ao input,
					break;    //o codigo é interrompido
			}
			if(i > nRounds) //interrompe o codigo em todos os "for"
				break;
		}
		n++; //trina de frases, o numero de vezes que cada frase aparece aumenta
		     //em uma unidade
	}
	return 0;
}
