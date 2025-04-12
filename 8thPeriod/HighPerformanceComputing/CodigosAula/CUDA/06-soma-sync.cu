// codigo incrementa e depois decrementa valores de um vetor.
//
// este codigo exemplifica o uso de __syncthreads() e 
// o uso de memoria compartilhada criada estaticamente
// e dinamicamente.
//
// a primeira grade incrementa as posicoes de um vetor
// N vezes por thread.  Usa memoria compartilhada criada estaticamente
//
// a segunda grade decrementa da mesma forma.
// o vetor comeca com vlrs 0 (zero) e termina com 0 (zero).
// Usa memória compartilhada criada dinamicamente.
//

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

// no maximo 1024, pois determina o nr de threads no bloco
#define N 1024

__global__ void staticShdMem(int *vetD_glb) 
{
  // criacao estatica na memoria compartilhada
  __shared__ int vetD_shd[N];
  int t = threadIdx.x;

  int i, aux;

  // transfere dado da memoria global para a mem shd
  // as N threads fazem isso
  vetD_shd[t] = vetD_glb[t];
  
  // cada thread incrementa N vezes cada posicao t
  for (i = 0; i < N; i++)
  {
	__syncthreads(); // sync necessaria
	aux = vetD_shd[N-t-1];
	aux++;
	__syncthreads(); // apenas esta sync produz resultados errados
	vetD_shd[t] = aux;
  }

  // Retorna resultado para memoria global. 
  // Executado por todas as N threads.
  vetD_glb[t] = vetD_shd[t];
  
}

__global__ void dynamicShdMem(int *vetD_glb)
{
  // criacao dinamica na memoria compartilhada
  extern __shared__ int vetD_shd[];

  int t = threadIdx.x;
  
  int i, aux;

  // transfere dado da memoria global para a mem shd
  // as N threads fazem isso
  vetD_shd[t] = vetD_glb[t];  
  
  // cada thread decrementa N vezes cada posicao t
  for (i = 0; i < N; i++)
  {
	__syncthreads(); // sync necessaria
	aux = vetD_shd[N-t-1];
	aux--;
	__syncthreads(); // apenas esta sync produz resultados errados
	vetD_shd[t] = aux;
  }

  // Retorna resultado para memoria global. 
  // Executado por todas as N threads.
  vetD_glb[t] = vetD_shd[t];
}


int main(void)
{
  int vetA_h[N], vetD_h[N];
  int *vetD_d;
  int i;

  for (i = 0; i < N; i++) {
    vetA_h[i] = 0;
  }

  cudaMalloc(&vetD_d, N * sizeof(int)); 

  cudaMemcpy(vetD_d, vetA_h, N*sizeof(int), cudaMemcpyHostToDevice);
  
  // algoritmo so funciona se as threads estiverem no mesmo bloco
  // devido a limitacao do __syncthreads()
  // invoca a versao com memoria compartilhada criada estaticamente
  staticShdMem<<<1,N>>>(vetD_d);
  
  cudaMemcpy(vetD_h, vetD_d, N*sizeof(int), cudaMemcpyDeviceToHost);

  printf("Static Results(%d): ", N);
  for (i = 0; i < N; i++) 
		printf("%d ", vetD_h[i]);
  printf("\n\n");
		

//  nao eh necessario copiar o vetor d do host para o device. 
//  a grade anterior fez essa copia e o conteudo dele ainda esta no device
//  cudaMemcpy(vetD_d, vetD_h, N*sizeof(int), cudaMemcpyHostToDevice);

  // invoca a versao com memoria compartilhada criada dinamicamente
  dynamicShdMem<<<1,N,(N*sizeof(int))>>>(vetD_d);
  
  cudaMemcpy(vetD_h, vetD_d, N * sizeof(int), cudaMemcpyDeviceToHost);

  printf("Dynamic Results(%d): ", N);
  for (i = 0; i < N; i++) 
		printf("%d ", vetD_h[i]);
  printf("\n\n");

  //Desaloca vetor no device
  cudaFree(vetD_d);

  exit(0);
}
