#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include "math.h"
/*------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <limits.h>
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaInit(void);
extern "C" bool cudaDeInit(void);
extern "C" void cudaGetLastError_Sync(void);
/*------------------------------------------------------------------------------------------*/
extern "C" void init_Matrix_Db(double* _dev_m, const int _w, const int _h, const double _d);
extern "C" void init_Matrix_Int(int* _dev_m, const int _w, const int _h, const int _v);
extern "C" void init_Matrix_UL(unsigned long * _dev_m, const int _w, const int _h, const unsigned long _d);
/*------------------------------------------------------------------------------------------*/
#if 0
extern "C" void Fill_Matrix_Int(int* _dev_m, const int _sz, const int _v);
extern "C" void Fill_Matrix_Float(float* _dev_m, const int _sz, const float _v);
extern "C" void Fill_Matrix_Db(double* _dev_m, const int _sz, const double _v);
#endif // 0
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C"  void PerformSuperpixelSLIC_gpu_lab_host_int(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,
	const int*			_host_matrix_l,
	const int*			_host_matrix_a,
	const int*			_host_matrix_b,

	int*				_host_kseedsl,
	int*				_host_kseedsa,
	int*				_host_kseedsb,
	int*				_host_kseedsx,
	int*				_host_kseedsy,
	int*				_host_klabels,
	const unsigned long		_f_m,
	const unsigned long		_f_d);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
__inline__  __device__  unsigned long CalDistLAB_Basic_Square_Int(
	const int	L0,
	const int	A0,
	const int	B0,
	const int	X0,
	const int	Y0,
	const int	L1,
	const int	A1,
	const int	B1,
	const int	X1,
	const int	Y1,
	const unsigned long		_f_m,
	const unsigned long		_f_d)
{
	const unsigned long dst = (L1 - L0)*(L1 - L0) + (B1 - B0)*(B1 - B0) + (A1 - A0)*(A1 - A0);
	const unsigned long dst_xy = (X1 - X0)*(X1 - X0) + (Y1 - Y0)*(Y1 - Y0);
	const unsigned long dist_labxy = dst + dst_xy*_f_m/_f_d;
	return dist_labxy;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void Statistics_Lab_Seed_collect_CPU_Incompletion_host_Int(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,

	const int*		_h_l,
	const int*		_h_a,
	const int*		_h_b,

	const int*			_h_klabels,

	int*				_h_kseed_L,
	int*				_h_kseed_A,
	int*				_h_kseed_B,
	int*				_h_kseed_X,
	int*				_h_kseed_Y,
	int*				_h_kseed_SZ)
{
	const int ZERO = 0;
	const int IMG_SZ = _width*_height;
	const int SEED_BUFF_SZ = _kseedsSize * sizeof(int);
	const int IMG_BUFF_SZ_DB = IMG_SZ * sizeof(double);
	const int IMG_BUFF_SZ_INT = IMG_SZ * sizeof(int);
	const int IMG_BUFF_SZ_UINT = IMG_SZ * sizeof(unsigned int);
	
	memset(_h_kseed_L,				ZERO,	SEED_BUFF_SZ);
	memset(_h_kseed_A,				ZERO,	SEED_BUFF_SZ);
	memset(_h_kseed_B,				ZERO,	SEED_BUFF_SZ);
	memset(_h_kseed_X,				ZERO,	SEED_BUFF_SZ);
	memset(_h_kseed_Y,				ZERO,	SEED_BUFF_SZ);
	memset(_h_kseed_SZ,				ZERO,	SEED_BUFF_SZ);
	
		int ind(0);
		for (register int r = 0; r < _height; r++){
			for (register int c = 0; c < _width; c++){	
				const int label_i = _h_klabels[ind];
						_h_kseed_L[label_i]		+= _h_l[ind];
						_h_kseed_A[label_i]		+= _h_a[ind];
						_h_kseed_B[label_i]		+= _h_b[ind];
						_h_kseed_X[label_i]		+= c;
						_h_kseed_Y[label_i]		+= r;
						_h_kseed_SZ[label_i]	+= 1.0;
						ind++;
			}
		}
			
		for (int k = 0; k < _kseedsSize; k++)
		{
			if (_h_kseed_SZ[k] <= 0) 
				_h_kseed_SZ[k] = 1;

			const double inv_k = 1.0 / _h_kseed_SZ[k];
			//computing inverse now to multiply, than divide later		

			_h_kseed_L[k] *= inv_k;
			_h_kseed_A[k] *= inv_k;
			_h_kseed_B[k] *= inv_k;
			_h_kseed_X[k] *= inv_k;
			_h_kseed_Y[k] *= inv_k;
			
		}
	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void Statistics_Lab_Seed_collect_CPU_Incompletion(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,
	const int*		_h_l,
	const int*		_h_a,
	const int*		_h_b,

	const int*			_dev_klabels,
	int*				_dev_kseed_L,
	int*				_dev_kseed_A,
	int*				_dev_kseed_B,
	int*				_dev_kseed_X,
	int*				_dev_kseed_Y)
{

	const int ZERO = 0;
	const int IMG_SZ = _width*_height;
	const int SEED_BUFF_SZ = _kseedsSize * sizeof(double);
	const int IMG_BUFF_SZ_DB = IMG_SZ * sizeof(double);
	const int IMG_BUFF_SZ_INT = IMG_SZ * sizeof(int);
	const int IMG_BUFF_SZ_UINT = IMG_SZ * sizeof(unsigned int);

	int*				h_klabels =		new int[IMG_SZ];
	int*				h_kseed_L =		new int[_kseedsSize];
	int*				h_kseed_A =		new int[_kseedsSize];
	int*				h_kseed_B =		new int[_kseedsSize];
	int*				h_kseed_X =		new int[_kseedsSize];
	int*				h_kseed_Y =		new int[_kseedsSize];
	int*				h_kseed_SZ =	new int[_kseedsSize];

	cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(h_klabels, _dev_klabels, IMG_BUFF_SZ_INT, cudaMemcpyDeviceToHost);

	Statistics_Lab_Seed_collect_CPU_Incompletion_host_Int(
		_kseedsSize,
		_width,
		_height,
		_h_l,
		_h_a,
		_h_b,

		h_klabels,
		h_kseed_L,
		h_kseed_A,
		h_kseed_B,
		h_kseed_X,
		h_kseed_Y,
		h_kseed_SZ);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	cudaStatus = cudaMemcpy(_dev_kseed_L,		h_kseed_L, SEED_BUFF_SZ, cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(_dev_kseed_A,		h_kseed_A, SEED_BUFF_SZ, cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(_dev_kseed_B,		h_kseed_B, SEED_BUFF_SZ, cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(_dev_kseed_X,		h_kseed_X, SEED_BUFF_SZ, cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(_dev_kseed_Y,		h_kseed_Y, SEED_BUFF_SZ, cudaMemcpyHostToDevice);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] 		h_klabels;
	delete[] 		h_kseed_L;
	delete[] 		h_kseed_A;
	delete[] 		h_kseed_B;
	delete[] 		h_kseed_X;
	delete[] 		h_kseed_Y;
	delete[] 		h_kseed_SZ;

}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
__inline__ __device__  void SetPixelLablesLab_Int(
	const int* x_offset,
	const int* y_offset,
	const int offsetSize,
	
	const int SeedWH,
	const int labelsX,
	const int labelsY,
	const int x,
	const int y,
	const int m_width,
	const int m_height,
	const int* dev_kseeds_L,
	const int* dev_kseeds_A,
	const int* dev_kseeds_B,
	const int* dev_kseeds_X,
	const int* dev_kseeds_Y,
	const int* dev_L,
	const int* dev_A,
	const int* dev_B,
	int*   klabels,
	unsigned long* distvec,
	const unsigned long		_f_m,
	const unsigned long		_f_d)
{
		unsigned long dist = 0;
		//////////////////////////////////////////////
		const int i = y*m_width + x;
		////////////////////////////////////////////
		for (int xyi = 0; xyi<offsetSize; xyi++) {
			const int nx = labelsX + x_offset[xyi];
			const int ny = labelsY + y_offset[xyi];
			if (nx >= 0 && nx<SeedWH&&ny >= 0 && ny<SeedWH) {
				const int ni = nx + ny*SeedWH;
				{
					 dist = CalDistLAB_Basic_Square_Int(
													dev_L[i], dev_A[i], dev_B[i], x, y,
													dev_kseeds_L[ni], dev_kseeds_A[ni], dev_kseeds_B[ni], dev_kseeds_X[ni], dev_kseeds_Y[ni],
						 							_f_m,
						 							_f_d);

					if (dist < distvec[i])
					{
						distvec[i] = dist;
						klabels[i] = ni;
					}
					
				}
			}

		}

}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMinimumOnLab_9Seeds_Int(
	const int kseedsSize,
		
	const int _width,
	const int _height,
	
	const int*		dev_L,
	const int*		dev_A,
	const int*		dev_B,

	const int*	dev_kseed_L,
	const int*	dev_kseed_A,
	const int*	dev_kseed_B,
	const int*	dev_kseed_X,
	const int*	dev_kseed_Y,

	int*				klabels,
	unsigned long*		distvec,

	const unsigned long		_f_m,
	const unsigned long		_f_d)
{
	const int x_offset[] = { 0,1,-1,0,0,1,-1,1,-1 };
	const int y_offset[] = { 0,0,0,1,-1,1,-1,-1,1 };

	{
		const int x = blockIdx.x*blockDim.x + threadIdx.x;
		const int y = blockIdx.y*blockDim.y + threadIdx.y;
		const int SeedWH = sqrt((float)kseedsSize);

		const int offsetSize = sizeof(x_offset) / sizeof(int);
		
		if (x >= 0 && x<_width&&y >= 0 && y<_height) {
			const int ind = x + y*_width;
			const int labels_ind = klabels[ind];
			assert(labels_ind >= -1 && labels_ind<kseedsSize);

			int labelsX = 0;
			int labelsY = 0;

			if (labels_ind == -1) {
					const float x_step = 1.0*_width		/	SeedWH;
					const float y_step = 1.0*_height	/	SeedWH;
					labelsX = x / x_step;
					labelsY = y / y_step;				
			}else {
					labelsX = labels_ind	%	SeedWH;
					labelsY = labels_ind	/	SeedWH;
			}
#if 0
			assert(x == dev_X[ind]);
			assert(y == dev_Y[ind]);
#endif // 0



			SetPixelLablesLab_Int(x_offset, y_offset, offsetSize,
					SeedWH, labelsX, labelsY, x, y,
					_width, _height,
					dev_kseed_L, dev_kseed_A, dev_kseed_B, dev_kseed_X, dev_kseed_Y,
					dev_L, dev_A, dev_B,
					klabels,
					distvec,
					_f_m,
					_f_d);

		}

	}

	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void SetMinimumOnLab_9Seeds_Super_Int(
	const int kseedsSize,

	const int _width,
	const int _height,

	const int* dev_L,
	const int* dev_A,
	const int* dev_B,

	int*	dev_kseed_L,
	int*	dev_kseed_A,
	int*	dev_kseed_B,
	int*	dev_kseed_X,
	int*	dev_kseed_Y,

	int*   klabels,
	unsigned long* distvec,

	const unsigned long		_f_m,
	const unsigned long		_f_d)
{
	cudaEvent_t start = 0, stop = 0;
	float costtime_ms=0, costtime_us = 0;
	cudaError_t cudaStatus_t = cudaEventRecord(start, 0);
	{
		dim3    threadsPerBlock(16, 16);
		dim3    numBlock((_width + threadsPerBlock.x - 1) / threadsPerBlock.x, (_height + threadsPerBlock.y - 1) / threadsPerBlock.y);

		SetMinimumOnLab_9Seeds_Int <<<numBlock, threadsPerBlock >>>(
			kseedsSize,
			_width,
			_height,

			dev_L,
			dev_A,
			dev_B,

			dev_kseed_L,
			dev_kseed_A,
			dev_kseed_B,
			dev_kseed_X,
			dev_kseed_Y,

			klabels,
			distvec,

			_f_m,
			_f_d);

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

/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_gpu_lab_dev_int(
	const int _kseedsSize,
	const int _width,
	const int _height,
	
	const int*		dev_L,
	const int*		dev_A,
	const int*		dev_B,
	
	int*			_dev_kseedsl,
	int*			_dev_kseedsa,
	int*			_dev_kseedsb,
	int*			_dev_kseedsx,
	int*			_dev_kseedsy,

	int*				_dev_klabels,
	unsigned long*			_dev_distvec,
	const unsigned long		_f_m,
	const unsigned long		_f_d)
{		
		const int SZ = _width*_height;

		init_Matrix_Int(_dev_klabels,_width,_height, -1);
		init_Matrix_UL(_dev_distvec,_width,_height, ULONG_MAX);
		

		SetMinimumOnLab_9Seeds_Super_Int(
			_kseedsSize,
			_width,
			_height,

			dev_L,
			dev_A,
			dev_B,
		
			_dev_kseedsl,
			_dev_kseedsa,
			_dev_kseedsb,
			_dev_kseedsx,
			_dev_kseedsy,

			_dev_klabels,
			_dev_distvec,
			_f_m,
			_f_d);
		
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_gpu_lab_host_int(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,
	const int*			_host_matrix_l,
	const int*			_host_matrix_a,
	const int*			_host_matrix_b,

	int*				_host_kseedsl,
	int*				_host_kseedsa,
	int*				_host_kseedsb,
	int*				_host_kseedsx,
	int*				_host_kseedsy,
	int*				_host_klabels,
	const unsigned long		_f_m,
	const unsigned long		_f_d)
{
	bool cuda_stat_t = cudaInit();
	assert(cuda_stat_t == true);
		{
		const int IMG_SZ = _width*_height;
		const int SEED_BUFF_SZ = _kseedsSize * sizeof(int);
		const int IMG_BUFF_SZ_UL =  IMG_SZ * sizeof(unsigned long);
		const int IMG_BUFF_SZ_INT = IMG_SZ * sizeof(int);
		
					cudaError_t cudaStatus;

					int*				dev_kseedsl = nullptr;
					int*				dev_kseedsa = nullptr;
					int*				dev_kseedsb = nullptr;
					int*				dev_kseedsx = nullptr;
					int*				dev_kseedsy = nullptr;

					int*				dev_klabels = nullptr;

					int*				dev_matrix_l = nullptr;
					int*				dev_matrix_a = nullptr;
					int*				dev_matrix_b = nullptr;
					
					unsigned long*		dev_distvec = nullptr;
		
					cudaStatus = cudaMalloc((void**)&dev_kseedsl, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsa, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsb, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsx, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsy, SEED_BUFF_SZ);

					cudaStatus = cudaMalloc((void**)&dev_klabels,  IMG_BUFF_SZ_INT);
					cudaStatus = cudaMalloc((void**)&dev_matrix_l, IMG_BUFF_SZ_INT);
					cudaStatus = cudaMalloc((void**)&dev_matrix_a, IMG_BUFF_SZ_INT);
					cudaStatus = cudaMalloc((void**)&dev_matrix_b, IMG_BUFF_SZ_INT);
					
					cudaStatus = cudaMalloc((void**)&dev_distvec, IMG_BUFF_SZ_UL);
						{
							cudaStatus = cudaMemcpy(dev_kseedsl,	_host_kseedsl,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsa,	_host_kseedsa,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsb,	_host_kseedsb,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsx,	_host_kseedsx,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsy,	_host_kseedsy,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							
							cudaStatus = cudaMemcpy(dev_matrix_l,	_host_matrix_l,	IMG_BUFF_SZ_INT,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_a,	_host_matrix_a, IMG_BUFF_SZ_INT,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_b,	_host_matrix_b, IMG_BUFF_SZ_INT,	cudaMemcpyHostToDevice);
																				
							cudaGetLastError_Sync();
								
							const int ITR_TIMES = 2;

							for (int itr = 0; itr < ITR_TIMES; itr++)
							{
									PerformSuperpixelSLIC_gpu_lab_dev_int(
									_kseedsSize,
									_width,
									_height,

									dev_matrix_l,
									dev_matrix_a,
									dev_matrix_b,

									dev_kseedsl,
									dev_kseedsa,
									dev_kseedsb,
									dev_kseedsx,
									dev_kseedsy,

									dev_klabels,
									dev_distvec,
									_f_m,
									_f_d);

									Statistics_Lab_Seed_collect_CPU_Incompletion(
										_kseedsSize,
										_width,
										_height,

										_host_matrix_l,
										_host_matrix_a,
										_host_matrix_b,

										dev_klabels,
										dev_kseedsl,
										dev_kseedsa,
										dev_kseedsb,
										dev_kseedsx,
										dev_kseedsy);
							}
							

							cudaStatus = cudaMemcpy(_host_kseedsl, dev_kseedsl, SEED_BUFF_SZ, cudaMemcpyDeviceToHost);
							cudaStatus = cudaMemcpy(_host_kseedsa, dev_kseedsa, SEED_BUFF_SZ, cudaMemcpyDeviceToHost);
							cudaStatus = cudaMemcpy(_host_kseedsb, dev_kseedsb, SEED_BUFF_SZ, cudaMemcpyDeviceToHost);
							cudaStatus = cudaMemcpy(_host_kseedsx, dev_kseedsx, SEED_BUFF_SZ, cudaMemcpyDeviceToHost);
							cudaStatus = cudaMemcpy(_host_kseedsy, dev_kseedsy, SEED_BUFF_SZ, cudaMemcpyDeviceToHost);
							cudaStatus = cudaMemcpy(_host_klabels, dev_klabels, IMG_BUFF_SZ_INT, cudaMemcpyDeviceToHost);

						}
					cudaFree(dev_kseedsl);
					cudaFree(dev_kseedsa);
					cudaFree(dev_kseedsb);
					cudaFree(dev_kseedsx);
					cudaFree(dev_kseedsy);
					cudaFree(dev_klabels);
					cudaFree(dev_matrix_l);
					cudaFree(dev_matrix_a);
					cudaFree(dev_matrix_b);
					cudaFree(dev_distvec);

		}	
	cuda_stat_t = cudaDeInit();
	assert(cuda_stat_t == true);
}

/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/