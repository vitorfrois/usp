#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
 * @brief Realiza ordenação propriamente dita do vetor
 * 
 * @param arr O vetor a ser ordenado
 * @param l Primeiro elemento
 * @param m Elemento central
 * @param r Último elemento
 */
void merge(int* arr, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */ 
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
/**
 * @brief Função mergeSort
 * 
 * @param arr O vetor de valores a ser ordenado
 * @param l início do vetor
 * @param r final do vetor
 */
void mergeSort(int* arr, int l, int r){
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
    }
}


/* Function to sort an array using insertion sort*/
/**
 * @brief Função de ordenação com Insertion Sort
 * 
 * @param arr Vetor a ser ordenado
 * @param n Tamanho do vetor
 */
void insertionSort(int* arr, int n){
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
 
// A function to implement bubble sort
/**
 * @brief Função de ordenação com Bubble Sort
 * 
 * @param arr Vetor a ser ordenado
 * @param n Tamanho do vetor
 */
void bubbleSort(int arr[], int n)
{
   int i, j, swapCheck;

   for (i = 0; i < n-1; i++){
     swapCheck = 0;
     for (j = 0; j < n-i-1; j++){
        if (arr[j] > arr[j+1]){
           swap(&arr[j], &arr[j+1]);
           swapCheck = 1;
        }
     }
     if (swapCheck == 0)
        break;
   }
}

/**
 * @brief Gerador de vetor aleatório
 * 
 * @param arraySize Tamanho do vetor
 * @param max Valor máximo
 * @return int* Vetor aleatório
 */
int* randomArr(int arraySize, int max){
    srand(time(NULL));
    int* array = malloc(sizeof(int) * arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = random() % max;
    }
    return array;
}

/**
 * @brief Gerador de vetor crescente
 * 
 * @param arraySize Tamanho do vetor
 * @param max Valor máximo
 * @return int* Vetor aleatório
 */
int* increasingArr(int arraySize, int max){
    int* array = malloc(sizeof(int) * arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = i;
    }
    return array;
}

/**
 * @brief Gerador de vetor decrescente
 * 
 * @param arraySize Tamanho do vetor
 * @param max Valor máximo
 * @return int* Vetor aleatório
 */
int* decreasingArr(int arraySize, int max){
    int* array = malloc(sizeof(int) * arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = arraySize-i;
    }
    return array;
}

/**
 * @brief Uma função para medir o tempo médio 
 * de cada método na ordenação de vetores aleatórios.
 * 
 * @param size Tamanho do vetor a ser analisado 
 * @param max Maior tamanho de elemento do vetor
 * @param iterations Número de iterações (números maiores evitam desvios)
 * @param mode Escolha um método disponível: merge, insertion ou bubble.
 */
void timeMeasure(int size, int max, int iterations, char* mode){
    double time_taken;
    clock_t t, totalTime = 0;

    if(strcmp(mode, "bubble") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            bubbleSort(decreasingArr(size, max), size);
            t = clock() - t;
            totalTime += t;
        }
    }else if(strcmp(mode, "insertion") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            insertionSort(decreasingArr(size, max), size);
            t = clock() - t;
            totalTime += t;
        }
    }else if(strcmp(mode, "merge") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            mergeSort(decreasingArr(size, max), 0, size);
            t = clock() - t;
            totalTime += t;
        }
    }else{
        printf("%s is a non-identified sorting method\n", mode);
        return;
    }

    totalTime = totalTime / iterations;
    time_taken = ((double)totalTime)/CLOCKS_PER_SEC;
    printf("%d,", (int) (time_taken*1000000));
    //printf("%sSort took %f seconds to execute the sort on %d elements\n", mode, time_taken, size); 
}



int main(int argc, char* argv[]){
    char* ptr;
    //Caso a função seja chamada de forma errada, o usuário é avisado
    if(argc != 5){
        printf("Program usage:\n");
        printf("./main size max iterations mode\n");
        printf("max - tamanho máximo do vetor\n");
        printf("step - tamanho de cada vetor por iteração.\n");
        printf("iterations - Número de iterações (números maiores evitam desvios)\n");
        printf("mode - Escolha um método disponível: merge, insertion ou bubble.\n");
        return 0;
    }

    int max = strtol(argv[1], &ptr, 10);
    int step = strtol(argv[2], &ptr, 10);
    int iterations = strtol(argv[3], &ptr, 10);

    printf("%sSort took x microsseconds to execute the sort on (i <= %d; i += %d) elements\n", argv[4], max, step);
    for(int i = step; i <= max; i += step)
        timeMeasure(i, max, iterations, argv[4]);
    
    return 0;
}


