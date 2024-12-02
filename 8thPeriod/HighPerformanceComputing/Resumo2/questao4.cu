#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void soma(int *vetorA, int *vetorB, int *vetorC, int tam, int iter) {
  int idx = blockDim.x * blockIdx.x + threadIdx.x;
  if (idx < tam) {
    vetorC[idx] = vetorA[idx] + vetorB[idx];
    printf("Iter=%d, Blc=%d, Thread=%d, Tam=%d, VetC[%d]=%d \n", iter,
           blockIdx.x, threadIdx.x, tam, idx, vetorC[idx]);
  }
}
int main(int argc, char **argv) {
  int i, *vetorA, *vetorB, *vetorC, threadsPerBlock;
  int *vetorA_d, *vetorB_d, *vetorC_d;

  cudaStream_t stream;

  cudaStreamCreate(&stream);

  int tam = 16;

  threadsPerBlock = 2;

  int streams_nr = 2;

  int threadsPerGrid = tam / streams_nr;

  int blocksPerGrid = (threadsPerGrid + threadsPerBlock - 1) / threadsPerBlock;

  cudaMallocHost((void **)&vetorA, tam * (sizeof(int)));
  cudaMallocHost((void **)&vetorB, tam * (sizeof(int)));
  cudaMallocHost((void **)&vetorC, tam * (sizeof(int)));
  cudaMalloc((void **)&vetorA_d, threadsPerGrid * (sizeof(int)));
  cudaMalloc((void **)&vetorB_d, threadsPerGrid * (sizeof(int)));
  cudaMalloc((void **)&vetorC_d, threadsPerGrid * (sizeof(int)));
  for (i = 0; i < tam; i++) {
    vetorA[i] = i;
    vetorB[i] = 0;
  }
  printf("Host: tam=%d, streams_nr=%d, TPG=%d, BPG=%d, TPB=%d \n", tam,
         streams_nr, threadsPerGrid, blocksPerGrid, threadsPerBlock);
  for (i = 0; i < tam; i += threadsPerGrid) {
    if ((tam - i) < threadsPerGrid)
      threadsPerGrid = tam - i;
    cudaMemcpyAsync(vetorA_d, vetorA + i, threadsPerGrid * (sizeof(int)),
                    cudaMemcpyHostToDevice, stream);
    cudaMemcpyAsync(vetorB_d, vetorB + i, threadsPerGrid * (sizeof(int)),
                    cudaMemcpyHostToDevice, stream);
    soma<<<blocksPerGrid, threadsPerBlock, 0, stream>>>(
        vetorA_d, vetorB_d, vetorC_d, threadsPerGrid, i);

    cudaMemcpyAsync(vetorC + i, vetorC_d, threadsPerGrid * (sizeof(int)),
                    cu daMemcpyDeviceToHost, stream);
  }
  cudaStreamSynchronize(stream);
  for (i = 0; i < tam; i++) {
    printf("%d ", vetorC[i]);
  }
  cudaFreeHost(vetorA);
  cudaFreeHost(vetorB);
  cudaFreeHost(vetorC);
  cudaFree(vetorA_d);
  cudaFree(vetorB_d);

  cudaFree(vetorC_d);
  cudaStreamDestroy(stream);
}