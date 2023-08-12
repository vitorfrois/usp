#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(int *a, int *b){
    int temp = *a; 
    *a = *b;
    *b = temp;
}

int* randomArr(int arraySize, int max){
    srand(time(NULL));
    int* array = malloc(sizeof(int) * arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = random() % max;
    }
    return array;
}

int* increasingArr(int arraySize, int max){
    int* array = malloc(sizeof(int) * arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = i;
    }
    return array;
}

int* decreasingArr(int arraySize, int max){
    int* array = malloc(sizeof(int) * arraySize);
    for(int i = 0; i < arraySize; i++){
        array[i] = arraySize-i;
    }
    return array;
}
//a - aritmetica
//b - atribuição
//c - comparação
void heapify(int *array, int size, int i){
    int largest = i;  //b
    int l = 2 * i + 1; //2a + b
    int r = 2 * i + 2; //2a + b
 
    if (l < size && array[l] > array[largest]) //2c
        largest = l; //b
 
    if (r < size && array[r] > array[largest]) //2c 
        largest = r; //b
 
    if (largest != i) { //c
        swap(&array[i], &array[largest]); //3b
        heapify(array, size, largest); //H(n/2)
    }
}

void heapSort(int *array, int size){
    for (int i = size / 2 - 1; i >= 0; i--) //N/2
        heapify(array, size, i);
 
    for (int i = size - 1; i > 0; i--) { //N
        swap(&array[0], &array[i]); //3b
        heapify(array, i, 0); //heapify
    }
    //Total = N/2 + N(heapfiy + 3b)
}

void insertionSort(int* arr, int began, int end){
    int i, key, j;
    int n = end - began;

    for (i = began-1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int averagePivo(int *array, int began, int end){
    int averageArray[3]; 
    averageArray[0] = array[began]; //b
    averageArray[1] = array[(began + end) / 2]; //2a + b
    averageArray[2] = array[end-1]; //a + b
    insertionSort(averageArray, 0, 3); //3^2= 9, constante
    //Total: 3a + 3b + 9
    return averageArray[1];
}

void quicksort(int* array, int began, int end){
	int i, j, pivo, aux, n;
    n = end - began; //a + b

    pivo = averagePivo(array, began, end); //3a + 3b + 9

	i = began;
	j = end-1; //a + 2b

	while(i <= j){ //N
		while(array[i] < pivo && i < end) //a + b + 2c
			i++;
		
		while(array[j] > pivo && j > began) //a + b + 2c
			j--;
		
		if(i <= j){ //c
			aux = array[i]; //b
			array[i] = array[j]; //b
			array[j] = aux; //b
			i++; //2a + 2b
			j--;
		}
	}
    //N(4a + 7b + 5c)

    if(j > began) //c
        quicksort(array, began, j+1); //Q
    
    if(i < end) //c
		quicksort(array, i, end); //Q 

    //Total = 5a + 6b + 2c + 9 + N(4a + 7b + 5c) + Q
        
}
void teste(int *array){
    int pivo;
    //pivo = averagePivo(array, began, end); //3a + 3b + 9
    pivo = array[0];
}

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

void printArray(int *array, int began, int end){
    int size = end - began;
    for(int i = began; i < size; i++)
        printf("%d,", array[i]);
}

/**
 * @brief measure function time in ms
 * 
 * @param size 
 * @param max 
 * @param iterations 
 * @param mode 
 * @return int time taken in ms
 */
int timeMeasure(int size, int max, int iterations, char* mode){
    double time_taken;
    clock_t t, totalTime = 0;
    int *array = randomArr(size, max);
    //printArray(array, 0, size);
    //quicksort(array, 0, size);
    if(strcmp(mode, "quick") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            quicksort(array, 0, size);
            t = clock() - t;
            totalTime += t;
        }
    }else if(strcmp(mode, "heap") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            heapSort(array, size);
            t = clock() - t;
            totalTime += t;
        }
    }else if(strcmp(mode, "merge") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            mergeSort(array, 0, size);
            t = clock() - t;
            totalTime += t;
        }
    }else if(strcmp(mode, "insertion") == 0){
        for(int i = 0; i < iterations; i++){
            t = clock();
            insertionSort(array, 0, size);
            t = clock() - t;
            totalTime += t;
        }
    }else{
        printf("%s is a non-identified sorting method\n", mode);
        return 0;
    }
    //printArray(array, 0, size);
    free(array);
    totalTime = totalTime / iterations;
    time_taken = ((double)totalTime)/CLOCKS_PER_SEC;
    printf("\ntime taken = %d", (int) (time_taken*1000000));
    //printf("%sSort took %f seconds to execute the sort on %d elements\n", mode, time_taken, size); 
    return (int) (time_taken*1000000);
}