/*
Multiplica um vetor por uma constante.
Exemplo para o uso de memória constante em CUDA
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TAM 100
#define VLR_ESCALAR 10
#define TPB 256

__device__ __constant__ int escalar_d;

__global__ void mult(int *vetA_glb){ 

    int idx = blockDim.x * blockIdx.x + threadIdx.x; 

    if (idx < TAM) 
    {
        vetA_glb[idx] = escalar_d * vetA_glb[idx];
    }
}

int main(int argc,char **argv){
    int *vetA_h;
    int *vetA_d;

	int blocksPerGrid;
	
	int i, escalar_h; 


    //Aloca o vetor no host
    vetA_h=(int *)malloc(TAM * sizeof(int)); 

    //Aloca o vetor no device
    cudaMalloc((void**)&vetA_d,TAM*(sizeof(int))); 
    
    //Preenche o vetor no host
    for(i=0;i<TAM;i++){
        vetA_h[i]=i;
    }

    //Copia o conteúdo do vetor para o device
    cudaMemcpy(vetA_d,vetA_h,TAM*(sizeof(int)), cudaMemcpyHostToDevice); 

    escalar_h=VLR_ESCALAR;
    //Copia o conteúdo de escalar_h, lido do terminal, para a variável constante escalar_d, no device
    cudaMemcpyToSymbol(escalar_d,&escalar_h,sizeof(int));

    //Define a quantidade de blocos por grade
    blocksPerGrid=(TAM+TPB-1)/TPB; 

    //Invoca o kernel com blocksPerGrid blocos e threadsPerBlock threads
    mult <<<blocksPerGrid,TPB>>> (vetA_d); 

    //Copia o resultado da soma de volta para o host
    cudaMemcpy(vetA_h,vetA_d,TAM*(sizeof(int)), cudaMemcpyDeviceToHost);

    //Imprime o resultado no host
    for(i=0;i<TAM;i++){
       printf("%d ",vetA_h[i]);
    }
    
    //Desaloca os vetores no host
    free(vetA_h); 
    
    //Desaloca os vetores no device
    cudaFree(vetA_d);
}