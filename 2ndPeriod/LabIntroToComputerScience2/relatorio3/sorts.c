#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sorts.h"

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

void heapify(int *array, int size, int i){
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
 
    if (l < size && array[l] > array[largest])
        largest = l;
 
    if (r < size && array[r] > array[largest])
        largest = r;
 
    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapify(array, size, largest);
    }
}

void heapSort(int *array, int size){
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);
 
    for (int i = size - 1; i > 0; i--) {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
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
    averageArray[0] = array[began];
    averageArray[1] = array[(began + end) / 2];
    averageArray[2] = array[end-1];
    insertionSort(averageArray, 0, 2);
    //printArray(averageArray, 0, 3);
    return averageArray[1];
}

void quicksort(int* array, int began, int end){
	int i, j, pivo, aux, n;
    n = end - began;

    //escolha média de 3 do pivô   
    //escolha do último elemento como pivô para pior caso
    // pivo = array[0];
    pivo = averagePivo(array, began, end);

	i = began;
	j = end-1;
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
        quicksort(array, began, j+1);
    
    if(i < end)
		quicksort(array, i, end);          
        
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
  
    int L[n1], R[n2];
  
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    i = 0, j = 0, k = l; 
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
  
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
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
        int m = l + (r - l) / 2;
  
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void radixCounting(int* vetor, int n, int exp, int base) {
    //Nao e preciso calcular min e max, pois min sera 0 e max o exp
	// 1 - cria vetor de contagem
	int contagem[base];
    for(int i = 0; i < base; i++) contagem[i] = 0; //
    int final[n];
	// Kb 
	
	// 2 - conta a frequencia de cada chave
	int i;
	for (i = 0; i < n; i++) 
		contagem[(vetor[i]/exp)%base]++;    // 4a
	// 4aN

    for(i = 1; i < base; i++)
        contagem[i] += contagem[i-1]; //K(a+b)

	// 3 - recria o vetor usando as frequencias para cada chave no vetor de contagem
    for(i = n-1; i >= 0; i--)
        final[--contagem[(vetor[i]/exp)%base]] = vetor[i]; //b + a+a+a
    //n(3a+b)
    
	for(i = 0; i < n; i++)
        vetor[i] = final[i];  //Na

    //Total = Kb + 4Na + Ka + Kb + N3a + Nb
    //      = N(7a+b) + K(a+2b)
    //      = N + K
}

void radixSort(int vetor[], int n)
{
    int max = vetor[0];
	for (int i=1; i < n; i++)
		if (vetor[i] > max) max = vetor[i]; // c+b
    //n(c+b)
    int base = n;

    for (int exp = 1; max / exp > 0; exp *= base) //log_n(c)
        radixCounting(vetor, n, exp, base); //counting
    //log_n(c) * (N+K)
}

typedef struct node {
	int elem;
	struct node *next, *prev;
} Node;

typedef struct bucket {
	Node *begin;
	Node *end;
} Bucket; 

void bucketSort(int *v, int n) {
	// 1- encontra min e max
    // n++;
	int max, min, i;
	max = min = v[0];
	for (int i=1; i < n; i++) {
		if (v[i] > max) max = v[i]; // c+b
		if (v[i] < min) min = v[i]; // c+b
	}
	// (2c+2b)n

	// 2- criar um vetor auxiliar contendo listas (buckets)
	//    cada bucket possui um ponteiro para o inicio e outro
	//    para o fim da lista
	int k = max-min+1; 
	Bucket **B = (Bucket **) calloc(k+1, sizeof(Bucket*));	
    for(int i = 0; i < k+1; i++){
        B[i] = malloc(sizeof(Bucket));
        B[i]->begin = NULL;
        B[i]->end = NULL;  
    }
	// Kb 

	// 3 - preenche os buckets com as chaves do vetor
	//     de entrada
	for (i = 0; i < n; i++) { //(c+a)
		int key = v[i]; //b
		Node *newnode = malloc(sizeof(Node));
		newnode->elem = v[i]; //b
		newnode->next = NULL; //b
		//3a
        // printf("key = %d\n", key);
		if (B[key]->begin == NULL) B[key]->begin = newnode; //b
		else (B[key]->end)->next = newnode; //b

		B[key]->end = newnode; //b
		//3b+c+2b+a+c
	}
	//n(a+5b+2c)

	// 4 - percorre cada bucket, removendo os elementos do inicio da fila e inserindo na posicao correta
	int j; // percorre buckets
	i = 0; // percorre vetor de entrada //b
	for (j = 0; j < k; j++) { //a+c
		Node *pos;
		pos = B[j]->begin; //b
		while (pos != NULL) { //c
			v[i] = pos->elem; //b
			i++; //a+b
			Node *del = pos; //b
			pos = pos->next; //b
			B[j]->begin = pos; //b
			free(del); 
		}
	}
	//(n+K)(a+5b+2c) 
	
	//total = 2Nc + 2Nb + Kb + Na + 5Nb + 2Nc + Na + 5Nb + 2Nc + Ka + 5Kb + 2Kc
	//		= 6Nc + 12Nb + 6Kb + 2Na + Ka + 2Kc
	// 		= n(2a+12b+6c) + K(a+6b+2c)
	//		= n + K
    for(int i = 0; i <= k; i++) 
        free(B[i]);
	free(B);
}

void countingSort(int* vetor, int n, int max) {

	int* vcop = (int*) malloc(n * sizeof(int)); 
    int min;
	max = min = vetor[0]; // chave inicial
	for (int i = 0; i < n; i++) {
		if (vetor[i] > max) max = vetor[i]; // maior
		if (vetor[i] < min) min = vetor[i]; // menor
		vcop[i] = vetor[i]; // copia "rasa" da struct (cuidado aqui)
	}

	// aloca vetor de contagem
	int* C = (int *) calloc( (max-min)+1, sizeof(int) );
	
	// 3.o - contagem acumulada das chaves
	// contagem de cada chave  
	for (int i = 0; i < n; i++) {
		int pos_key = vetor[i]-min; // desloca min=0
		C[pos_key]++; // incrementa ocorrencia da chave
	}

	// acumular a contagem (cada posicao indica quantos
	// valores no vetor sao menores do que aquela chave)
	//  2  3  4  5  6 => chaves
	//  0, 1, 2, 3, 4 => posicoes
	// [2, 6, 1, 0, 2]  contagem
	//
	// [0, 2, 8, 9, 9]  contagem acumulada
	int tot = 0;
	for (int j = 0; j <= (max-min); j++) {
		int c_ant = C[j]; // guardo n.o chaves anterior
		C[j] = tot; // acumulado antes de j
		tot = tot + c_ant; // atualizo total acumulado
	}

	// 4 - percorrer o vetor de copia e produzir
	//     o posicionamento correto no vetor original
	for (int i = 0; i < n; i++) {
		int pos_ord = C[vcop[i]-min];

		// atribui a posicao correta no vetor original
		vetor[pos_ord] = vcop[i];

		// atualiza a proxima posicao da chave
		C[vcop[i]-min]++;
	}

	free(vcop);
	free(C);
}

void printArray(int *array, int began, int end){
    int size = end - began;
    for(int i = began; i < size; i++)
        printf("%d,", array[i]);
}

int timeMeasure(int size, int iterations, char* mode){
    double time_taken;
    int max = size;
    clock_t t, totalTime = 0;
    int *array = randomArr(size, max);
    // printArray(array, 0, size);

    for(int i = 0; i < iterations; i++){
        t = clock();
        if(strcmp(mode, "quick") == 0) quicksort(array, 0, size);
        else if(strcmp(mode, "heap") == 0) heapSort(array, size);
        else if(strcmp(mode, "merge") == 0) mergeSort(array, 0, size);
        else if(strcmp(mode, "insertion") == 0) insertionSort(array, 0, size);
        else if(strcmp(mode, "radix") == 0) radixSort(array, size);
        else if(strcmp(mode, "bucket") == 0) bucketSort(array, size);
        else if(strcmp(mode, "counting") == 0) countingSort(array, size, max);
        else{
            printf("%s is a non-identified sorting method\n", mode);
            i = iterations;
        } 
        t = clock() - t;
        totalTime += t;
    }
    free(array);
    totalTime = totalTime / iterations;
    time_taken = ((double)totalTime)/CLOCKS_PER_SEC;
    // printf("\ntime taken = %d", (int) (time_taken*1000000));
    printf("%sSort took %f seconds to execute the sort on %d elements\n", mode, time_taken, size); 
    return (int) (time_taken*1000000);
}