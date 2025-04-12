/*
Soma dois vetores
Ilustra o uso da memória unificada (managed memory)
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TAM 16
#define TPB 256

__global__ void soma(int *vetA_glb, int *vetB_glb,int *vetC_glb){ 
    int idx = blockDim.x * blockIdx.x + threadIdx.x; 

    if (idx < TAM) 
    {
        vetC_glb[idx] = vetA_glb[idx] + vetB_glb[idx];
    }
}

int main(int argc,char **argv){
	int *vetA,*vetB,*vetC;
	int blocksPerGrid; 

    int i;
    
    //Aloca os vetores no host e no device
    cudaMallocManaged((void**)&vetA,TAM*(sizeof(int))); 
    cudaMallocManaged((void**)&vetB,TAM*(sizeof(int))); 
    cudaMallocManaged((void**)&vetC,TAM*(sizeof(int))); 
    
    //Preenche os vetores no host
    for(i=0;i<TAM;i++){
        vetA[i]=i;
        vetB[i]=0; //-i;
    }

    //Define a quantidade de blocos por grade
    blocksPerGrid=(TAM+TPB-1)/TPB; 
    
    //Calcula o tempo de execução do kernel com eventos
    cudaEvent_t start, stop;
    float gpu_time = 0.0f;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    //Invoca o kernel com blocksPerGrid blocos e threadsPerBlock threads
    soma <<<blocksPerGrid,TPB>>> (vetA,vetB,vetC); 
    
    //Calcula o tempo de execução do kernel com eventos
    cudaDeviceSynchronize();
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    
    //Sincroniza as threads do device para impressão do resultado
    cudaDeviceSynchronize();

    //Imprime o resultado no host
    for(i=0;i<TAM;i++){
       printf("%d ",vetC[i]);
    }

    printf("\nElapsed Time:%.5f (ms)\n", gpu_time);
    
    //Desaloca os vetores no device
    cudaFree(vetA);
    cudaFree(vetB);
    cudaFree(vetC);
}