#include <stdio.h>
#include <string.h>

int main(){
	// Definicao e leitura de variaveis
	int nRounds, nJogadores, posPingu;
	scanf("%d %d %d", &nRounds, &nJogadores, &posPingu);

	// Definicao de variaveis usadas na iteracao
	int nFrases = 1;
	for (int i = 0, posSubRound = 0; i < nRounds; i++, posSubRound++){
		if (posSubRound == 3 * nFrases) {
			posSubRound = 0;
			nFrases++;
		}
	
		if (i % nJogadores == posPingu - 1){
			printf("posSubRound = %d; nFrases = %d", posSubRound, nFrases);
			if (posSubRound < nFrases){
				char *substantivo = nFrases == 1 ? "pinguim" : "pinguins";
				printf("%d %s\n", nFrases, substantivo);
			}
			else if (posSubRound < nFrases * 2){
				printf("no gelo\n");
			}
			else {
				printf("uhuu!\n");
			}
		}
	}

	return 0;
}
