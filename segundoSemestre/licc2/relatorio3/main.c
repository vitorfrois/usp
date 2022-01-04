#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorts.h"
#define NUM_STRINGS 4
#define MAX_LENGHT 20

int main(int argc, char* argv[]){
    char* ptr;
    //Caso a função seja chamada de forma errada, o usuário é avisado
    // if(argc != 4){
    //     printf("Program usage:\n");
    //     printf("./main max step iterations mode\n");
    //     printf("max - tamanho máximo do vetor\n");
    //     printf("step - tamanho de cada vetor por iteração.\n");
    //     printf("iterations - Número de iterações (números maiores evitam desvios)\n");
    //     return 0;
    // }

    // int max = strtol(argv[1], &ptr, 10);
    // int step = strtol(argv[2], &ptr, 10);
    int iterations = 10;
    //header
    FILE* fp = fopen("manim/data.csv", "w");
    // fprintf(fp, "%d,", 0);
    int max = 10;
    int vectorSize[10]={1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    for(int i = 0; i < max; i ++){
        if(i != max-1) fprintf(fp, "%d,", vectorSize[i]);
        else fprintf(fp, "%d", vectorSize[i]);
    }

    //time array
    char methods[NUM_STRINGS][MAX_LENGHT] = {{"quick"}, {"heap"}, {"insertion"}, {"merge"}};
    fprintf(fp, "\n");
    for(int i = 0; i < NUM_STRINGS; i++){
        printf("%s:", methods[i]);
        // fprintf(fp, "%s,", methods[i]);
        for(int j = 0; j < max; j++){
            if(j != max-1) fprintf(fp, "%d,", timeMeasure(vectorSize[j], iterations, methods[i]));
            else fprintf(fp, "%d", timeMeasure(vectorSize[j], iterations, methods[i]));
        }
        fprintf(fp, "\n");
    }
    
    
    // for(int i = 0; i < dataSize; i++){
    //     if(i+1 != dataSize) fprintf(fp, "%d,", timeArray[i]);
    //     else fprintf(fp, "%d", timeArray[i]);
    // }
    fclose(fp);
    
    return 0;
}


