#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorts.h"

int main(int argc, char* argv[]){
    char* ptr;
    //Caso a função seja chamada de forma errada, o usuário é avisado
    if(argc != 5){
        printf("Program usage:\n");
        printf("./main size max iterations mode\n");
        printf("max - tamanho máximo do vetor\n");
        printf("step - tamanho de cada vetor por iteração.\n");
        printf("iterations - Número de iterações (números maiores evitam desvios)\n");
        printf("mode - Escolha um método disponível: heap ou quick.\n");
        return 0;
    }

    int max = strtol(argv[1], &ptr, 10);
    int step = strtol(argv[2], &ptr, 10);
    int iterations = strtol(argv[3], &ptr, 10);

    //printf("%sSort took x microsseconds to execute the sort on (i <= %d; i += %d) elements\n", argv[4], max, step);
    int dataSize = max/iterations;
    int timeArray[dataSize];
    for(int i = step; i <= max; i += step)
        timeMeasure(i, max, iterations, argv[4]);
    
    // FILE* fp = fopen("data.csv", "w");
    // for(int i = 0; i < dataSize; i++){
    //     if(i+1 != dataSize) fprintf(fp, "%d,", timeArray[i]);
    //     else fprintf(fp, "%d", timeArray[i]);
    // }
    // fclose(fp);
    
    return 0;
}


