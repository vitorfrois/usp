#include "busca_e_ordenacao.h"

/* Funcao que gera um vetor de inteiros aleatorios
	em um determinado intervalo de valores
   Parametros:
	int tam - tamanho do vetor a ser gerado
	int min - valor minimo
	int max - valor maximo
   Retorno:
	int*    - endereco do vetor na heap
*/
int* gera_vetor (int tam, int min, int max) {

	// verifica problemas
	if (tam < 1 || min > max) return NULL;

	int* vet = (int *) malloc(sizeof(int)*tam);

	// verifica se houve problema na alocacao
	if (vet == NULL) return NULL;

	for (int i = 0; i < tam; i++) {
		// ex. min = 0, max = 5, [0, 4] = [0,4+1] = [0, 5]
		//     min = 3, max = 8, [0, 5] + 3 = [3, 8]
		int val = (rand()%(max-min+1)) + min;
		vet[i] = val;
	}
	return vet;
}

/* Funcao que gera um vetor de inteiros ordenados
   Parametros:
	int tam - tamanho do vetor a ser gerado
	int min - valor minimo
	int max - valor maximo
   Retorno:
	int*    - endereco do vetor na heap
*/
int* gera_vetor_ordenado(int tam, int min, int max) {

	// verifica problemas
	if (tam < 1 || min > max) return NULL;

	int* vet = (int *) malloc(sizeof(int)*tam);

	// verifica se houve problema na alocacao
	if (vet == NULL) return NULL;

	// TODO: melhorar isso pra ficar uniformemente distribuido
	int val = min;
	vet[0] = 0;
	for (int i = 0; i < tam; i++) {
		vet[i] = val;
		val = vet[i]+(rand()%2)+1;
		if (val > max) val = max;
	}
	return vet;
}

/* Funcao que gera um vetor de structs
 * 	com chaves tendo inteiros aleatorios
	em um determinado intervalo de valores
   Parametros:
	int tam - tamanho do vetor a ser gerado
	int min - valor minimo
	int max - valor maximo
   Retorno:
	int*    - endereco do vetor na heap
*/
Record* gera_vetor_rec(int tam, int min, int max) {

	// verifica problemas
	if (tam < 1 || min > max) return NULL;

	Record* vet = (Record *) malloc(sizeof(Record)*tam);

	// verifica se houve problema na alocacao
	if (vet == NULL) return NULL;

	for (int i = 0; i < tam; i++) {
		// ex. min = 0, max = 5, [0, 4] = [0,4+1] = [0, 5]
		//     min = 3, max = 8, [0, 5] + 3 = [3, 8]
		int key_aleat = (rand()%(max-min+1)) + min;
		vet[i].key = key_aleat;

		float val1_aleat = (rand()/(float)RAND_MAX)*10.0;
		vet[i].value1 = val1_aleat;

		char val2_aleat = (rand()%89+1)+33;
		vet[i].value2 = val2_aleat;
	}
	return vet;
}

/* Imprime vetor de inteiros
   Parametros
	int* v - vetor
	int  N - tamanho do vetor
*/
void imprime_vetor(int*v, int N) {
	for (int i = 0; i < N; i++)
		printf("%d ", v[i]);
	printf("\n");
}


/* Imprime vetor de inteiros
   Parametros
	int* v - vetor
	int  N - tamanho do vetor
*/
void imprime_vetor_rec(Record* v, int N) {
	for (int i = 0; i < N; i++)
		printf("[%d] %.2f %c\n", v[i].key, v[i].value1, v[i].value2);
	printf("\n");
}

/* Busca sequencial
   Parametros:
      int* - vetor de inteiros para realizar a busca
      int chave - chave a ser buscada
      int N - tamanho do vetor
   Retorno:
      int - posicao em que a chave foi encontrada, ou FAIL caso contrario
*/
int busca_sequencial(int* v, int chave, int N) {
	for (int i = 0; i < N; i++) {
		if (v[i] == chave)
			return i;
	}	
	return FAIL;
}


/* Busca sequencial (recursiva)
	OBS: NAO UTILIZAR NA PRATICA, apenas para fins didaticos
   Parametros:
      int* - vetor de inteiros para realizar a busca
      int chave - chave a ser buscada
      int N - tamanho do vetor
      int i - posicao a ser verificada (inicializada com 0)
   Retorno:
      int - posicao em que a chave foi encontrada, ou FAIL caso contrario
*/
int busca_sequencial_recursiva(int* v, int chave, int N, int i) {

	// caso base (1)
	if (i > N) return FAIL;
	// caso base (2)
	if (v[i] == chave) return i;

	// passo recursivo
	return busca_sequencial_recursiva(v, chave, N, i+1);

	// TODO: verificar o que acontece
	// return busca_sequencial_recursiva(v, chave, N, i++); n.funciona
	// return busca_sequencial_recursiva(v, chave, N, ++i); ok
	// i sera modificado
}


/* Busca binaria
	OBS: assume que o vetor esta ordenado
	TODO: analisar o algoritmo usando f(n) = c + f(n/2)
   Parametros:
      int* - vetor de inteiros para realizar a busca
      int chave - chave a ser buscada
      int ini   - posicao inicial do espaco de busca
      int fim   - posicao final do espaco de busca
   Retorno:
      int - posicao em que a chave foi encontrada, ou FAIL caso contrario
*/
int busca_binaria(int* v, int chave, int ini, int fim) {

	// 0 - caso base (busca sem sucesso)
	if (ini > fim) return FAIL;

	// 1 - calcula ponto central e verifica se chave foi encontrada
	int centro = (int)((ini+fim)/2.0);
	if (v[centro] == chave)
		return centro;

	// 2 - chamada recursiva para metade do espaco de busca
	if (chave < v[centro])
		// se chave eh menor, fim passa ser o centro-1
		return busca_binaria(v, chave, ini, centro-1);

	if (chave > v[centro])
		// se a chave eh maior, inicio passa ser centro+1
		return busca_binaria(v, chave, centro+1, fim);
	
}

/* Funcao de ordenacao Insertion sort,
	ordena os elementos do vetor passado por parametro
   Parametros:
      int* v - vetor a ser ordenado
      int  n - tamanho do vetor
*/
void insertion_sort(int* v, int n) {

	int i = 1; 

	while (i < n) {
		int chave = v[i]; // fixa chave i e compara com os anteriores
		int j = i-1; // inspeciona elemento anterior
		while (j >= 0 && chave < v[j]) {
			v[j+1] = v[j]; // movimenta elemento
			j--;
		}
		v[j+1] = chave; // copia chave para a posicao correta

		i++; // vai para a proxima chave
	}

}

/* Funcao de ordenacao Mergesort
*/
void mergesort (int* v, int ini, int fim) {

	if (fim <= ini) return; // caso base (vetor de 1 elemento)

	int centro = (int) ((fim+ini)/2.0);

	// 1 - passo recursivo (divisao)
	mergesort(v, ini, centro);   // divisao lista 1 (primeira metade)
	mergesort(v, centro+1, fim); // divisao lista 2 (segunda metade)

	// 2 - intercalacao, combinando solucoes parciais (conquista)
	// vetor auxiliar para copiar a intercalacao
	// gasta memória proporcional ao tamanho do vetor!
	int* aux = (int*) malloc(sizeof(int) * (fim-ini+1) );
	
	int i = ini;	  // indice da lista 1 (ini ate centro)
	int j = centro+1; // indice da lista 2 (centro+1 ate fim)
 	int k = 0;	  // indice do vetor auxiliar (0 ate fim-ini)

	// comparar elementos das duas listas
	while (i <= centro && j <= fim) {
		if (v[i] <= v[j]) {
			aux[k] = v[i]; 
			i++; // proximo elemento da lista 1
		} 
		else {
			aux[k] = v[j];
			j++; // proximo elemento da lista 2
		}
		k++; // proximo elemento do aux
	}

	// copia os restantes da l1
	while (i <= centro) {
		aux[k] = v[i];
		i++; k++;
	}	
	// copia os restantes da l2
	while (j <= fim) {
		aux[k] = v[j];
		j++; k++;
	}	

	// copia aux para a posicao correta do vetor original	
	for (i = ini, k = 0; i <= fim; i++, k++) {
		v[i] = aux[k];
	}
	free(aux); // libera vetor auxiliar
}

/* Funcao de ordenacao Quicksort 
   Parametros:
	int *v - vetor a ser ordenado
	int  ini - posicao inicial
	int  fim - posicao final
	int  (*eep)() - funcao de estrategia de escolha do pivo:
*/
void quicksort(int* v, int ini, int fim, int (*eep)() ) {

	// 1- caso base (vetores de tamanho 0 ou 1)
	if (ini >= fim) return;
	
	// 2- particao ao redor de um *pivo*
	// - seleciona um pivo [--- l1 ---] <= p < [--- l2 ---]
	// - percorre o inicio do vetor para garantir <= pivo
	// - percorre o fim do vetor para garantir > pivo
	int p = eep(ini, fim);

	// troca pivo com a 1.a posicao
	int tmp = v[p];
	v[p] = v[ini];
	v[ini] = tmp;

	p = ini;
	int i = ini+1; // percorre l1 <= p ++
	int j = fim;   // percorre l2 > p  --

	while (i <= j) {
		while (i <= fim && v[i] <= v[p]) i++; 
		while (v[j] > v[p]) j--; // pivo demarca o inicio

		// i e j sao candidatos a troca
		if (j > i) {
			tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}
	}
	// posicionar o vetor na sua posicao já ordenada
	// a posicao do pivo será a *j*
	tmp = v[p];
	v[p] = v[j];
	v[j] = tmp;
	p = j;

	// 3- chamadas recursivas
	quicksort(v, ini, p-1, eep);
	quicksort(v, p+1, fim, eep);
}

/* Função heapify - garantir que um nó esteja
 * em condição de heap
 * Parametros:
 * 	int* v - vetor que representa a árvore binária
 * 	int  p - posicao do nó da árvore a ser verificada
 * 	int  N - número de elementos
 */
void max_heapify(int* v, int p, int N) {

	// comecando em um nó "p"
	// 1 - verificar os filhos e, caso quebrem a condicao 
	//     de heap, trocar o maior filho com o pai
	// 2 - chamar recursivamente se houver troca
	
	// filho da esquerda
	int f = p*2;

	// garantir que o nó não é folha
	// se o filho calculado excede o tamanho do vetor
	// entao é um nó folha
	if (f > N) return;

	// verificar a condicao de heap com relacao aos filhos
	// f   = p*2 ->esq
	// f+1 = p*2 + 1 -> dir
	// se um for maior, troca e chama recursivamente
	if (v[f] > v[p] || (f+1 <= N && v[f+1] > v[p]) ) {
	
		// se entrou aqui, o que sabemos?
		// sabemos que ao menos um dos filhos é maior
		// verifico se há filho dir. e se esse é maior
		// do que o da esq.
		if (f+1 <= N && v[f+1] > v[f]) 
			f = f+1; // se for o da dir. atualizo f.

		// troca
		int tmp = v[p];
		v[p] = v[f];
		v[f] = tmp;

		// chamada recursiva (potencialmente até uma folha)
		max_heapify(v, f, N);
	}

}

/* Monta um maxheap a partir de um vetor arbitrário
 *
 * Parametro:
 * 	- int* v: árvore codificada em vetor
 * 	- int  N: numero de elementos
 */
void build_maxheap(int* v, int N) {
	int m = (int) N/2.0; // ultimo nó pai

	// executa da metade para o início    (n/2)
	for (int p = m; p >= 1; p--) {
		max_heapify(v, p, N); // ????
	}
}

/* Algoritmo de ordenacao Heapsort
 * Parametros:
 * 	- int* v: vetor (arvore)
 * 	- int  N: numero de elementos
 */
void heapsort(int* v, int N) {

	build_maxheap(v, N);

	while (N >= 2) {
		// seleciona maior : raiz
		int maior = v[1];
		// troca com o último
		v[1] = v[N];
		v[N] = maior;

		N--;

		// remontar maxheap - sempre a raiz
		max_heapify(v, 1, N);
	}
}

/* Algoritmo countingsort com registros
 * Parametros:
 * 	Record* v: vetor de structs com campo chave=key
 * 	int N: tamanho do vetor
 */
void countingsort_rec(Record* v, int N) {
	
	// 1.o - Alocar memoria para manter uma copia
	// 	 do vetor original
	Record* vcop = (Record*) malloc(N * sizeof(Record));

	// 2.o - Alocar vetor de contagem (acumulada)
	// 	 antes disso, encontrar o intervalo de chaves
	// 	 [min, max] -> alocar vetor com menor tamanho
	//         0   ultima

	// encontra maior, menor, faz copia
	int max, min;
	max = min = v[0].key; // chave inicial
	for (int i = 0; i < N; i++) {
		if (v[i].key > max) max = v[i].key; // maior
		if (v[i].key < min) min = v[i].key; // menor
		vcop[i] = v[i]; // copia "rasa" da struct (cuidado aqui)
	}

	// aloca vetor de contagem
	int* C = (int *) calloc( (max-min)+1, sizeof(int) );
	
	// 3.o - contagem acumulada das chaves
	// contagem de cada chave  
	for (int i = 0; i < N; i++) {
		int pos_key = v[i].key-min; // desloca min=0
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
	for (int i = 0; i < N; i++) {
		int pos_ord = C[vcop[i].key-min];

		// atribui a posicao correta no vetor original
		v[pos_ord] = vcop[i];

		// atualiza a proxima posicao da chave
		C[vcop[i].key-min]++;
	}

	free(vcop);
	free(C);
}

/* Algoritmo Bucketsort
 * Parametros:
 * 	Record* v: vetor de structs com campo chave=key
 * 	int N: tamanho do vetor
 */
void bucketsort(Record* v, int N) {
	
	// 1- Alocando o vetor de listas encadeadas
	// 	min max (intervalo das chaves)
	// 	primeira lista = min
	// 	ultima lista = max
	
	// encontra maior, menor
	int max, min;
	max = min = v[0].key; // chave inicial
	for (int i = 0; i < N; i++) {
		if (v[i].key > max) max = v[i].key; // maior
		if (v[i].key < min) min = v[i].key; // menor
	}

	// aloca o vetor auxiliar de listas (Buckets)
	Bucket* B = (Bucket*) calloc((max-min)+1, sizeof(Bucket));	
	// 2 - preenche os buckets com elementos do vetor original
	for (int i = 0; i < N; i++) {
		int pos_key = v[i].key-min; // bucket da chave

		// criar novo no
		Node* newnode = malloc(sizeof(Node));
		newnode->elem = v[i]; // copia
		newnode->next = NULL;
		// B[2]->begin->x05
		// B[2]->end->x7c
		//
		// x05 [4, 9.32, 'a']->next=xa5
		// xa5 [4, 5.1,  'x']->next=x7c
		// x7c [4, 8.1,  '!']->next=NULL
		
		// insere na fila
		if (B[pos_key].begin == NULL) {
			// fila vazia
			B[pos_key].begin = newnode;
		} else {
			// fila nao vazia
			// ultimo elemento aponta para o novo no
			(B[pos_key].end)->next = newnode;
		}
		// novo elemento vai sempre para o fim da fila
		B[pos_key].end = newnode; 
	}

	// 3 - Percorrer os buckets (filas), removendo os elementos
	// 	um a um e posicionando no vetor original
	
	int i = 0; // indice do vetor original
	for (int j = 0; j <= (max-min); j++) {
		//para cada bucket / fila
		Node* pos;
		pos = B[j].begin;
		// enquanto fila nao for vazia
		while (pos != NULL) {
			// copia elemento do inicio da lista
			// para o vetor de entrada
			v[i] = pos->elem;
			i++;

			// deleta o elemento e vou para o proximo
			Node *del = pos;
			pos = pos->next; // vai para proximo
			B[j].begin = pos; // proximo vira inicio
			free(del);
		}	
	}
	free(B);
}
