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
extern "C" void Fill_Matrix_Int(int* _dev_m, const int _sz, const int _v);
extern "C" void Fill_Matrix_Float(float* _dev_m, const int _sz, const float _v);
extern "C" void Fill_Matrix_Db(double* _dev_m, const int _sz, const double _v);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void PerformSuperpixelSLIC_gpu_lab(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,
	const double*		_host_matrix_l,
	const double*		_host_matrix_a,
	const double*		_host_matrix_b,
	const double*		_host_matrix_x,
	const double*		_host_matrix_y,
	double*				_host_kseedsl,
	double*				_host_kseedsa,
	double*				_host_kseedsb,
	double*				_host_kseedsx,
	double*				_host_kseedsy,
	int*				_host_klabels,
	const double		_invwt);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
__inline__  __device__  double CalDistLAB_Basic_Square(
	const double	L0,
	const double	A0,
	const double	B0,
	const double	X0,
	const double	Y0,
	const double	L1,
	const double	A1,
	const double	B1,
	const double	X1,
	const double	Y1,
	const double	INVWT)
{
	const double dst = (L1 - L0)*(L1 - L0) + (B1 - B0)*(B1 - B0) + (A1 - A0)*(A1 - A0);
	const double dst_xy = (X1 - X0)*(X1 - X0) + (Y1 - Y0)*(Y1 - Y0);
	const double dist_labxy = dst + INVWT * dst_xy;
	return dist_labxy;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void Statistics_Lab_Seed_collect_CPU_Incompletion_host(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,

	const double*		_h_l,
	const double*		_h_a,
	const double*		_h_b,
	const double*		_h_x,
	const double*		_h_y,

	const int*			_h_klabels,

	double*				_h_kseed_L,
	double*				_h_kseed_A,
	double*				_h_kseed_B,
	double*				_h_kseed_X,
	double*				_h_kseed_Y,
	double*				_h_kseed_SZ)
{
	const int ZERO = 0;
	const int IMG_SZ = _width*_height;
	const int SEED_BUFF_SZ = _kseedsSize * sizeof(double);
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
	const double*		_h_l,
	const double*		_h_a,
	const double*		_h_b,
	const double*		_h_x,
	const double*		_h_y,
	const int*			_dev_klabels,
	double*				_dev_kseed_L,
	double*				_dev_kseed_A,
	double*				_dev_kseed_B,
	double*				_dev_kseed_X,
	double*				_dev_kseed_Y)
{

	const int ZERO = 0;
	const int IMG_SZ = _width*_height;
	const int SEED_BUFF_SZ = _kseedsSize * sizeof(double);
	const int IMG_BUFF_SZ_DB = IMG_SZ * sizeof(double);
	const int IMG_BUFF_SZ_INT = IMG_SZ * sizeof(int);
	const int IMG_BUFF_SZ_UINT = IMG_SZ * sizeof(unsigned int);

	int*				h_klabels =		new int[IMG_SZ];
	double*				h_kseed_L =		new double[_kseedsSize];
	double*				h_kseed_A =		new double[_kseedsSize];
	double*				h_kseed_B =		new double[_kseedsSize];
	double*				h_kseed_X =		new double[_kseedsSize];
	double*				h_kseed_Y =		new double[_kseedsSize];
	double*				h_kseed_SZ =	new double[_kseedsSize];

	cudaError_t cudaStatus;

	cudaStatus = cudaMemcpy(h_klabels, _dev_klabels, IMG_BUFF_SZ_INT, cudaMemcpyDeviceToHost);

	Statistics_Lab_Seed_collect_CPU_Incompletion_host(
		_kseedsSize,
		_width,
		_height,
		_h_l,
		_h_a,
		_h_b,
		_h_x,
		_h_y,
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
__inline__ __device__  void SetPixelLablesLab(
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
	const double* dev_kseeds_L,
	const double* dev_kseeds_A,
	const double* dev_kseeds_B,
	const double* dev_kseeds_X,
	const double* dev_kseeds_Y,
	const double* dev_L,
	const double* dev_A,
	const double* dev_B,
	const double* dev_X,
	const double* dev_Y,
	int*   klabels,
	double* distvec,
	const double _invwt)
{
		double dist = 0;
		//////////////////////////////////////////////
		const int i = y*m_width + x;
		////////////////////////////////////////////
		for (int xyi = 0; xyi<offsetSize; xyi++) {
			const int nx = labelsX + x_offset[xyi];
			const int ny = labelsY + y_offset[xyi];
			if (nx >= 0 && nx<SeedWH&&ny >= 0 && ny<SeedWH) {
				const int ni = nx + ny*SeedWH;
				{
					 dist = CalDistLAB_Basic_Square(
													dev_L[i], dev_A[i], dev_B[i], dev_X[i], dev_Y[i],
													dev_kseeds_L[ni], dev_kseeds_A[ni], dev_kseeds_B[ni], dev_kseeds_X[ni], dev_kseeds_Y[ni],
													_invwt);

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
__global__ void SetMinimumOnLab_9Seeds(
	const int kseedsSize,
		
	const int _width,
	const int _height,
	
	const double*		dev_L,
	const double*		dev_A,
	const double*		dev_B,
	const double*		dev_X,
	const double*		dev_Y,

	const double*	dev_kseed_L,
	const double*	dev_kseed_A,
	const double*	dev_kseed_B,
	const double*	dev_kseed_X,
	const double*	dev_kseed_Y,

	int*   klabels,
	double* distvec,

	const double _invwt)
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

			SetPixelLablesLab(x_offset, y_offset, offsetSize,
					SeedWH, labelsX, labelsY, x, y,
					_width, _height,
					dev_kseed_L, dev_kseed_A, dev_kseed_B, dev_kseed_X, dev_kseed_Y,
					dev_L, dev_A, dev_B, dev_X, dev_Y,
					klabels,
					distvec,
					_invwt);

		}

	}

	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
void SetMinimumOnLab_9Seeds_Super(
	const int kseedsSize,

	const int m_width,
	const int m_height,

	const double* dev_L,
	const double* dev_A,
	const double* dev_B,
	const double* dev_X,
	const double* dev_Y,

	double*	dev_kseed_L,
	double*	dev_kseed_A,
	double*	dev_kseed_B,
	double*	dev_kseed_X,
	double*	dev_kseed_Y,

	int*   klabels,
	double* distvec,

	const double _invwt)
{
	cudaEvent_t start = 0, stop = 0;
	float costtime_ms=0, costtime_us = 0;
	cudaError_t cudaStatus_t = cudaEventRecord(start, 0);
	{
		dim3    threadsPerBlock(16, 16);
		dim3    numBlock((m_width + threadsPerBlock.x - 1) / threadsPerBlock.x, (m_height + threadsPerBlock.y - 1) / threadsPerBlock.y);

		SetMinimumOnLab_9Seeds <<<numBlock, threadsPerBlock >>>(
			kseedsSize,
			m_width,
			m_height,

			dev_L,
			dev_A,
			dev_B,
			dev_X,
			dev_Y,

			dev_kseed_L,
			dev_kseed_A,
			dev_kseed_B,
			dev_kseed_X,
			dev_kseed_Y,

			klabels,
			distvec,

			_invwt);

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
void PerformSuperpixelSLIC_gpu_lab_dev(
	const int _kseedsSize,
	const int _width,
	const int _height,
	
	const double*		dev_L,
	const double*		dev_A,
	const double*		dev_B,
	const double*		dev_X,
	const double*		dev_Y,
	
	double*				_dev_kseedsl,
	double*				_dev_kseedsa,
	double*				_dev_kseedsb,
	double*				_dev_kseedsx,
	double*				_dev_kseedsy,

	int*				_dev_klabels,
	double*				_dev_distvec,
	const double		_invwt)
{
		const int SZ = _width*_height;
		
		Fill_Matrix_Db(_dev_distvec, SZ , DBL_MAX);
	
		SetMinimumOnLab_9Seeds_Super(
			_kseedsSize,
			_width,
			_height,

			dev_L,
			dev_A,
			dev_B,
			dev_X,
			dev_Y,

			_dev_kseedsl,
			_dev_kseedsa,
			_dev_kseedsb,
			_dev_kseedsx,
			_dev_kseedsy,

			_dev_klabels,
			_dev_distvec,
			_invwt);
		
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
void PerformSuperpixelSLIC_gpu_lab(
	const int			_kseedsSize,
	const int			_width,
	const int			_height,
	const double*		_host_matrix_l,
	const double*		_host_matrix_a,
	const double*		_host_matrix_b,
	const double*		_host_matrix_x,
	const double*		_host_matrix_y,
	double*				_host_kseedsl,
	double*				_host_kseedsa,
	double*				_host_kseedsb,
	double*				_host_kseedsx,
	double*				_host_kseedsy,
	int*				_host_klabels,
	const double		_invwt)
{
	bool cuda_stat_t = cudaInit();
	assert(cuda_stat_t == true);
		{
		const int IMG_SZ = _width*_height;
		const int SEED_BUFF_SZ = _kseedsSize * sizeof(double);
		const int IMG_BUFF_SZ_DB = IMG_SZ * sizeof(double);
		const int IMG_BUFF_SZ_INT = IMG_SZ * sizeof(int);
		
					cudaError_t cudaStatus;

					double*				dev_kseedsl = nullptr;
					double*				dev_kseedsa = nullptr;
					double*				dev_kseedsb = nullptr;
					double*				dev_kseedsx = nullptr;
					double*				dev_kseedsy = nullptr;

					int*				dev_klabels = nullptr;

					double*				dev_matrix_l = nullptr;
					double*				dev_matrix_a = nullptr;
					double*				dev_matrix_b = nullptr;
					double*				dev_matrix_x = nullptr;
					double*				dev_matrix_y = nullptr;

					double*				dev_distvec = nullptr;
		
					cudaStatus = cudaMalloc((void**)&dev_kseedsl, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsa, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsb, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsx, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_kseedsy, SEED_BUFF_SZ);
					cudaStatus = cudaMalloc((void**)&dev_klabels, IMG_BUFF_SZ_INT);
					cudaStatus = cudaMalloc((void**)&dev_matrix_l,  IMG_BUFF_SZ_DB);
					cudaStatus = cudaMalloc((void**)&dev_matrix_a,  IMG_BUFF_SZ_DB);
					cudaStatus = cudaMalloc((void**)&dev_matrix_b,  IMG_BUFF_SZ_DB);
					cudaStatus = cudaMalloc((void**)&dev_matrix_x,	IMG_BUFF_SZ_DB);
					cudaStatus = cudaMalloc((void**)&dev_matrix_y,	IMG_BUFF_SZ_DB);

					cudaStatus = cudaMalloc((void**)&dev_distvec,	IMG_BUFF_SZ_DB);
						{
							cudaStatus = cudaMemcpy(dev_kseedsl,	_host_kseedsl,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsa,	_host_kseedsa,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsb,	_host_kseedsb,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsx,	_host_kseedsx,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_kseedsy,	_host_kseedsy,	SEED_BUFF_SZ,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_klabels,	_host_klabels,	IMG_BUFF_SZ_INT,cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_l,	_host_matrix_l,	IMG_BUFF_SZ_DB,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_a,	_host_matrix_a,	IMG_BUFF_SZ_DB,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_b,	_host_matrix_b,	IMG_BUFF_SZ_DB,	cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_x,	_host_matrix_x,	IMG_BUFF_SZ_DB, cudaMemcpyHostToDevice);
							cudaStatus = cudaMemcpy(dev_matrix_y,	_host_matrix_y,	IMG_BUFF_SZ_DB, cudaMemcpyHostToDevice);
														
							cudaGetLastError_Sync();
								
							const int ITR_TIMES = 2;

							for (int itr = 0; itr < ITR_TIMES; itr++)
							{
									PerformSuperpixelSLIC_gpu_lab_dev(
									_kseedsSize,
									_width,
									_height,

									dev_matrix_l,
									dev_matrix_a,
									dev_matrix_b,
									dev_matrix_x,
									dev_matrix_y,

									dev_kseedsl,
									dev_kseedsa,
									dev_kseedsb,
									dev_kseedsx,
									dev_kseedsy,

									dev_klabels,
									dev_distvec,
									_invwt);

									Statistics_Lab_Seed_collect_CPU_Incompletion(
										_kseedsSize,
										_width,
										_height,


										_host_matrix_l,
										_host_matrix_a,
										_host_matrix_b,
										_host_matrix_x,
										_host_matrix_y,


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
					cudaFree(dev_matrix_x);
					cudaFree(dev_matrix_y);
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