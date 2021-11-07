#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "game.h"
#include "readString.h"

int main(){
    int userInput;
    scanf("%d\n", &userInput);

    char* filename = readString();
    FILE* fp = fopen(filename, "r");
    if (fp == NULL){printf("Erro!\n");}
    
    char c;
    char** matrix;
    matrix = malloc(sizeof(char*));
    int i = 0, j = 0;

    int heigth, lenght, fReturn = 0;

    fscanf(fp, "%c", &c);
    matrix = malloc(sizeof(char*) * (i+1));
    while(fReturn != EOF){
        matrix[i] = realloc(matrix[i], sizeof(char) * (j + 1));
        matrix[i][j] = c;
        j++;
        if(c == '\n'){
            lenght = j - 1;
            j = 0;
            i++;
            matrix = realloc(matrix, sizeof(char*) * (i+1));
        }
        fReturn = fscanf(fp, "%c", &c);
    }
    fclose(fp);
    heigth = i;
    
    if(userInput == 1){
        //1. prints the board
        matrixPrinter(heigth, lenght, matrix, 0);
    }else if(userInput == 2){
        //2. prints the board with tips
        char** paddedMatrix = mallocAndFill(matrix, heigth, lenght, 2); 
        char** tipMatrix = processTips(paddedMatrix, heigth, lenght);

        matrixPrinter(heigth, lenght, tipMatrix, 0);

        matrixFree(heigth, tipMatrix);
        matrixFree(heigth+2, paddedMatrix);
    }else if(userInput == 3){
        //3. waits for user input
        int m, n; //coordinates 
        scanf("%d %d\n", &m, &n);
        char** paddedMatrix = mallocAndFill(matrix, heigth, lenght, 2); 
        char** tipMatrix = processTips(paddedMatrix, heigth, lenght); 

        if(tipMatrix[m][n] == '.'){
            //the player clicked on a blank space
            //this should reveal all blank spaces and tips around the area

            char** revealedMatrix = malloc((heigth+2) * sizeof(char*));
            for(int i = 0; i < heigth+2; i++)
                revealedMatrix[i] = malloc((lenght+2) * sizeof(char));
            for(int i = 0; i < heigth+2; i++){
                for(int j = 0; j < lenght+2; j++){
                    revealedMatrix[i][j] = 'X';
                }
            }

            revealedMatrix = recursiveReveal(tipMatrix, revealedMatrix, heigth, lenght, m, n);
            
            matrixPrinter(heigth, lenght, revealedMatrix, 1);
            
            matrixFree(heigth, tipMatrix);
            matrixFree(heigth+2, paddedMatrix);
            matrixFree(heigth+2, revealedMatrix);
        }else if(tipMatrix[m][n] == '*'){
            //the player clicked on a bomb, so the game ends and the table is printed
            matrixPrinter(heigth, lenght, tipMatrix, 0);
        }else{
            //if the player clicked on a tip, simply print the tip
            for(int i = 0; i < heigth; i++){
                for(int j = 0; j < lenght; j++){
                    if(i == m && j == n){
                        printf("%d", tipMatrix[i][j]);
                    }else{
                        printf("X");
                    }
                }
            printf("\n");
            }
        }
    }
    matrixFree(heigth, matrix);   
    
    free(filename);
    return 0;
}