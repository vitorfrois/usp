#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

int neigh(int i, int j, char** matrix){
        int bombs = 0;
        if(matrix[i + 1][j + 1] == '*')
            bombs++;
        if(matrix[i + 1][j] == '*')
            bombs++;
        if(matrix[i + 1][j - 1] == '*')
            bombs++;
        if(matrix[i][j - 1] == '*')
            bombs++;
        if(matrix[i - 1][j - 1] == '*')
            bombs++;
        if(matrix[i - 1][j] == '*')
            bombs++;
        if(matrix[i - 1][j + 1] == '*')
            bombs++;
        if(matrix[i][j + 1] == '*')
            bombs++;
        return bombs;
}

char** processTips(char** matrix, int heigth, int lenght){
    int bombs;
    char** tipMatrix = malloc((heigth) * sizeof(char*));
    for(int i = 0; i < heigth; i++)
        tipMatrix[i] = malloc((lenght) * sizeof(char));

    for(int i = 1; i < heigth+1; i++){
        for(int j = 1; j < lenght+1; j++){
            if(matrix[i][j] == '.'){
                bombs = neigh(i, j, matrix);
                if(bombs != 0){
                    tipMatrix[i-1][j-1] = bombs;
                }else{
                    tipMatrix[i-1][j-1] = '.';
                }
            }else{
                tipMatrix[i-1][j-1] = '*';
            }
        }
    }
    //matrixPrinter(heigth, lenght, tipMatrix, 0);
    return tipMatrix;
}

char** recursiveReveal(char** tipMatrix, char** reveleadMatrix, int heigth, int lenght, int m, int n){
    if(m >= 0 && n >= 0 && m < heigth && n < lenght && reveleadMatrix[m+1][n+1] == 'X'){
        reveleadMatrix[m+1][n+1] = tipMatrix[m][n];
    }
    else return reveleadMatrix;
    //matrixPrinter(heigth+2, lenght+2, reveleadMatrix, 0);  
    //usleep(100000);
    //system("clear");   
    if(tipMatrix[m][n] == '.' && reveleadMatrix[m+1][n+1] != 'X'){
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m+1, n+1);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m+1, n);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m+1, n-1);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m, n-1);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m-1, n-1);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m-1, n);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m-1, n+1);
        reveleadMatrix = recursiveReveal(tipMatrix, reveleadMatrix, heigth, lenght, m, n+1);
    }   
    return reveleadMatrix;   
}