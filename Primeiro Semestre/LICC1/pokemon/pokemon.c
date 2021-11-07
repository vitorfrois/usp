#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
      int matrixSize;
      scanf("%d\n", &matrixSize);
      float matrix[matrixSize][matrixSize];
      for(int i = 0; i < matrixSize; i++){
            for(int j = 0; j < matrixSize; j++){
                  scanf("%f ", &matrix[i][j]);
            }
            scanf("\n");
      }
      float** attackMatrix = malloc(sizeof(float*) * 2);
      attackMatrix[0] = malloc(sizeof(float));
      attackMatrix[1] = malloc(sizeof(float));
      int nAttack = 0;
      while(attackMatrix[0][nAttack] != -1){
            attackMatrix[0] = realloc(attackMatrix[0], sizeof(float) * (nAttack+1));
            attackMatrix[1] = realloc(attackMatrix[1], sizeof(float) * (nAttack+1));
            scanf("%f", &attackMatrix[0][nAttack]);
            if(attackMatrix[0][nAttack] == -1)
                  break;
            scanf("%f\n", &attackMatrix[1][nAttack]);
            nAttack++;
      }

      int attackType;
      scanf("%d", &attackType);

      //calculate the best attack
      float finalAttackDamage = 0;
      int attackIndex;
      for(int j = 0; j < matrixSize; j++){
            int i = attackMatrix[1][j];
            float damage = matrix[i][attackType] * attackMatrix[0][j];
            if(damage > finalAttackDamage){
                  finalAttackDamage = damage;
                  attackIndex = i;
            }
      }

      printf("O melhor ataque possui indice %d e dano %.2f\n", attackIndex, finalAttackDamage);

      free(attackMatrix[0]);
      free(attackMatrix[1]);
      free(attackMatrix);
      return 0;
}
