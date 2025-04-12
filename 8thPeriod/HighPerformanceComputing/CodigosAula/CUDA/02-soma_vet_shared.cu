/*
Soma dois vetores
Ilustra a alocação dinâmica da memoria compartilhada
*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TAM 16
#define TPB 256

__global__ void soma(int *vetA_glb, int *vetB_glb,int *vetC_glb){ 

	// alocacao dinamica de vetC_shd
    extern __shared__ int vetC_shd[];

    int idx = blockDim.x * blockIdx.x + threadIdx.x; 

    if (idx < TAM) 
    {
        vetC_shd[idx] = vetA_glb[idx]+vetB_glb[idx];
        vetC_glb[idx] = vetC_shd[idx];
    }
}

int main(int argc,char **argv){
    int *vetA_h,*vetB_h,*vetC_h;
    int *vetA_d,*vetB_d,*vetC_d;

	int i, blocksPerGrid; 

    //Aloca os vetores no host
    vetA_h=(int *)malloc(TAM * sizeof(int)); 
    vetB_h=(int *)malloc(TAM * sizeof(int)); 
    vetC_h=(int *)malloc(TAM * sizeof(int)); 

    //Aloca os vetores no device
    cudaMalloc((void**)&vetA_d,TAM*(sizeof(int))); 
    cudaMalloc((void**)&vetB_d,TAM*(sizeof(int))); 
    cudaMalloc((void**)&vetC_d,TAM*(sizeof(int))); 
    
    //Preenche os vetores no host
    for(i=0;i<TAM;i++){
        vetA_h[i]=i;
        vetB_h[i]=0; //-i;
    }
    
    //Copia o conteúdo dos vetores para o device
    cudaMemcpy(vetA_d,vetA_h,TAM*(sizeof(int)), cudaMemcpyHostToDevice); 
    cudaMemcpy(vetB_d,vetB_h,TAM*(sizeof(int)), cudaMemcpyHostToDevice); 

    //Define a quantidade de blocos por grade
    blocksPerGrid=(TAM+TPB-1)/TPB; 
	
    //Calcula o tempo de execução do kernel com eventos
    // cudaEvent_t start, stop;
    // float gpu_time = 0.0f;
    // cudaEventCreate(&start);
    // cudaEventCreate(&stop);
    // cudaEventRecord(start, 0);
    
    //Invoca o kernel com blocksPerGrid blocos e threadsPerBlock threads
    soma <<<blocksPerGrid,TPB,TAM*sizeof(int)>>> (vetA_d,vetB_d,vetC_d);
    
    //Calcula o tempo de execução do kernel com eventos
    // cudaDeviceSynchronize();
    // cudaEventRecord(stop, 0);
    // cudaEventSynchronize(stop);
    // cudaEventElapsedTime(&gpu_time, start, stop);
    // printf("%.5f\n", gpu_time);
    // cudaEventDestroy(start);
    // cudaEventDestroy(stop);

    //Copia o resultado da soma de volta para o host
    cudaMemcpy(vetC_h,vetC_d,TAM*(sizeof(int)), cudaMemcpyDeviceToHost);

    //Imprime o resultado no host
    for(i=0;i<TAM;i++){
       printf("%d ",vetC_h[i]);
    }
    
    //Desaloca os vetores no host
    free(vetA_h); 
    free(vetB_h);
    free(vetC_h);  
    
    //Desaloca os vetores no device
    cudaFree(vetA_d);
    cudaFree(vetB_d);
    cudaFree(vetC_d);
}