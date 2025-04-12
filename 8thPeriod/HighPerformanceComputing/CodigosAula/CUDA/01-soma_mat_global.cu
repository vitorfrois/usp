/*
Soma duas matrizes quadradas 
Ilustra o uso da mem global e mem local

*/

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TAM 16
#define THREADS 3

__global__ void soma(int *A_dev_glb, int *B_dev_glb,int *C_dev_glb)
{ 
    int i = blockDim.x * blockIdx.x + threadIdx.x; 
    int j = blockDim.y * blockIdx.y + threadIdx.y; 

    if (i < TAM && j < TAM) 
    {
        C_dev_glb[i*TAM+j] = A_dev_glb[i*TAM+j] + B_dev_glb[i*TAM+j];
    }
}

int main(int argc,char **argv)
{
	int *mA_hst,*mB_hst,*mC_hst; 
    int *mA_dev,*mB_dev,*mC_dev;
    int i,j;
    
    //Aloca matrizes no host
    mA_hst=(int *)malloc(TAM*TAM*sizeof(int)); 
    mB_hst=(int *)malloc(TAM*TAM*sizeof(int)); 
    mC_hst=(int *)malloc(TAM*TAM*sizeof(int)); 

    //Aloca matrizes no device
    cudaMalloc((void**)&mA_dev,TAM*TAM*(sizeof(int))); 
    cudaMalloc((void**)&mB_dev,TAM*TAM*(sizeof(int))); 
    cudaMalloc((void**)&mC_dev,TAM*TAM*(sizeof(int))); 

    //Preenche matrizes no host
    for(i=0;i<TAM;i++)
	{
        for(j=0;j<TAM;j++)
		{
            mA_hst[i*TAM+j]=i;
            mB_hst[i*TAM+j]=-i;
        }
    }

    //Copia o conteúdo das matrizes para o device
    cudaMemcpy(mA_dev,mA_hst,TAM*TAM*(sizeof(int)), cudaMemcpyHostToDevice); 
    cudaMemcpy(mB_dev,mB_hst,TAM*TAM*(sizeof(int)), cudaMemcpyHostToDevice); 

    //Define a quantidade de threads por bloco
    dim3 threadsPerBlock(THREADS,THREADS);

    //Define a quantidade de blocos por grade
    dim3 blocksPerGrid((TAM+(threadsPerBlock.x-1)) / threadsPerBlock.x, (TAM+(threadsPerBlock.y-1)) / threadsPerBlock.y);

    //Invoca o kernel com blocksPerGrid blocos e threadsPerBlock threads
    soma <<<blocksPerGrid,threadsPerBlock>>> (mA_dev,mB_dev,mC_dev); 

    //Copia o resultado da soma de volta para o host
    cudaMemcpy(mC_hst,mC_dev,TAM*TAM*(sizeof(int)), cudaMemcpyDeviceToHost);

    //Imprime o resultado no host. Matriz C deve ter apenas valores zero.
    for(i=0;i<TAM;i++)
	{
        for(j=0;j<TAM;j++)
            printf("%d ",mC_hst[i*TAM+j]);
        printf("\n");
    }
    
    //Desaloca matrizes no host
    free(mA_hst); 
    free(mB_hst);
    free(mC_hst);  
    
    //Desaloca matrizes no device
    cudaFree(mA_dev);
    cudaFree(mB_dev);
    cudaFree(mC_dev);
}
