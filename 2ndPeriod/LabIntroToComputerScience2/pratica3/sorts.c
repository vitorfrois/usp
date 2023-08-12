#include <stdio.h>
#include <stdlib.h>
#include "sorts.h"

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

int averagePivo(Node **array, int began, int end){
    int averageArray[3];
    averageArray[0] = array[began]->s.frequency;
    averageArray[1] = array[(began + end) / 2]->s.frequency;
    averageArray[2] = array[end-1]->s.frequency;
    insertionSort(averageArray, 0, 3);
    return averageArray[1];
}

void quicksort(Node **array, int began, int end){
	int i, j, pivo;
    Node *aux;

    pivo = averagePivo(array, began, end);

	i = began;
	j = end-1;
	while(i <= j){
		while(array[i]->s.frequency > pivo && i < end)
			i++;
		
		while(array[j]->s.frequency < pivo && j > began)
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
        quicksort(array, began, j+1);
    
    if(i < end)
		quicksort(array, i, end);          
        
}