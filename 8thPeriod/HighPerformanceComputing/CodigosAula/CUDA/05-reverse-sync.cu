/*
Troca os valores de posição em um vetor (inverte os valores no vetor).

Exemplo da necessidade da sincronização de threads de um bloco.
Exemplo para alocação dinâmica e estática de shared mem

Quando a função __syncthreads() no kernel está comentada, o resultado fica errado.
Os if's nos for's das saídas dos resultados mostram os casos errados.
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N 1024

__global__ void staticReverse(int *vetD_glb)
{
  __shared__ int vetD_shd[N];
  int t = threadIdx.x;
  int tr = N-t-1;

  vetD_shd[t] = vetD_glb[t];
  __syncthreads();
  vetD_glb[t] = vetD_shd[tr];
}

__global__ void dynamicReverse(int *vetD_glb)
{
  extern __shared__ int vetD_shd[];
  int t = threadIdx.x;
  int tr = N-t-1;

  vetD_shd[t] = vetD_glb[t];
  __syncthreads();
  vetD_glb[t] = vetD_shd[tr];
}

int main(void)
{
  int vetA_h[N], vetCtrl_h[N], vetD_h[N];
  int *vetD_d;
  int i;

  for (i = 0; i < N; i++) {
    vetA_h[i] = i;  // source
    vetCtrl_h[i] = N-i-1;  // just to check our results
    vetD_h[i] = 0;   // target
  }

  cudaMalloc(&vetD_d, N * sizeof(int)); 

  // copy vet a into device global memory
  cudaMemcpy(vetD_d, vetA_h, N*sizeof(int), cudaMemcpyHostToDevice);

  // run version with static shared memory
  staticReverse<<<1,N>>>(vetD_d);

  // copy results from device to host memory
  cudaMemcpy(vetD_h, vetD_d, N*sizeof(int), cudaMemcpyDeviceToHost);

  printf("Static Results(%d): ", N);
  for (i = 0; i < N; i++) 
	if (vetD_h[i] != vetCtrl_h[i])
		printf("vetD_h[%d]=%d, vetCtrl_h[%d]=%d \n", i, vetD_h[i], i, vetCtrl_h[i]);

  printf("\nN=%d \n", N);

  // *************************************************
  
    // copy again vet a into device global memory
  cudaMemcpy(vetD_d, vetA_h, N*sizeof(int), cudaMemcpyHostToDevice);
  
  // run dynamic shared memory version
  dynamicReverse<<<1,N,N*sizeof(int)>>>(vetD_d);

  // copy results from device to host memory
  cudaMemcpy(vetD_h, vetD_d, N * sizeof(int), cudaMemcpyDeviceToHost);

  printf("Dynamic Results(%d): ", N);
  for (i = 0; i < N; i++) 
	if (vetD_h[i] != vetCtrl_h[i])
		printf("vetD_h[%d]=%d, vetCtrl_h[%d]=%d \n", i, vetD_h[i], i, vetCtrl_h[i]);
  printf("\nN=%d \n", N);

  
  // device memory free!!!!
  cudaFree(vetD_d);

  exit(0);
}
