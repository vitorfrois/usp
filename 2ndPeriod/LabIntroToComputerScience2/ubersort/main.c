#include <stdio.h>
#include <stdlib.h>
#include "ubersort.h"

int main(int argc, char *argv[]){	
	int size;
	char option;
	scanf("%d\n", &size);
	scanf("%c\n", &option);
	//printf("option = %c\n", option);
	srand(42);
	int *array = (int*) malloc(sizeof(int) * size);
	for(int i = 0; i < size; i++)
		scanf("%d", &array[i]);

	quicksort(array, 0, size, option);

	printArray(array, 0, size);	
    
    free(array);
	return 0;
}
