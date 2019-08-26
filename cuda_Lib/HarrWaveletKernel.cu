#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
//#include<stdio.h>
#include<assert.h>
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaInit_CUI(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaDeInit_CUI(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void cudaGetLastError_Sync_CUI(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void HarrTransformLet_MatrixSub_thread(
	unsigned char *matrixA, 
	unsigned char *matrixB, 
	int height, 
	int width, 
	unsigned char *result)
{
	int x =blockIdx.x*blockDim.x+threadIdx.x;
	int y =blockIdx.y*blockDim.y+threadIdx.y;
	if(x>=0&&x<width&&y>=0&&y<height){
		int index=y * width + x;			
		result[index]= matrixA[index] - matrixB[index] + 128; 
	}

}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
void HarrTransformLet_MatrixSub_gpu(
	unsigned char *matrixA, 
	unsigned char *matrixB, 
	int height, 
	int width, 
	unsigned char *result)
{
	unsigned char *matixaA_dev;
	unsigned char *matrixB_dev;
	unsigned char *result_dev;
	cudaError_t cudaStatus;
	assert(cudaInit_CUI()==true);
	//////////////////////////////////////////////////////////////////////////////
	cudaStatus=cudaMalloc((void**)&matixaA_dev, width*height*sizeof(unsigned char));
	cudaStatus=cudaMalloc((void**)&matrixB_dev,width*height*sizeof(unsigned char));
	cudaStatus=cudaMalloc((void**)&result_dev,width*height*sizeof(unsigned char));

	cudaStatus = cudaMemcpy(matixaA_dev,matrixA, width*height*sizeof(unsigned char), cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(matrixB_dev,matrixB,width*height*sizeof(unsigned char), cudaMemcpyHostToDevice);
	dim3    threadsPerBlock(16,16);
	dim3    numBlock((width+threadsPerBlock.x-1)/threadsPerBlock.x,(height+threadsPerBlock.y-1)/threadsPerBlock.y);
	HarrTransformLet_MatrixSub_thread<<<numBlock,threadsPerBlock>>>(
											matixaA_dev,
											matrixB_dev,											
											height,
											width,
											result_dev);
	cudaGetLastError_Sync_CUI();
	cudaMemcpy(result,result_dev,width*height*sizeof(unsigned char),cudaMemcpyDeviceToHost);

	cudaFree(matixaA_dev);
	cudaFree(matrixB_dev);
	cudaFree(result_dev);
	////////////////////////////////////////////////////////////////////////////
	assert(cudaDeInit_CUI()==true);

}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/