#include <stdio.h>
#include <stdlib.h>
#define N_COLORS 256

void printMatrix(int** matrix, int x, int y, int size){
    for(int i = x; i < x+size; i++){
        for(int j = y; j < y+size; j++){
            printf("%d ", matrix[i][j]);
        }       
        printf("\n");
    }
    printf("\n");

}

void quadtree(int** matrix, int x, int y, int size){

    //printf("size = %d\n", size);
    //printMatrix(matrix, x, y, size);

    //if matrix is unitary, print its value
    if(size == 1){
        printf("%d ", matrix[x][y]);
        return;
    }

    //else, check if it's monocolor or not
    int* colors = calloc(sizeof(int), N_COLORS);
    int n, i, j;

    //int first = matrix[x][y];
    for(i = x; i < x+size; i++){
        for(j = y; j < y+size; j++){
            colors[matrix[i][j]]++;
        }
    }

    //if true, print the dominant color and return
    for(n = 0; n < N_COLORS; n++){
        //printf("colors[%d] = %d\n", n, colors[n]);
        if(colors[n] == (size*size)){
            //printf("monocolor\n");
            printf("%d ", matrix[x][y]);
            free(colors);
            return;
        }
    }

    //else, print -1 and recursively calls the function for 4 equal submatrixes 
    printf("-1 ");
    size = size/2;
    quadtree(matrix, x, y, size);
    quadtree(matrix, x, y + size, size);
    quadtree(matrix, x + size, y, size);
    quadtree(matrix, x+size, y+size, size);

    free(colors);
    return;

}



int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    int** matrix = (int**) malloc(sizeof(int*) * x);
    for(int i = 0; i < x; i++)
        matrix[i] = (int*) malloc(sizeof(int) * y);

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            scanf("%d", &matrix[i][j]);
        }       
        scanf("%*c");
    }
    int size = x;
    //printMatrix(matrix, 0, 0, size);
    quadtree(matrix, 0, 0, size);
    
    for(int i = 0; i < x; i++)
        free(matrix[i]);
    free(matrix);
    return 0;
}