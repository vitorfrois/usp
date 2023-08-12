void swap(int *a, int *b);

/**
 * @brief Gerador de vetor aleatório
 * 
 * @param arraySize Tamanho do vetor
 * @param max Valor máximo
 * @return int* Vetor aleatório
 */
int *randomArr(int arraySize, int max);

/**
 * @brief Gerador de vetor crescente
 * 
 * @param arraySize Tamanho do vetor
 * @param max Valor máximo
 * @return int* Vetor aleatório
 */
int *increasingArr(int arraySize, int max);

/**
 * @brief Gerador de vetor decrescente
 * 
 * @param arraySize Tamanho do vetor
 * @param max Valor máximo
 * @return int* Vetor aleatório
 */
int *decreasingArr(int arraySize, int max);


void heapify(int *array, int size, int i);
void heapSort(int *array, int size);
void insertionSort(int* arr, int began, int end);
int averagePivo(int *array, int began, int end);
void quicksort(int* array, int began, int end);
void merge(int* arr, int l, int m, int r);
void mergeSort(int* arr, int l, int r);

void radixCounting(int*, int, int exp, int base);
void radixSort(int*, int);
void bucketSort(int*, int n);
void countingSort(int*, int, int);


void printArray(int *array, int began, int end);

/**
 * @brief Uma função para medir o tempo médio 
 * de cada método na ordenação de vetores aleatórios.
 * 
 * @param size Tamanho do vetor a ser analisado 
 * @param max Maior tamanho de elemento do vetor
 * @param iterations Número de iterações (números maiores evitam desvios)
 * @param mode Escolha um método disponível: merge, insertion ou bubble.
 */
int timeMeasure(int size, int iterations, char* mode);

