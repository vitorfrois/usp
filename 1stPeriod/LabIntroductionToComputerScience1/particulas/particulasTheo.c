#include <stdio.h>
#include <stdlib.h>

char matriz[32][64];
char matriz_copia[32][64];

void atualizar_fisica();

int main(){


    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 64; j++){
            matriz[i][j] = ' ';
        }
    }
    
    int frame_final, frame, x, y;
    char nova_particula;
    int n_lido;

    scanf("%d", &frame_final);

    int contador = 0;
    
    while (contador < frame_final) {

        // `scanf` retorna EOF quando chega ao fim da entrada.
        n_lido = scanf(" %d: %d %d %c", &frame, &x, &y, &nova_particula);

        // Se não há mais partículas a serem criadas, continue até o final
        // da simulação.
        if (n_lido == EOF) {
            frame = frame_final;
        }

        // Calcula todos os frames até o próximo frame onde queremos criar
        // uma partícula.

        while (contador < frame) {
            
            printf("frame: %d\n", contador + 1);
            
            for (int i = 0; i < 32; i++){
                for (int j = 0; j < 64; j++){
                    printf("%c", matriz[i][j]);
                }
                printf("\n");
            }
            atualizar_fisica(matriz);
            contador++;
        }

        // Se há uma particula a ser criada, crie ela.
        if (n_lido != EOF) {
            matriz[y][x] = nova_particula;
        }
    }
    return 0;
}

void atualizar_fisica(){

    char elemento;

    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 64; j++){
            matriz_copia[i][j] = matriz[i][j];
        }    
    }
    
    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 64; j++){

            //atualizar fisica da areia
            
            if(matriz[i][j] == '#'){

                if((matriz[i + 1][j] == ' ' || matriz[i + 1][j] == '~') && i != 31){ //posicao abaixo e ar ou agua

                    
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i + 1][j];
                    matriz_copia[i + 1][j] = elemento;  
                }
                else if((matriz[i + 1][j - 1] == ' ' || matriz[i + 1][j - 1] == '~') && i != 31 && j != 0){ //posicao abaixo e a esquerda e ar ou agua
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i + 1][j - 1];
                    matriz_copia[i + 1][j - 1] = elemento;  
                }
                else if((matriz[i + 1][j + 1] == ' ' || matriz[i + 1][j + 1] == '~') && i != 31 && j != 63){ //posicao abaixo e a direita e ar ou agua
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i + 1][j + 1];
                    matriz_copia[i + 1][j + 1] = elemento;
                }
            }

            //atualizar fisica da agua

            if(matriz[i][j] == '~'){

                if(matriz[i + 1][j] == ' ' && i != 31){ //posicao abaixo e ar

                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i + 1][j];
                    matriz_copia[i + 1][j] = elemento;  
                }
                else if(matriz[i + 1][j - 1] == ' ' && i != 31 && j != 0){ //posicao abaixo e a esquerda e ar
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i + 1][j - 1];
                    matriz_copia[i + 1][j - 1] = elemento;  
                }
                else if(matriz[i + 1][j + 1] == ' '&& i != 31 && j != 63){ //posicao abaixo e a direita e ar
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i + 1][j + 1];
                    matriz_copia[i + 1][j + 1] = elemento;
                }
                else if(matriz[i][j - 1] == ' ' && j != 0){
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i][j - 1];
                    matriz_copia[i][j - 1] = elemento;
                }
                else if(matriz[i][j + 1] == ' ' && j != 63){
                    elemento = matriz_copia[i][j];
                    matriz_copia[i][j] = matriz_copia[i][j + 1];
                    matriz_copia[i][j + 1] = elemento;
                }
            }
        }    
    } 

    for (int i = 0; i < 32; i++){
        for (int j = 0; j < 64; j++){
            matriz[i][j] = matriz_copia[i][j];
        }    
    }  
}