#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <device_functions.h>
/*------------------------------------------------------------------------------------------*/
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/sequence.h>
#include <thrust/copy.h>
#include <thrust/fill.h>
#include <thrust/replace.h>
#include <thrust/functional.h>
/*------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <assert.h>
#include <iostream>
/*------------------------------------------------------------------------------------------*/
#if linux||__linux||__linux__ || __GNUC__

#include <unistd.h>    
#include <sys/types.h>  
#include <sys/syscall.h>//Linux system call for thread id
#include <pthread.h>

#endif
/*------------------------------------------------------------------------------------------*/
#ifdef _MSC_VER

#include <windows.h>

#endif
/*------------------------------------------------------------------------------------------*/
#define TIME_COST_FUNC (1)
/*------------------------------------------------------------------------------------------*/
extern int  GetTimeCostFunc();
extern void SetTimeCostFunc(int _t);
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaInit(void);
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaDeInit(void);
/*------------------------------------------------------------------------------------------*/
extern "C" void cudaGetLastError_Sync(void);
/*------------------------------------------------------------------------------------------*/
extern "C" void init_Matrix_Db(double* _dev_m, const int _w, const int _h, const double _d);
extern "C" void init_Matrix_Int(int* _dev_m, const int _w, const int _h, const int _v);
extern "C" void init_Matrix_UL(unsigned long * _dev_m, const int _w, const int _h, const unsigned long _d);
/*------------------------------------------------------------------------------------------*/
extern "C" void Fill_Matrix_Int(int* _dev_m, const int _sz, const int _v);
extern "C" void Fill_Matrix_Float(float* _dev_m, const int _sz, const float _v);
extern "C" void Fill_Matrix_Db(double* _dev_m, const int _sz, const double _v);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
int mTimeCostFunc = TIME_COST_FUNC;
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
int GetTimeCostFunc()
{
	return mTimeCostFunc;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
void SetTimeCostFunc(int _t)
{
	mTimeCostFunc=_t;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
int GetThreadIdSelfwinlinux(void)
{

	int thread_id = 0;
#if _DEBUG
	int device_count;
	cudaGetDeviceCount(&device_count);
#endif


#if _MSC_VER
	thread_id = ::GetCurrentThreadId();
#elif linux||__linux||__linux__||__GNUC__
	//thread_id=(struct pthread_fake *)pthread_self()->tid;
	thread_id = syscall(__NR_gettid);
#else
	thread_id = -1;
	assert(0);
#endif

	return thread_id;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*cuda初始化
*@retval true 初始化成功
*@retval false 初始化失败
*/
/*------------------------------------------------------------------------------------------*/
bool cudaInit(void)
{
		 int i;
		 int device_count;

		 if( cudaGetDeviceCount(&device_count) )
		 {
			 printf(" There is zero device beyond 1.0\n"); 
			 return false;
		 }
#if _DEBUG
		//printf("CUDA DEVICE NUMS: %d \n",device_count);
#endif
		 // 找到一个可用的设备
		 for(i=0;i<device_count;i++)
		 {
			  struct cudaDeviceProp device_prop;
			  if(cudaGetDeviceProperties(&device_prop,i)==cudaSuccess)
			  {
#if 0
	printf("device properties is :\n"
			"\t device name is %s\n"
			"\t totalGlobalMem is %d\n"
			"\t sharedMemPerBlock is %d\n"
			"\t regsPerBlock is %d\n"
			"\t warpSize is %d\n"
			"\t memPitch is %d\n"
			"\t maxThreadsPerBlock is %d\n"
			"\t maxThreadsDim [3] is %d X %d X %d\n"
			"\t maxGridSize [3] is %d X %d X %d\n"
			"\t totalConstMem is %d\n"
			"\t device version is major %d ,minor %d\n"
			"\t clockRate is %d\n"
			"\t textureAlignment is %d\n"
			"\t deviceOverlap is %d\n"
			"\t multiProcessorCount is %d\n",
			device_prop.name,
			device_prop.totalGlobalMem,
			device_prop.sharedMemPerBlock,
			device_prop.regsPerBlock,
			device_prop.warpSize,
			device_prop.memPitch,
			device_prop.maxThreadsPerBlock,
			device_prop.maxThreadsDim[0],device_prop.maxThreadsDim[1],device_prop.maxThreadsDim[2],
			device_prop.maxGridSize[0],device_prop.maxGridSize[1],device_prop.maxGridSize[2],
			device_prop.totalConstMem,
			device_prop.major,device_prop.minor,
			device_prop.clockRate,
			device_prop.textureAlignment,
			device_prop.deviceOverlap,
			device_prop.multiProcessorCount);
#endif				
					/* if(cudaSetDevice(i)==cudaSuccess){
						 printf("USE GPU ID: %d \n",i);
						 return true;
					 }*/
				break;
			  }

		 }
		 
		 if(i==device_count)
		 {
			  printf("Get the propertites of device occurred error\n");
			  return false;
		 }
		 //有可用设备
		 int default_id,expect_id;		 
		 int thread_id=GetThreadIdSelfwinlinux();
		 expect_id=thread_id%device_count;
		
		 printf("CUDA NUMS: %d, ID: %d,EXPECT: %d \n",device_count,thread_id,expect_id);

		 cudaGetDevice(&default_id);

		 if(default_id==expect_id){
			 return true;
		 }else{			 
			 //设备可用
			 if(cudaSetDevice(expect_id)==cudaSuccess){
				 //printf("USE GPU ID: %d \n",expect_id);
				 return true;
			 }
		 }
		 
		 //////////////////////////////////////////
	//	 int ket=kernelExecTimeoutEnabled();
		 /////////////////////////////////////////
		 return false;
	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*cuda去初始化
*@return 
*@retval true 初始化成功
*@retval false 初始化失败
*/
/*------------------------------------------------------------------------------------------*/
bool cudaDeInit(void)
{
#if 0
	cudaError_t cudaStatus;
	cudaStatus=cudaDeviceReset();
	if(cudaStatus!=cudaSuccess){
		return false;
	}else{
		return true;
	}
#else
	return true;
#endif
	
}
/*------------------------------------------------------------------------------------------*/
/**
*Cuda等待延时获取错误代码
*
*
*/
/*------------------------------------------------------------------------------------------*/
void cudaGetLastError_Sync(void)
{
	cudaError_t cudaStatus_syn,cudaStatus;
	const char  *errstr=NULL;
	
	do 
	{

		cudaStatus_syn=cudaDeviceSynchronize();
		if (cudaStatus_syn==cudaSuccess)
		{
			break;

		}else{
			cudaStatus=cudaGetLastError();
			if (cudaStatus!=cudaSuccess){
				errstr=cudaGetErrorString(cudaStatus);
				printf("cudaDeviceSynchronize: %s",errstr);
			}
		}
		
	} while (cudaStatus_syn!=cudaSuccess);

}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMatrixUnsignedLong(unsigned long *matrix, const int width, const int height, const unsigned long value_t)
{
	int ind = blockIdx.x*blockDim.x + threadIdx.x;
	const int offset = blockDim.x*gridDim.x;
	const int size_t = width*height;

	while (ind<size_t) {
		matrix[ind] = value_t;
		ind += offset;
	}

}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMatrixDouble(double *matrix,const int width,const int height,const double value_t)
{
	int ind = blockIdx.x*blockDim.x + threadIdx.x;
	const int offset = blockDim.x*gridDim.x;
	const int size_t = width*height;
	/////////////////////////////////////////
	while (ind<size_t) {
		matrix[ind] = value_t;
		ind += offset;
	}
	/////////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMatrixInt(int* _matrix, const int width, const int height, const int _v)
{
	int ind = blockIdx.x*blockDim.x + threadIdx.x;
	const int offset = blockDim.x*gridDim.x;
	const int size_t = width*height;
	while (ind<size_t) {
		_matrix[ind] = _v;
		ind += offset;
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void init_Matrix_UL(unsigned long * _dev_m, const int _w, const int _h, const unsigned long _d)
{
	cudaEvent_t start = 0, stop = 0;
	float costtime_ms = 0, costtime_us = 0;
	cudaError_t cudaStatus_t = cudaEventRecord(start, 0);
	{
		SetMatrixUnsignedLong << <16, 16 * 16 >> >(_dev_m, _w, _h, _d);
		cudaGetLastError_Sync();
	}
	cudaStatus_t = cudaEventRecord(stop, 0);
	cudaGetLastError_Sync();
	cudaStatus_t = cudaEventElapsedTime(&costtime_ms, start, stop);
	costtime_us = costtime_ms * 1000;
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void init_Matrix_Db(double* _dev_m, const int _w, const int _h, const double _d)
{
	cudaEvent_t start = 0, stop = 0;
	float costtime_ms = 0, costtime_us = 0;
	cudaError_t cudaStatus_t = cudaEventRecord(start, 0);
	{
		SetMatrixDouble <<<16, 16 * 16 >>>(_dev_m, _w, _h, _d);
		cudaGetLastError_Sync();
	}
	cudaStatus_t = cudaEventRecord(stop, 0);
	cudaGetLastError_Sync();
	cudaStatus_t = cudaEventElapsedTime(&costtime_ms, start, stop);
	costtime_us = costtime_ms * 1000;
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void init_Matrix_Int(int* _dev_m, const int _w, const int _h, const int _v)
{
	cudaEvent_t start = 0, stop = 0;
	float costtime_ms = 0, costtime_us = 0;
	cudaError_t cudaStatus_t = cudaEventRecord(start, 0);
	{
		SetMatrixInt <<<16, 16 * 16 >>>(_dev_m, _w, _h, _v);
		cudaGetLastError_Sync();
	}
	cudaStatus_t = cudaEventRecord(stop, 0);
	cudaGetLastError_Sync();
	cudaStatus_t = cudaEventElapsedTime(&costtime_ms, start, stop);
	costtime_us = costtime_ms * 1000;
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
void GetCudaDevProp(int _d)
{
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, 0);
	int blocks = prop.multiProcessorCount;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
void Fill_Matrix_Db(double* _dev_m, const int _sz, const double _v)
{
	thrust::device_ptr<double> dev_ptr(_dev_m);
	thrust::fill(dev_ptr, dev_ptr + _sz, _v);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
void Fill_Matrix_Float(float* _dev_m, const int _sz, const float _v)
{
	thrust::device_ptr<float> dev_ptr(_dev_m);
	thrust::fill(dev_ptr, dev_ptr + _sz, _v);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/
void Fill_Matrix_Int(int* _dev_m, const int _sz, const int _v)
{
	thrust::device_ptr<int> dev_ptr(_dev_m);
	thrust::fill(dev_ptr, dev_ptr + _sz, _v);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*/
/*------------------------------------------------------------------------------------------*/