#include <stdio.h>
#include <stdlib.h>
#include "ubersort.h"

int averagePivo(int *array, int began, int end){
    int *averageArray = (int *) malloc(sizeof(int) * 3);
    averageArray[0] = array[began];
    averageArray[1] = array[(began + end) / 2];
    averageArray[2] = array[end];
    insertionSort(averageArray, 0, 3);
    //printArray(averageArray, 0, 3);
    return averageArray[1];
}

void quicksort(int* array, int began, int end, char option){
	int i, j, pivo, aux, n;
    n = end - began;
    if(n <= 10)
        insertionSort(array, began, end);
       
    if(option == '1')
        pivo = averagePivo(array, began, end);  
    else if(option == '2'){
        pivo = array[rand()%n];
    }
    

	i = began;
	j = end-1;
	pivo = array[(began + end) / 2];
	while(i <= j){
		while(array[i] < pivo && i < end)
			i++;
		
		while(array[j] > pivo && j > began)
			j--;
		
		if(i <= j){
			aux = array[i];
			array[i] = array[j];
			array[j] = aux;
			i++;
			j--;
		}
	}

    if(j > began)
        quicksort(array, began, j+1, option);
    
    if(i < end)
		quicksort(array, i, end, option);          
        
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

void printArray(int *array, int began, int end){
    int size = end - began;
    for(int i = began; i < size; i++)
        printf("%d\n", array[i]);
}

