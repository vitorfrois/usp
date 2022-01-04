//A ESTEIRA DE PLINIO
//VITOR AMORIM FROIS

#include <stdio.h>
#include <string.h>

#define empate 0
#define xGanhou 1
#define oGanhou 2
#define emAndamento 3

#define lines 3
#define collumns 3

int main(){

      int state = empate;
      char winner = 'e';
	char gameMatrix[3][4] = {'\0'};
	for(int i = 0; i < lines; i++){
		for(int j = 0; j < collumns; j++){
			scanf(" %c", &gameMatrix[i][j]);
                  if(gameMatrix[i][j] == '-'){
                        state = emAndamento;
                        //check if the game is still going
                  }
		}
	}

      //ganhou na horizontal?
      for(int i = 0; i < lines; i++){
            if((gameMatrix[i][0] == gameMatrix[i][1])
            && (gameMatrix[i][1] == gameMatrix[i][2])){
                  if(gameMatrix[i][0] != '-'){
                        winner = gameMatrix[i][0];
                  }
            }
      }

      //ganhou na vertical?
      for(int j = 0; j < 3; j++){
            if((gameMatrix[0][j] == gameMatrix[1][j])
            && (gameMatrix[1][j] == gameMatrix[2][j])){
                  if(gameMatrix[0][j] != '-'){
                        winner = gameMatrix[0][j];
                  }
            }
      }

      //check diagonal 1
      if((gameMatrix[0][0] == gameMatrix[1][1])
      && (gameMatrix[1][1] == gameMatrix[2][2])){
            if(gameMatrix[0][0] != '-'){
                  winner = gameMatrix[0][0];
            }
      }

      //check diagonal 2
      if((gameMatrix[0][2] == gameMatrix[1][1])
      && (gameMatrix[1][1] == gameMatrix[2][0])){
            if(gameMatrix[0][2] != '-'){
                  winner = gameMatrix[0][2];
            }
      }

      switch(winner){
            case 'x':
                  state = xGanhou;
                  break;
            case 'o':
                  state = oGanhou;
                  break;
      }

      switch(state){
            case emAndamento:
                  printf("em jogo");
                  break;
            case xGanhou:
                  printf("x ganhou");
                  break;
            case oGanhou:
                  printf("o ganhou");
                  break;
            case empate:
                  printf("empate");
                  break;

      }
      return 0;

}
