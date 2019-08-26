#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include "math.h"
/*------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include<assert.h>
/*------------------------------------------------------------------------------------------*/
#ifndef UINT32
typedef unsigned int UINT32;
#endif
#if linux||__linux||__linux__ || __GNUC__

#ifndef nullptr
#define nullptr 0
#endif

#ifndef _DEBUG
#define  _DEBUG 1
#endif
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
extern "C" void Fill_Matrix_Int(int* _dev_m, const int _sz, const int _v);
extern "C" void Fill_Matrix_Float(float* _dev_m, const int _sz, const float _v);
extern "C" void Fill_Matrix_Db(double* _dev_m, const int _sz, const double _v);
/*------------------------------------------------------------------------------------------*/
/**
*时间2014- 11-4
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void PerformSuperpixelSLIC_gpu(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels,
	const int			STEP,
	double*				host_edgemag,
	const double		M);
/*------------------------------------------------------------------------------------------*/
extern "C" void PerformSuperpixelSLIC_ThetaMLXY_gpu_simplify(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,   
	const int m_height,
	double*     host_sita_n,
	double*     host_m_n,
	double*     host_L_n,
	double*     host_X_n,
	double*     host_Y_n,
	double*     host_kseedsTheta,
	double*     host_kseedsM,
	double*     host_kseedsL,
	double*     host_kseedsX,
	double*     host_kseedsY,
	int*		host_klabels,
	const int			STEP);
/*------------------------------------------------------------------------------------------*/
/**
*时间2014- 11-4
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void PerformSuperpixelSLIC_gpu_simplify(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels,
	const int			STEP,
	double*				host_edgemag,
	const double		M);
extern "C" void PerformSuperpixelSLIC_gpu_simplify2(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels,
	const int			STEP,
	double*				host_edgemag,
	const double		M);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void DrawContoursAroundSegments_gpu(
	unsigned int*			ubuff,
	int*					labels,
	const int				width,
	const int				height,
	const unsigned int	color_in,
	const unsigned int  color_out);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void  GetSeedsLabxy_gpu(
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				host_m_lvec,
	double*				host_m_avec,
	double*				host_m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" int GetThreadIdSelfwinlinux(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void Get_Nighbour_E_matrix_gpu(
	int*			labels,
	const  int		NumLabels,
	UINT32 *		Matrix_E,
	const int		width,
	const int		height);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
void InitMaskTemplate(
	unsigned int*			dev_mask,
	int*					dev_labels,
	const int				width,
	const int				height,
	const int                Pixel);
void StatisticsThetaMLXY_Seed_collect_CPU_ALL(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*       host_sita_n,
	double*       host_m_n,
	double*       host_L_n,
	double*       host_X_n,
	double*       host_Y_n,	
	int*				host_klabels,
	unsigned int*       host_img_mask,
    double*	      host_kseed_sita_n,
	double*	      host_kseed_m_n,
	double*	      host_kseed_L_n,
	double*       host_kseed_X_n,
	double*	      host_kseed_Y_n);
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
#define  NULL_MATH    1
#define  MATH_USE  0
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
*cuda初始化
*@retval true 初始化成功
*@retval false 初始化失败
*/
/*------------------------------------------------------------------------------------------*/
bool cudaInit_CUI(void)
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
bool cudaDeInit_CUI(void)
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
void cudaGetLastError_Sync_CUI(void)
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
*转换LAB色彩空间成角度、模长、亮度表示法
*
*@param m_width 图像宽度
*@param m_height 图像高度
*@param L 像素点的L分量
*@param A 像素点的A分量
*@param B 像素点的B分量
*@param X 像素点的X坐标
*@param Y 像素点的Y坐标
*@param sita_n 像素点的角度 （归一化到[0,1]）
*@param m_n    像素点的模长 （归一化到[0,1]）
*@param L_n    像素点的亮度 （归一化到[0,1]）
*@param X_n    像素点的X坐标（归一化到[0,1]）
*@param Y_n    像素点的Y坐标（归一化到[0,1]）
*
*/
/*------------------------------------------------------------------------------------------*/
__inline__ __host__ __device__ void ConvertLab2oml(
	int m_width,
	int m_height,
	double L,
	double A,
	double B,
	double X,
	double Y,
	double* sita_n,
	double* m_n,
	double* L_n,
	double* X_n,
	double* Y_n)
{
	assert(L>=0&&L<=100+1);
	assert(A>=-128&&A<=128+1);
	assert(B>=-128&&B<=128+1);
	assert(X>=0&&X<=m_width+1);
	assert(Y>=0&&Y<=m_height+1);
#if 1
	///////////////////////////////////////
	*sita_n=atan2(B,A);
	*sita_n=*sita_n/(2*3.1415927)+0.5;
	///////////////////////////////////////
	*m_n=sqrt(A*A+B*B);
	*m_n=*m_n/(128*1.415);
	///////////////////////////////////////
	*L_n=L/100;
	assert(*L_n>=0&&*L_n<=1+1E-1);
	///////////////////////////////////////
	*X_n=X/m_width;
	assert(*X_n>=0&&*X_n<=1+1E-1);
	*Y_n=Y/m_height;
	assert(*Y_n>=0&&*Y_n<=1+1E-1);
#endif
	assert(*sita_n>=0-0.1&&*sita_n<=1+0.1);
	assert(*m_n>=0-0.1&&*m_n<=1+0.1);
	assert(*L_n>=0-0.1&&*L_n<=1+0.1);
	assert(*X_n>=0-0.1&&*X_n<=1+0.1);
	assert(*Y_n>=0-0.1&&*Y_n<=1+0.1);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*计算两个像素点的距离
*@image html image027.png "色彩公式"
*@image html image029.png "距离公式"
*@image html image031.png "距离综合公式"
*
*
*@param  alpha     角度系数
*@param  betta     模长系数
*@param  gama      亮度系数
*@param  fai       距离系数
*@param  sita_n0   像素0的角度
*@param  m_n0      像素0的模长
*@param  L_n0      像素0的亮度
*@param  X_n0      像素0的等价X坐标
*@param  Y_n0      像素0的等价Y坐标
*@param  sita_n1   像素1的角度
*@param  m_n1      像素1的模长
*@param  L_n1      像素1的亮度
*@param  X_n1      像素1的等价X坐标
*@param  Y_n1      像素1的等价Y坐标
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__inline__ __device__ double  CalculateNewDistance(
	float alpha,
	float betta,
	float gama,
	float fai,
	double sita_n0,
	double m_n0,
	double L_n0,
	double X_n0,
	double Y_n0,
	double sita_n1,
	double m_n1,
	double L_n1,
	double X_n1,
	double Y_n1)
{
	/*alpha=0.6;
	betta=0.3;
	gama=1-alpha-betta;*/
	/*float fai=100;*/
	assert(sita_n0>=0-0.1&&sita_n0<=1+0.1);
	assert(L_n0>=0-0.1&&L_n0<=1+0.1);
	assert(X_n0>=0-0.1&&X_n0<=1+0.1);
	assert(Y_n0>=0-0.1&&Y_n0<=1+0.1);
	assert(sita_n1>=0-0.1&&sita_n1<=1+0.1);
    assert(L_n1>=0-0.1&&L_n1<=1+0.1);
	assert(X_n1>=0-0.1&&X_n1<=1+0.1);
	assert(Y_n1>=0-0.1&&Y_n1<=1+0.1);
#if 0
	double dst=alpha*fabs(sita_n1-sita_n0)+betta*fabs(m_n1-m_n0)+gama*fabs(L_n1-L_n0);
	double dst_xy=fai*sqrt((X_n1-X_n0)*(X_n1-X_n0)+(Y_n1-Y_n0)*(Y_n1-Y_n0));
	dst+=dst_xy;
	return dst;
#else
	double dst=alpha*fabs(sita_n1-sita_n0)+betta*fabs(m_n1-m_n0)+gama*fabs(L_n1-L_n0);
	double dst_xy=fai*(fabs(X_n1-X_n0)+fabs(Y_n1-Y_n0));
	dst+=dst_xy;
	return dst;
#endif
	
}
/*------------------------------------------------------------------------------------------*/
/**
*一个像素与所有种子计算距离保留最小值
*
*@param     kseedsSize 种子个数 
*@param     alpha      角度系数
*@param     betta      模长系数
*@param     gama       亮度系数
*@param     fai        距离参数
*@param     m_width    图像宽度
*@param     m_height   图像高度
*@param   [in]  m_lvec     图像L分量
*@param   [in]  m_avec     图像A分量
*@param   [in] m_bvec     图像B分量
*@param   [in]  dev_sita_n  图像角度分量
*@param   [in] dev_m_n    图像模长分量
*@param   [in]  dev_L_n   图像亮度分量
*@param   [in] dev_X_n   图像X分量
*@param   [in]  dev_Y_n   图像Y分量
*@param   [in]  kseedsl   种子的L分量
*@param   [in] kseedsa   种子的A分量
*@param   [in] kseedsb   种子的B分量
*@param   [in] kseedsx   种子的X坐标分量
*@param   [in] kseedsy   种子的Y坐标分量
*@param   [in] dev_kseed_sita_n  种子角度分量
*@param   [in] dev_kseed_m_n     种子模长分量
*@param   [in] dev_kseed_L_n     种子的L分量
*@param   [in] dev_kseed_X_n     种子的X分量
*@param   [in] dev_kseed_Y_n     种子的Y分量
*@param   [in] klabels           图像的标定信息
*@param   [in] distvec           未使用
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMinimumOnLab(
	const int kseedsSize,
	float alpha,
	float betta,
	float gama,
	float fai,
	const int m_width,
	const int m_height,
	double* m_lvec,
	double* m_avec,
	double* m_bvec,
	double* kseedsl,
	double* kseedsa,
	double* kseedsb,
	double* kseedsx,
	double* kseedsy,
	int*   klabels,
	double* distvec,
	const int			STEP,
	const double		M)
{

	int x1, y1, x2, y2;
	double l, a, b;
	double dist;
	//double distxy;
	int SpIdx = threadIdx.x+blockIdx.x*blockDim.x;
	int n=SpIdx;
	int offset = STEP;
	if (SpIdx<kseedsSize){
#if 1
///////////////////////////////////////////////
		y1 = max(0.0,			kseedsy[n]-offset);
		y2 = min((double)m_height,	kseedsy[n]+offset);
		x1 = max(0.0,			kseedsx[n]-offset);
		x2 = min((double)m_width,	kseedsx[n]+offset);
	//////////////////////////////////////////////
		for( int y = y1; y < y2; y++ )
			{
				for( int x = x1; x < x2; x++ )
				{
					int i = y*m_width + x;

					l = m_lvec[i];
					a = m_avec[i];
					b = m_bvec[i];
#if 0
					dist =			(l - kseedsl[n])*(l - kseedsl[n]) +
						(a - kseedsa[n])*(a - kseedsa[n]) +
						(b - kseedsb[n])*(b - kseedsb[n]);
					//if (itr>5)
					{
						distxy =		(x - kseedsx[n])*(x - kseedsx[n]) +
							(y - kseedsy[n])*(y - kseedsy[n]);
					}
					//else
					//{
					//	distxy =0;
					//}
					//------------------------------------------------------------------------
					dist += distxy*invwt;//dist = sqrt(dist) + sqrt(distxy*invwt);//this is more exact
					//------------------------------------------------------------------------
#endif
#if 1
					double sita_n, m_n, L_n, X_n, Y_n;
					double Ksita_n, Km_n, KL_n, KX_n, KY_n;
					ConvertLab2oml(m_width,m_height,l,a,b,x,y,&sita_n,&m_n,&L_n,&X_n,&Y_n);
					ConvertLab2oml(m_width,m_height,kseedsl[n],kseedsa[n],kseedsb[n],kseedsx[n],kseedsy[n],&Ksita_n,&Km_n,&KL_n,&KX_n,&KY_n);
					dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
#endif
					if( dist < distvec[i] )
					{
						distvec[i] = dist;
						klabels[i]  = n;
						//atomicExch(&klabels[i],n);
					}
				}
			}

#endif
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*设置超像素图片的Labels
*
*@param   x_offset   围绕中心像素X的偏移量
*@param   y_offset   围绕中心像素Y的偏移量
*@param   offsetSize 偏移数组的长度
*@param   alpha      角度系数
*@param   betta      模长系数
*@param   gama       亮度系数
*@param   fai        距离系数
*@param   SeedWH     种子平方数开根号
*@param   labelsX    超像素块的宽度
*@param   labelsY    超像素块的长度
*@param   x          像素X坐标
*@param   y          像素Y坐标
*@param   m_width    图像宽度
*@param   m_height   图像高度
*@param   dev_kseeds_sita_n  图像的角度矩阵
*@param   dev_kseeds_m_n     图像的宽度矩阵
*@param   dev_kseeds_L_n     图像的亮度矩阵
*@param   dev_kseeds_X_n     图像的等价X矩阵
*@param   dev_kseeds_Y_n     图像的等价Y矩阵
*@param   dev_sita_n         图像的角度分量矩阵
*@param   dev_m_n			 图像的模长分量矩阵
*@param   dev_L_n            图像的亮度分量矩阵
*@param   dev_X_n            图像的X分量矩阵
*@param   dev_Y_n            图像的Y分量矩阵
*@param   klabels            图像的标定信息
*@param   distvec            保存距离最小值的矩阵
*
*/
/*------------------------------------------------------------------------------------------*/
__inline__ __device__  void SetPixelLables(
	const int* x_offset,
	const int* y_offset,
	const int offsetSize,
	const float alpha,
	const float betta,
	const float gama,
	const float fai,
	const int SeedWH,
	const int labelsX,
	const int labelsY,
	const int x,
	const int y,
	const int m_width,
	const int m_height,
	const double* dev_kseeds_sita_n,
	const double* dev_kseeds_m_n,
	const double* dev_kseeds_L_n,
	const double* dev_kseeds_X_n,
	const double* dev_kseeds_Y_n,
	const double* dev_sita_n,
	const double* dev_m_n,
	const double* dev_L_n,
	const double* dev_X_n,
	const double* dev_Y_n,
	int*   klabels,
	double* distvec)
{
#if 0
	{
		double dist;
		//////////////////////////////////////////////
		int i = y*m_width + x;
		////////////////////////////////////////////
		for (int xi=0;xi<offsetSize;xi++){
			for (int yi=0;yi<offsetSize;yi++){
				int nx=labelsX+x_offset[xi];
				int ny=labelsY+y_offset[yi];
				if (nx>=0&&nx<SeedWH&&ny>=0&&ny<SeedWH){
					int ni=nx+ny*SeedWH;
					{
						dist=CalculateNewDistance(alpha,betta,gama,fai,
							dev_sita_n[i],dev_m_n[i],dev_L_n[i],dev_X_n[i],dev_Y_n[i],
							dev_kseeds_sita_n[ni],dev_kseeds_m_n[ni],dev_kseeds_L_n[ni],dev_kseeds_X_n[ni],dev_kseeds_Y_n[ni]);
						if( dist < distvec[i] )
						{
							distvec[i] = dist;
							klabels[i]  = ni;
						}

					}
				}
			}
		}
	}
#endif
#if 1
	{
		double dist;
		//////////////////////////////////////////////
		int i = y*m_width + x;
		////////////////////////////////////////////
		for (int xyi=0;xyi<offsetSize;xyi++){			
				int nx=labelsX+x_offset[xyi];
				int ny=labelsY+y_offset[xyi];
				if (nx>=0&&nx<SeedWH&&ny>=0&&ny<SeedWH){
					int ni=nx+ny*SeedWH;
					{
						dist=CalculateNewDistance(alpha,betta,gama,fai,
							dev_sita_n[i],dev_m_n[i],dev_L_n[i],dev_X_n[i],dev_Y_n[i],
							dev_kseeds_sita_n[ni],dev_kseeds_m_n[ni],dev_kseeds_L_n[ni],dev_kseeds_X_n[ni],dev_kseeds_Y_n[ni]);
						if( dist < distvec[i] )
						{
							distvec[i] = dist;
							klabels[i]  = ni;
						}

					}
				}
			
		}
	}
#endif
}
/*------------------------------------------------------------------------------------------*/
/**
*
*一个像素与5个种子计算距离保留最小值
*
*@param     kseedsSize 种子个数 
*@param     alpha      角度系数
*@param     betta      模长系数
*@param     gama       亮度系数
*@param     fai        距离参数
*@param     m_width    图像宽度
*@param     m_height   图像高度
*@param   [in]  m_lvec     图像L分量
*@param   [in]  m_avec     图像A分量
*@param   [in] m_bvec     图像B分量
*@param   [in]  dev_sita_n  图像角度分量
*@param   [in] dev_m_n    图像模长分量
*@param   [in]  dev_L_n   图像亮度分量
*@param   [in] dev_X_n   图像X分量
*@param   [in]  dev_Y_n   图像Y分量
*@param   [in]  kseedsl   种子的L分量
*@param   [in] kseedsa   种子的A分量
*@param   [in] kseedsb   种子的B分量
*@param   [in] kseedsx   种子的X坐标分量
*@param   [in] kseedsy   种子的Y坐标分量
*@param   [in] dev_kseed_sita_n  种子角度分量
*@param   [in] dev_kseed_m_n     种子模长分量
*@param   [in] dev_kseed_L_n     种子的L分量
*@param   [in] dev_kseed_X_n     种子的X分量
*@param   [in] dev_kseed_Y_n     种子的Y分量
*@param   [in] klabels           图像的标定信息
*@param   [in] distvec           未使用
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMinimumOnLab_5Seeds(
	const int kseedsSize,
	float alpha,
	float betta,
	float gama,
	float fai,
	const int m_width,
	const int m_height,
	double* m_lvec,
	double* m_avec,
	double* m_bvec,
	double* dev_sita_n,
	double* dev_m_n,
	double* dev_L_n,
	double* dev_X_n,
	double* dev_Y_n,
	double* kseedsl,
	double* kseedsa,
	double* kseedsb,
	double* kseedsx,
	double* kseedsy,
	double*	dev_kseed_sita_n,
	double*	dev_kseed_m_n,
	double*	dev_kseed_L_n,
	double*	dev_kseed_X_n,
	double*	dev_kseed_Y_n,
	int*   klabels,
	double* distvec)
{
	int x_offset[]={0,1,-1,0,0};
	int y_offset[]={0,0,0,1,-1};
////////////////////////////////////////////////////////////////////////
#if 1
{
	int x =blockIdx.x*blockDim.x+threadIdx.x;
	int y =blockIdx.y*blockDim.y+threadIdx.y;
	int SeedWH=sqrt((float)kseedsSize);	
	/////////////////////////////////////////////
	int offsetSize=sizeof(x_offset)/sizeof(int);
	if (x>=0&&x<m_width&&y>=0&&y<m_height){
		int ind=x+y*m_width;
		int labels_ind=klabels[ind];
	assert(labels_ind>=-1&&labels_ind<kseedsSize);
#if 1
		if (labels_ind==-1){
			int x_step=m_width/SeedWH;
			int y_step=m_height/SeedWH;
			int labelsX=x/x_step;
			int labelsY=y/y_step;
			SetPixelLables(x_offset,y_offset,offsetSize,
				alpha,betta,gama,fai,
				SeedWH,labelsX,labelsY,x,y,m_width,m_height,
				dev_kseed_sita_n,dev_kseed_m_n,dev_kseed_L_n,dev_kseed_X_n,dev_kseed_Y_n,
				dev_sita_n,dev_m_n,dev_L_n,dev_X_n,dev_Y_n,				
				klabels,distvec);
		}else{
			int labelsX=labels_ind%SeedWH;
			int labelsY=labels_ind/SeedWH;
#if 1
			SetPixelLables(x_offset,y_offset,offsetSize,
				alpha,betta,gama,fai,
				SeedWH,labelsX,labelsY,x,y,m_width,m_height,
				dev_kseed_sita_n,dev_kseed_m_n,dev_kseed_L_n,dev_kseed_X_n,dev_kseed_Y_n,
				dev_sita_n,dev_m_n,dev_L_n,dev_X_n,dev_Y_n,
				klabels,distvec);
#endif	
		}
#endif
	}

}
#endif
////////////////////////////////////////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*一个像素与9个种子计算距离保留最小值
*
*@param     kseedsSize 种子个数 
*@param     alpha      角度系数
*@param     betta      模长系数
*@param     gama       亮度系数
*@param     fai        距离参数
*@param     m_width    图像宽度
*@param     m_height   图像高度
*@param   [in]  m_lvec     图像L分量
*@param   [in]  m_avec     图像A分量
*@param   [in] m_bvec     图像B分量
*@param   [in]  dev_sita_n  图像角度分量
*@param   [in] dev_m_n    图像模长分量
*@param   [in]  dev_L_n   图像亮度分量
*@param   [in] dev_X_n   图像X分量
*@param   [in]  dev_Y_n   图像Y分量
*@param   [in]  kseedsl   种子的L分量
*@param   [in] kseedsa   种子的A分量
*@param   [in] kseedsb   种子的B分量
*@param   [in] kseedsx   种子的X坐标分量
*@param   [in] kseedsy   种子的Y坐标分量
*@param   [in] dev_kseed_sita_n  种子角度分量
*@param   [in] dev_kseed_m_n     种子模长分量
*@param   [in] dev_kseed_L_n     种子的L分量
*@param   [in] dev_kseed_X_n     种子的X分量
*@param   [in] dev_kseed_Y_n     种子的Y分量
*@param   [in] klabels           图像的标定信息
*@param   [in] distvec           未使用
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMinimumOnLab_9Seeds(
	const int kseedsSize,
	float alpha,
	float betta,
	float gama,
	float fai,
	const int m_width,
	const int m_height,
	double* m_lvec,
	double* m_avec,
	double* m_bvec,
	double* dev_sita_n,
	double* dev_m_n,
	double* dev_L_n,
	double* dev_X_n,
	double* dev_Y_n,
	double* kseedsl,
	double* kseedsa,
	double* kseedsb,
	double* kseedsx,
	double* kseedsy,
	double*	dev_kseed_sita_n,
	double*	dev_kseed_m_n,
	double*	dev_kseed_L_n,
	double*	dev_kseed_X_n,
	double*	dev_kseed_Y_n,
	int*   klabels,
	double* distvec)
{
////////////////////////////////////////////////////////////////////////
	int x_offset[]={0,1,-1,0,0,1,-1,1,-1};
	int y_offset[]={0,0,0,1,-1,1,-1,-1,1};
#if 1
	{
		int x =blockIdx.x*blockDim.x+threadIdx.x;
		int y =blockIdx.y*blockDim.y+threadIdx.y;
		int SeedWH=sqrt((float)kseedsSize);	

		int offsetSize=sizeof(x_offset)/sizeof(int);
		if (x>=0&&x<m_width&&y>=0&&y<m_height){
			int ind=x+y*m_width;
			int labels_ind=klabels[ind];
			assert(labels_ind>=-1&&labels_ind<kseedsSize);
#if 1
			if (labels_ind==-1){
				float x_step=1.0*m_width/SeedWH;
				float y_step=1.0*m_height/SeedWH;
				int labelsX=x/x_step;
				int labelsY=y/y_step;
				SetPixelLables(x_offset,y_offset,offsetSize,
					alpha,betta,gama,fai,
					SeedWH,labelsX,labelsY,x,y,m_width,m_height,
					dev_kseed_sita_n,dev_kseed_m_n,dev_kseed_L_n,dev_kseed_X_n,dev_kseed_Y_n,
					dev_sita_n,dev_m_n,dev_L_n,dev_X_n,dev_Y_n,				
					klabels,distvec);
			}else{
				int labelsX=labels_ind%SeedWH;
				int labelsY=labels_ind/SeedWH;
#if 1
				SetPixelLables(x_offset,y_offset,offsetSize,
					alpha,betta,gama,fai,
					SeedWH,labelsX,labelsY,x,y,m_width,m_height,
					dev_kseed_sita_n,dev_kseed_m_n,dev_kseed_L_n,dev_kseed_X_n,dev_kseed_Y_n,
					dev_sita_n,dev_m_n,dev_L_n,dev_X_n,dev_Y_n,
					klabels,distvec);
#endif

			}
#endif
		}

	}
#endif
////////////////////////////////////////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*一个像素与9个种子计算距离保留最小值
*
*@param     kseedsSize 种子个数 
*@param     alpha      角度系数
*@param     betta      模长系数
*@param     gama       亮度系数
*@param     fai        距离参数
*@param     m_width    图像宽度
*@param     m_height   图像高度
*@param   [in]  m_lvec     图像L分量
*@param   [in]  m_avec     图像A分量
*@param   [in] m_bvec     图像B分量
*@param   [in]  dev_sita_n  图像角度分量
*@param   [in] dev_m_n    图像模长分量
*@param   [in]  dev_L_n   图像亮度分量
*@param   [in] dev_X_n   图像X分量
*@param   [in]  dev_Y_n   图像Y分量
*@param   [in]  kseedsl   种子的L分量
*@param   [in] kseedsa   种子的A分量
*@param   [in] kseedsb   种子的B分量
*@param   [in] kseedsx   种子的X坐标分量
*@param   [in] kseedsy   种子的Y坐标分量
*@param   [in] dev_kseed_sita_n  种子角度分量
*@param   [in] dev_kseed_m_n     种子模长分量
*@param   [in] dev_kseed_L_n     种子的L分量
*@param   [in] dev_kseed_X_n     种子的X分量
*@param   [in] dev_kseed_Y_n     种子的Y分量
*@param   [in] klabels           图像的标定信息
*@param   [in] distvec           未使用
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMinimumOnThetaMLXY_9Seeds(
	const int kseedsSize,
	float alpha,
	float betta,
	float gama,
	float fai,
	const int m_width,
	const int m_height,
	double* dev_sita_n,
	double* dev_m_n,
	double* dev_L_n,
	double* dev_X_n,
	double* dev_Y_n,
	double*	dev_kseed_sita_n,
	double*	dev_kseed_m_n,
	double*	dev_kseed_L_n,
	double*	dev_kseed_X_n,
	double*	dev_kseed_Y_n,
	int*   klabels,
	double* distvec)
{
////////////////////////////////////////////////////////////////////////
	int x_offset[]={0,1,-1,0,0,1,-1,1,-1};
	int y_offset[]={0,0,0,1,-1,1,-1,-1,1};
#if 1
	{
		int x =blockIdx.x*blockDim.x+threadIdx.x;
		int y =blockIdx.y*blockDim.y+threadIdx.y;
		int SeedWH=sqrt((float)kseedsSize);	

		int offsetSize=sizeof(x_offset)/sizeof(int);
		if (x>=0&&x<m_width&&y>=0&&y<m_height){
			int ind=x+y*m_width;
			int labels_ind=klabels[ind];
			assert(labels_ind>=-1&&labels_ind<kseedsSize);
#if 1
			if (labels_ind==-1){
				float x_step=1.0*m_width/SeedWH;
				float y_step=1.0*m_height/SeedWH;
				int labelsX=x/x_step;
				int labelsY=y/y_step;
				SetPixelLables(x_offset,y_offset,offsetSize,
					alpha,betta,gama,fai,
					SeedWH,labelsX,labelsY,x,y,m_width,m_height,
					dev_kseed_sita_n,dev_kseed_m_n,dev_kseed_L_n,dev_kseed_X_n,dev_kseed_Y_n,
					dev_sita_n,dev_m_n,dev_L_n,dev_X_n,dev_Y_n,				
					klabels,distvec);
			}else{
				int labelsX=labels_ind%SeedWH;
				int labelsY=labels_ind/SeedWH;
#if 1
				SetPixelLables(x_offset,y_offset,offsetSize,
					alpha,betta,gama,fai,
					SeedWH,labelsX,labelsY,x,y,m_width,m_height,
					dev_kseed_sita_n,dev_kseed_m_n,dev_kseed_L_n,dev_kseed_X_n,dev_kseed_Y_n,
					dev_sita_n,dev_m_n,dev_L_n,dev_X_n,dev_Y_n,
					klabels,distvec);
#endif

			}
#endif
		}

	}
#endif
////////////////////////////////////////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMinimumOnLab_AllSeeds(
	const int kseedsSize,
	float alpha,
	float betta,
	float gama,
	float fai,
	const int m_width,
	const int m_height,
	double* m_lvec,
	double* m_avec,
	double* m_bvec,
	double* dev_sita_n,
	double* dev_m_n,
	double* dev_L_n,
	double* dev_X_n,
	double* dev_Y_n,
	double* kseedsl,
	double* kseedsa,
	double* kseedsb,
	double* kseedsx,
	double* kseedsy,
	double*	dev_kseed_sita_n,
	double*	dev_kseed_m_n,
	double*	dev_kseed_L_n,
	double*	dev_kseed_X_n,
	double*	dev_kseed_Y_n,
	int*   klabels,
	double* distvec)
{
	////////////////////////////////////////////////////////////////////////
#if 0
	int x =blockIdx.x*blockDim.x+threadIdx.x;
	int y =blockIdx.y*blockDim.y+threadIdx.y;
	int ind=x+y*m_width;
	int labels_ind;
	if (x>=0&&x<m_width&&y>=0&&y<m_height){
		labels_ind= klabels[ind];	
		assert(labels_ind>=-1&&labels_ind<kseedsSize);
		{
			double l, a, b;
			double dist;
			//////////////////////////////////////////////
			int i = y*m_width + x;
			l = m_lvec[i];
			a = m_avec[i];
			b = m_bvec[i];
			double sita_n, m_n, L_n, X_n, Y_n;
			double Ksita_n, Km_n, KL_n, KX_n, KY_n;
			ConvertLab2oml(m_width,m_height,l,a,b,x,y,sita_n,m_n,L_n,X_n,Y_n);
			int kseedareaXmin=max(0,x-STEP);
			int kseedareaYmin=max(0,y-STEP);
			int kseedareaXmax=min(m_width,x+STEP);
			int kseedareaYmax=min(m_height,y+STEP);

			for(int ni=0;ni<kseedsSize;ni++){
				int n=ni;
				int KseedX=kseedsx[n];
				int KseedY=kseedsy[n];
				if ((KseedX>=kseedareaXmin)&&
					(KseedX<kseedareaXmax)&&
					(KseedY>=kseedareaYmin)&&
					(KseedY<kseedareaYmax)){
						ConvertLab2oml(m_width,m_height,kseedsl[n],kseedsa[n],kseedsb[n],kseedsx[n],kseedsy[n],Ksita_n,Km_n,KL_n,KX_n,KY_n);
						dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
						if( dist < distvec[i] )
						{
							distvec[i] = dist;
							klabels[i]  = n;
						}
				}

			}

		}

	}

#endif
	////////////////////////////////////////////////////////////////////////
#if 0
	{
		int x =blockIdx.x*blockDim.x+threadIdx.x;
		int y =blockIdx.y*blockDim.y+threadIdx.y;
		int ind=x+y*m_width;
		int labels_ind;
		if (x>=0&&x<m_width&&y>=0&&y<m_height){
			labels_ind= klabels[ind];	
			assert(labels_ind>=-1&&labels_ind<kseedsSize);
			{
				double l, a, b;
				double dist;
				double sita_n, m_n, L_n, X_n, Y_n;
				double Ksita_n, Km_n, KL_n, KX_n, KY_n;
				//////////////////////////////////////////////
				int i = y*m_width + x;
				////////////////////////////////////////////
				sita_n=dev_sita_n[i];
				m_n=dev_m_n[i];
				L_n=dev_L_n[i];
				X_n=dev_X_n[i];
				Y_n=dev_Y_n[i];
				int kseedareaXmin=max(0,x-STEP);
				int kseedareaYmin=max(0,y-STEP);
				int kseedareaXmax=min(m_width,x+STEP);
				int kseedareaYmax=min(m_height,y+STEP);

				for(int ni=0;ni<kseedsSize;ni++){
					int KseedX=kseedsx[ni];
					int KseedY=kseedsy[ni];
					if ((KseedX>=kseedareaXmin)&&
						(KseedX<kseedareaXmax)&&
						(KseedY>=kseedareaYmin)&&
						(KseedY<kseedareaYmax)){
							Ksita_n=dev_sita_n[ni];
							Km_n=dev_m_n[ni];
							KL_n=dev_L_n[ni];
							KX_n=dev_X_n[ni];
							KY_n=dev_Y_n[ni];
							dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
							if( dist < distvec[i] )
							{
								distvec[i] = dist;
								klabels[i]  = ni;
							}
					}

				}

			}

		}
	}
#endif
	////////////////////////////////////////////////////////////////////////
#if 1
	{
		int x =blockIdx.x*blockDim.x+threadIdx.x;
		int y =blockIdx.y*blockDim.y+threadIdx.y;
		int SeedWH=sqrt((float)kseedsSize);	
		int x_step=m_width/SeedWH;
		int y_step=m_height/SeedWH;
		int STEP=x_step+y_step;
		int ind=x+y*m_width;
		int labels_ind=klabels[ind];
		if (labels_ind==-1){
#if 1
			if (x>=0&&x<m_width&&y>=0&&y<m_height){
				labels_ind= klabels[ind];	
				assert(labels_ind>=-1&&labels_ind<kseedsSize);
				{
					double l, a, b;
					double dist;
					double sita_n, m_n, L_n, X_n, Y_n;
					double Ksita_n, Km_n, KL_n, KX_n, KY_n;
					//////////////////////////////////////////////
					int i = y*m_width + x;
					////////////////////////////////////////////
					sita_n=dev_sita_n[i];
					m_n=dev_m_n[i];
					L_n=dev_L_n[i];
					X_n=dev_X_n[i];
					Y_n=dev_Y_n[i];
					int kseedareaXmin=max(0,x-STEP);
					int kseedareaYmin=max(0,y-STEP);
					int kseedareaXmax=min(m_width,x+STEP);
					int kseedareaYmax=min(m_height,y+STEP);

					for(int ni=0;ni<kseedsSize;ni++){
						int KseedX=kseedsx[ni];
						int KseedY=kseedsy[ni];
						if ((KseedX>=kseedareaXmin)&&
							(KseedX<kseedareaXmax)&&
							(KseedY>=kseedareaYmin)&&
							(KseedY<kseedareaYmax)){
								Ksita_n=dev_sita_n[ni];
								Km_n=dev_m_n[ni];
								KL_n=dev_L_n[ni];
								KX_n=dev_X_n[ni];
								KY_n=dev_Y_n[ni];
								dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
								if( dist < distvec[i] )
								{
									distvec[i] = dist;
									klabels[i]  = ni;
								}
						}
					}
				}
			}
#endif
		}else{
#if 1
			{
				int SeedWH=sqrt((float)kseedsSize);
				int labelsX=labels_ind%SeedWH;
				int labelsY=labels_ind/SeedWH;
				int x_offset[]={0,1,-1,0,0};
				int y_offset[]={0,0,0,1,-1};
				int offsetSize=sizeof(x_offset)/sizeof(int);
				if (x>=0&&x<m_width&&y>=0&&y<m_height){
					assert(labels_ind>=-1&&labels_ind<kseedsSize);
					{
						double l, a, b;
						double dist;
						double sita_n, m_n, L_n, X_n, Y_n;
						double Ksita_n, Km_n, KL_n, KX_n, KY_n;
						//////////////////////////////////////////////
						int i = y*m_width + x;
						////////////////////////////////////////////
						sita_n=dev_sita_n[i];
						m_n=dev_m_n[i];
						L_n=dev_L_n[i];
						X_n=dev_X_n[i];
						Y_n=dev_Y_n[i];
						int kseedareaXmin=max(0,x-STEP);
						int kseedareaYmin=max(0,y-STEP);
						int kseedareaXmax=min(m_width,x+STEP);
						int kseedareaYmax=min(m_height,y+STEP);

						for (int xi=0;xi<offsetSize;xi++){
							for (int yi=0;yi<offsetSize;yi++)
							{
								int nx=labelsX+xi;
								int ny=labelsY+yi;
								if (nx>=0&&nx<SeedWH&&ny>=0&&ny<SeedWH){
									int ni=nx+ny*SeedWH;
									{
										int KseedX=kseedsx[ni];
										int KseedY=kseedsy[ni];
										if ((KseedX>=kseedareaXmin)&&
											(KseedX<kseedareaXmax)&&
											(KseedY>=kseedareaYmin)&&
											(KseedY<kseedareaYmax)){
												Ksita_n=dev_sita_n[ni];
												Km_n=dev_m_n[ni];
												KL_n=dev_L_n[ni];
												KX_n=dev_X_n[ni];
												KY_n=dev_Y_n[ni];
												dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
												if( dist < distvec[i] )
												{
													distvec[i] = dist;
													klabels[i]  = ni;
												}
										}
									}
								}

							}
						}
					}
				}
			}
#endif
		}
	}
#endif
	////////////////////////////////////////////////////////////////////////
#if 0
	{
		int x =blockIdx.x*blockDim.x+threadIdx.x;
		int y =blockIdx.y*blockDim.y+threadIdx.y;
		int SeedWH=sqrt((float)kseedsSize);
		int ind=x+y*m_width;
		int x_offset[]={0,1,-1,0,0};
		int y_offset[]={0,0,0,1,-1};
		int offsetSize=sizeof(x_offset)/sizeof(int);
		int labels_ind=klabels[ind];
		if (labels_ind==-1){
			int x_step=m_width/SeedWH;
			int y_step=m_height/SeedWH;
			int labelsX=x/x_step;
			int labelsY=y/y_step;
#if 1
			if (x>=0&&x<m_width&&y>=0&&y<m_height){
				assert(labels_ind>=-1&&labels_ind<kseedsSize);
				{
					double l, a, b;
					double dist;
					double sita_n, m_n, L_n, X_n, Y_n;
					double Ksita_n, Km_n, KL_n, KX_n, KY_n;
					//////////////////////////////////////////////
					int i = y*m_width + x;
					////////////////////////////////////////////
					sita_n=dev_sita_n[i];
					m_n=dev_m_n[i];
					L_n=dev_L_n[i];
					X_n=dev_X_n[i];
					Y_n=dev_Y_n[i];
					int kseedareaXmin=max(0,x-STEP);
					int kseedareaYmin=max(0,y-STEP);
					int kseedareaXmax=min(m_width,x+STEP);
					int kseedareaYmax=min(m_height,y+STEP);
					for (int xi=0;xi<offsetSize;xi++){
						for (int yi=0;yi<offsetSize;yi++)
						{
							int nx=labelsX+x_offset[xi];
							int ny=labelsY+y_offset[yi];
							if (nx>=0&&nx<SeedWH&&ny>=0&&ny<SeedWH){
								int ni=nx+ny*SeedWH;
								{
									int KseedX=kseedsx[ni];
									int KseedY=kseedsy[ni];
									if ((KseedX>=kseedareaXmin)&&
										(KseedX<kseedareaXmax)&&
										(KseedY>=kseedareaYmin)&&
										(KseedY<kseedareaYmax)){
											Ksita_n=dev_sita_n[ni];
											Km_n=dev_m_n[ni];
											KL_n=dev_L_n[ni];
											KX_n=dev_X_n[ni];
											KY_n=dev_Y_n[ni];
											dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
											if( dist < distvec[i] )
											{
												distvec[i] = dist;
												klabels[i]  = ni;
											}
									}
								}
							}
						}
					}
				}
			}
#endif
		}else{
			int labelsX=labels_ind%SeedWH;
			int labelsY=labels_ind/SeedWH;
#if 1
			if (x>=0&&x<m_width&&y>=0&&y<m_height){
				assert(labels_ind>=-1&&labels_ind<kseedsSize);
				{
					double l, a, b;
					double dist;
					double sita_n, m_n, L_n, X_n, Y_n;
					double Ksita_n, Km_n, KL_n, KX_n, KY_n;
					//////////////////////////////////////////////
					int i = y*m_width + x;
					////////////////////////////////////////////
					sita_n=dev_sita_n[i];
					m_n=dev_m_n[i];
					L_n=dev_L_n[i];
					X_n=dev_X_n[i];
					Y_n=dev_Y_n[i];
					int kseedareaXmin=max(0,x-STEP);
					int kseedareaYmin=max(0,y-STEP);
					int kseedareaXmax=min(m_width,x+STEP);
					int kseedareaYmax=min(m_height,y+STEP);
					for (int xi=0;xi<offsetSize;xi++){
						for (int yi=0;yi<offsetSize;yi++)
						{
							int nx=labelsX+x_offset[xi];
							int ny=labelsY+y_offset[yi];
							if (nx>=0&&nx<SeedWH&&ny>=0&&ny<SeedWH){
								int ni=nx+ny*SeedWH;
								{
									int KseedX=kseedsx[ni];
									int KseedY=kseedsy[ni];
									if ((KseedX>=kseedareaXmin)&&
										(KseedX<kseedareaXmax)&&
										(KseedY>=kseedareaYmin)&&
										(KseedY<kseedareaYmax)){
											Ksita_n=dev_sita_n[ni];
											Km_n=dev_m_n[ni];
											KL_n=dev_L_n[ni];
											KX_n=dev_X_n[ni];
											KY_n=dev_Y_n[ni];
											dist=CalculateNewDistance(alpha,betta,gama,fai,sita_n,m_n,L_n,X_n,Y_n,Ksita_n,Km_n,KL_n,KX_n,KY_n);
											if( dist < distvec[i] )
											{
												distvec[i] = dist;
												klabels[i]  = ni;
											}
									}
								}
							}
						}
					}
				}
			}
#endif
		}
	}
#endif
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMatrix(double *matrix,int width,int height,double value_t)
{
	int i=blockIdx.x*blockDim.x+threadIdx.x;
	int j=blockIdx.y*blockDim.y+threadIdx.y;
	int ind=i+j*width;
	if(ind<width*height){
		matrix[ind]=value_t;
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void SetMatrix_Efficient(double *matrix,int width,int height,double value_t)
{
	int ind=blockIdx.x*blockDim.x+threadIdx.x;
	int offset=blockDim.x*gridDim.x;
	int size_t=width*height;
	/////////////////////////////////////////
	while(ind<size_t){
		matrix[ind]=value_t;
		ind+=offset;
	}
	/////////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
#if !defined(__CUDA_ARCH__) || __CUDA_ARCH__ >= 600 

#else 
__device__ double atomicAdd(double* address, double val)
{
	unsigned long long int* address_as_ull =
		(unsigned long long int*)address;
	unsigned long long int old = *address_as_ull, assumed;

	do {
		assumed = old;
		old = atomicCAS(address_as_ull, assumed,
			__double_as_longlong(val +
				__longlong_as_double(assumed)));

		// Note: uses integer comparison to avoid hang in case of NaN (since NaN != NaN)
	} while (assumed != old);

	return __longlong_as_double(old);
}
//Read more at: http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#ixzz3HQ3voVZ1 
//Follow us: @GPUComputing on Twitter | NVIDIA on Facebook
#endif
/*------------------------------------------------------------------------------------------*/
/**
*              1*1            
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect_blocks(
	const int			kseedSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	int m=blockIdx.x*blockDim.x+threadIdx.x;
	int n=blockIdx.y*blockDim.y+threadIdx.y;
	///////////////////////////////////////
	int m_dim=blockDim.x*gridDim.x;
	int n_dim=blockDim.y*gridDim.y;
	int width_step=width/m_dim;
	int height_step=height/n_dim;
	/////////////////////////////////////////
	int w_start=m*width_step;
	int h_start=n*height_step;
	int w_end=min((m+1)*width_step,width);
	int h_end=min((n+1)*height_step,height);
	///////////////////////////////////////////
	int labels_ind;
	int ind;
	for (int xi=w_start;xi<w_end;xi++){
		for (int yi=h_start;yi<h_end;yi++){
			ind=xi+yi*width;
			labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
#if 1
					{
						atomicAdd(&dev_sigmal[labels_ind],m_lvec[ind]);
						atomicAdd(&dev_sigmaa[labels_ind],m_avec[ind]);
						atomicAdd(&dev_sigmab[labels_ind],m_bvec[ind]);
						atomicAdd(&dev_sigmax[labels_ind],xi);
						atomicAdd(&dev_sigmay[labels_ind],yi);
						atomicAdd(&dev_clustersize[labels_ind],1.0);
					}
#else
						{
							dev_sigmal[labels_ind]+=m_lvec[ind];
							dev_sigmaa[labels_ind]+=m_avec[ind];
							dev_sigmab[labels_ind]+=m_bvec[ind];
							dev_sigmax[labels_ind]+=xi;
							dev_sigmay[labels_ind]+=yi;
							dev_clustersize[labels_ind]+=1.0;
						}
#endif
		}
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*              1*1            
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect_blocks_sheard(
	const int			kseedSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	int m=blockIdx.x*blockDim.x+threadIdx.x;
	int n=blockIdx.y*blockDim.y+threadIdx.y;
	///////////////////////////////////////
	int m_dim=blockDim.x*gridDim.x;
	int n_dim=blockDim.y*gridDim.y;
	int width_step=width/m_dim;
	int height_step=height/n_dim;
	/////////////////////////////////////////
	int w_start=m*width_step;
	int h_start=n*height_step;
	int w_end=min((m+1)*width_step,width);
	int h_end=min((n+1)*height_step,height);
	///////////////////////////////////////////
	int labels_ind;
	int ind;
	for (int xi=w_start;xi<w_end;xi++){
		for (int yi=h_start;yi<h_end;yi++){
			ind=xi+yi*width;
			labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
#if 1
			{
				atomicAdd(&dev_sigmal[labels_ind],m_lvec[ind]);
				atomicAdd(&dev_sigmaa[labels_ind],m_avec[ind]);
				atomicAdd(&dev_sigmab[labels_ind],m_bvec[ind]);
				atomicAdd(&dev_sigmax[labels_ind],xi);
				atomicAdd(&dev_sigmay[labels_ind],yi);
				atomicAdd(&dev_clustersize[labels_ind],1.0);
			}
#else
			{
				dev_sigmal[labels_ind]+=m_lvec[ind];
				dev_sigmaa[labels_ind]+=m_avec[ind];
				dev_sigmab[labels_ind]+=m_bvec[ind];
				dev_sigmax[labels_ind]+=xi;
				dev_sigmay[labels_ind]+=yi;
				dev_clustersize[labels_ind]+=1.0;
			}
#endif
		}
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect(
	unsigned int*		mutex,
	const int			kseedSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	int c=blockIdx.x*blockDim.x+threadIdx.x;
	int r=blockIdx.y*blockDim.y+threadIdx.y;
	int ind=c+r*width;
	int labels_ind;
	if (ind>=0&&ind<width*height){
		labels_ind=dev_klabels[ind];
	}else{
		return;
	}

	assert(labels_ind>=0&&labels_ind<kseedSize);
	//	bool finished = false; 
	if (labels_ind>=0&&labels_ind<kseedSize)
	{
		if (ind<width*height){

			//	while(!finished)
			{
				//	if( atomicExch(mutex, 1) == 0)
				{
#if 1
					{
						atomicAdd(&dev_sigmal[labels_ind],m_lvec[ind]);
						atomicAdd(&dev_sigmaa[labels_ind],m_avec[ind]);
						atomicAdd(&dev_sigmab[labels_ind],m_bvec[ind]);
						atomicAdd(&dev_sigmax[labels_ind],c);
						atomicAdd(&dev_sigmay[labels_ind],r);
						atomicAdd(&dev_clustersize[labels_ind],1.0);
					}
#else
					{
						dev_sigmal[labels_ind]+=m_lvec[ind];
						dev_sigmaa[labels_ind]+=m_avec[ind];
						dev_sigmab[labels_ind]+=m_bvec[ind];
						dev_sigmax[labels_ind]+=c;
						dev_sigmay[labels_ind]+=r;
						dev_clustersize[labels_ind]+=1.0;
					}
#endif

					//	finished = true;
					//	atomicExch(mutex, 0);
				}
			}

		}
	}
	/*****************************************/
	//while(!finished)
	//{
	//		if( atomicExch(mutex, 1) == 0){
	//			
	//			
	//			finished = true;
	//			atomicExch(mutex, 0);
	//		}

	//}

	/*****************************************/

}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，默认问K^2（平方数）个数
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect_new2014_11_3(
	unsigned int*		mutex,
	const int			kseedSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	__shared__ double temp[4096];
	assert(kseedSize<=4096);
	{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
			__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
			atomicAdd(&temp[labels_ind],m_lvec[ind]);
			ind+=offset;
		}
			__syncthreads();
		atomicAdd(&dev_sigmal[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_sigmal[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_sigmal[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_sigmal[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
#if 0
{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
			__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
			atomicAdd(&temp[labels_ind],m_avec[ind]);
			ind+=offset;
		}
			__syncthreads();
		atomicAdd(&dev_sigmaa[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_sigmaa[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_sigmaa[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_sigmaa[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
	{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
			__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
				atomicAdd(&temp[labels_ind],m_bvec[ind]);
			ind+=offset;
		}
			__syncthreads();
		atomicAdd(&dev_sigmab[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_sigmab[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_sigmab[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_sigmab[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
	{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
			__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
				atomicAdd(&temp[labels_ind],int(ind%width));
			ind+=offset;
		}
			__syncthreads();
		atomicAdd(&dev_sigmax[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_sigmax[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_sigmax[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_sigmax[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
	{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
			__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
				atomicAdd(&temp[labels_ind],int(ind/width));
			ind+=offset;
		}
			__syncthreads();
		atomicAdd(&dev_sigmay[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_sigmay[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_sigmay[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_sigmay[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
	{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
			__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
				atomicAdd(&temp[labels_ind],1);
			ind+=offset;
		}
			__syncthreads();
		atomicAdd(&dev_clustersize[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_clustersize[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_clustersize[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_clustersize[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
#endif	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，默认问K^2（平方数）个数
*
*@param			kseedsSize		种子数量
*@param			width		图像宽度
*@param			height		图像高度
*@param	[in]	m_lvec		图像L分量矩阵
*@param	[in]	m_avec		图像A分量矩阵
*@param	[in]	m_bvec		图像B分量矩阵
*@param	[in]	dev_klabels		图像标定矩阵
*@param [in]	dev_img_mask		未使用
*@param	[out]	dev_sigmal		对L分量统计求和
*@param	[out]	dev_sigmaa		对A分量统计求和
*@param	[out]	dev_sigmab		对B分量统计求和
*@param	[out]	dev_sigmax		对X分量统计求和
*@param	[out]	dev_sigmay		对Y分量统计求和
*@param	[out]	dev_clustersize	 未使用 	
*
*/
/*------------------------------------------------------------------------------------------*/
 void StatisticsLABXY_Seed_collect_CPU(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	unsigned int*       dev_img_mask,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	cudaError_t cudaStatus;
	unsigned int*       host_img_mask=nullptr;
	int*				host_klabels=new int[width*height];
	double*				host_sigmal=new double[kseedsSize];
	double*				host_sigmaa=new double[kseedsSize];
	double*				host_sigmab=new double[kseedsSize];
	double*				host_sigmax=new double[kseedsSize];
	double*				host_sigmay=new double[kseedsSize];
	double*				host_clustersize=new double[kseedsSize];

#if 1
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (dev_img_mask==nullptr){
		host_img_mask=nullptr;
	}else{
		 host_img_mask=new unsigned int[width*height];
		 cudaStatus = cudaMemcpy( host_img_mask,dev_img_mask, width*height * sizeof(unsigned int), cudaMemcpyDeviceToHost);
	}
	 cudaStatus = cudaMemcpy(host_klabels,dev_klabels, width*height * sizeof(int), cudaMemcpyDeviceToHost);
	memset(host_sigmal,0,kseedsSize * sizeof(double));
	memset(host_sigmaa,0,kseedsSize * sizeof(double));
	memset(host_sigmab,0,kseedsSize * sizeof(double));
	memset(host_sigmax,0,kseedsSize * sizeof(double));
	memset(host_sigmay,0,kseedsSize * sizeof(double));	
	memset(host_clustersize,0,kseedsSize*sizeof(double));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
	{
		int ind(0);
		for(register int r = 0; r < height; r++ )
		{
			for(register  int c = 0; c < width; c++ )
			{
				if (host_img_mask==nullptr){
					host_sigmal[host_klabels[ind]] += m_lvec[ind];
					host_sigmaa[host_klabels[ind]] += m_avec[ind];
					host_sigmab[host_klabels[ind]] += m_bvec[ind];
					host_sigmax[host_klabels[ind]] += c;
					host_sigmay[host_klabels[ind]] += r;
					host_clustersize[host_klabels[ind]] += 1.0;
				}
				if (host_img_mask!=nullptr&&host_img_mask[ind]==0x000000000){
					host_sigmal[host_klabels[ind]] += m_lvec[ind];
					host_sigmaa[host_klabels[ind]] += m_avec[ind];
					host_sigmab[host_klabels[ind]] += m_bvec[ind];
					host_sigmax[host_klabels[ind]] += c;
					host_sigmay[host_klabels[ind]] += r;
					host_clustersize[host_klabels[ind]] += 1.0;
				}				
				//------------------------------------
				//edgesum[klabels[ind]] += edgemag[ind];
				//------------------------------------
				
				ind++;
			}
		}
#if 0
				double x_max=0;
				double y_max=0;
				double *inv=new double[kseedsSize];
				{
					for( int k = 0; k < kseedsSize; k++ )
					{
						if(host_clustersize[k] <= 0 ) host_clustersize[k] = 1;
						inv[k] = 1.0/host_clustersize[k];//computing inverse now to multiply, than divide later
						////////////////////////////////////
						host_sigmal[k] = host_sigmal[k]*inv[k];
						host_sigmaa[k] = host_sigmaa[k]*inv[k];
						host_sigmab[k] = host_sigmab[k]*inv[k];
						host_sigmax[k] = host_sigmax[k]*inv[k];
						host_sigmay[k] = host_sigmay[k]*inv[k];
						if (host_sigmax[k]>x_max){
							x_max=host_sigmax[k];
						}
						if (host_sigmay[k]>y_max){
							y_max=host_sigmay[k];
						}
						//------------------------------------
						//edgesum[k] *= inv[k];
						//------------------------------------
					}
				}
				delete []inv;
#endif
	}
#if 1
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (dev_img_mask==nullptr){
		host_img_mask=nullptr;
	}else{
		cudaStatus = cudaMemcpy( dev_img_mask,host_img_mask, width*height * sizeof(int), cudaMemcpyHostToDevice);
	}
	
	
	cudaStatus = cudaMemcpy(dev_sigmal, host_sigmal, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
	
	cudaStatus = cudaMemcpy(dev_sigmaa, host_sigmaa, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
	
	cudaStatus = cudaMemcpy(dev_sigmab, host_sigmab, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
	
	cudaStatus = cudaMemcpy(dev_sigmax, host_sigmax, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
	
	cudaStatus = cudaMemcpy(dev_sigmay, host_sigmay, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
	
	cudaStatus = cudaMemcpy(dev_clustersize, host_clustersize, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
	delete [] host_img_mask;
	delete [] host_klabels;
	delete [] host_sigmal;
	delete [] host_sigmaa;
	delete [] host_sigmab;
	delete [] host_sigmax;
	delete [] host_sigmay;
	delete [] host_clustersize;
 ;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，默认问K^2（平方数）个数
*
*@param			kseedsSize		种子数量
*@param			width		图像宽度
*@param			height		图像高度
*@param	[in]	m_lvec		图像L分量矩阵
*@param	[in]	m_avec		图像A分量矩阵
*@param	[in]	m_bvec		图像B分量矩阵
*@param	[in]	dev_klabels		图像标定矩阵
*@param [in]	dev_img_mask		未使用
*@param	[out]	dev_sigmal		对L分量统计求和
*@param	[out]	dev_sigmaa		对A分量统计求和
*@param	[out]	dev_sigmab		对B分量统计求和
*@param	[out]	dev_sigmax		对X分量统计求和
*@param	[out]	dev_sigmay		对Y分量统计求和
*@param	[out]	dev_clustersize	 未使用 	
*
*/
/*------------------------------------------------------------------------------------------*/
 void StatisticsThetaMLXY_Seed_collect_CPU(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*       host_sita_n,
	double*       host_m_n,
	double*       host_L_n,
	double*       host_X_n,
	double*       host_Y_n,	
	int*				dev_klabels,
    double*	      dev_kseed_sita_n,
	double*	      dev_kseed_m_n,
	double*	      dev_kseed_L_n,
	double*       dev_kseed_X_n,
	double*	      dev_kseed_Y_n)
{
	cudaError_t cudaStatus;
	double*	      host_kseed_sita_n=new double[kseedsSize];
	double*	      host_kseed_m_n=new double[kseedsSize];
	double*	      host_kseed_L_n=new double[kseedsSize];
	double*       host_kseed_X_n=new double[kseedsSize];
	double*	      host_kseed_Y_n=new double[kseedsSize];
	int*	      host_klabels=new int[width*height];
	unsigned int*       dev_img_mask;
	unsigned int*       host_img_mask=new unsigned[width*height];
 
   cudaStatus=cudaMalloc((void**)&dev_img_mask,sizeof(unsigned int)*width*height);  
   InitMaskTemplate(dev_img_mask,dev_klabels,width,height,4);

   cudaStatus = cudaMemcpy(host_kseed_sita_n, dev_kseed_sita_n, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
   cudaStatus = cudaMemcpy(host_kseed_m_n, dev_kseed_m_n, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
   cudaStatus = cudaMemcpy(host_kseed_L_n, dev_kseed_L_n, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
   cudaStatus = cudaMemcpy(host_kseed_X_n, dev_kseed_X_n, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
   cudaStatus = cudaMemcpy(host_kseed_Y_n, dev_kseed_Y_n, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
   cudaStatus = cudaMemcpy(host_klabels, dev_klabels, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
   cudaStatus = cudaMemcpy(host_img_mask,dev_img_mask, kseedsSize * sizeof(double), cudaMemcpyDeviceToHost);
  
	StatisticsThetaMLXY_Seed_collect_CPU_ALL(
					kseedsSize,
					width,
					height,
					host_sita_n,
					host_m_n,
					host_L_n,
					host_X_n,
					host_Y_n,	
					host_klabels,
					host_img_mask,
					host_kseed_sita_n,
					host_kseed_m_n,
					host_kseed_L_n,
					host_kseed_X_n,
					host_kseed_Y_n);

    delete[]	  host_kseed_sita_n;
	delete[]      host_kseed_m_n;
	delete[]      host_kseed_L_n;
	delete[]      host_kseed_X_n;
	delete[]      host_kseed_Y_n;
	delete[]      host_klabels;
	cudaFree(dev_img_mask);
	delete[]      host_img_mask;

}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，默认问K^2（平方数）个数
*
*@param			kseedsSize		种子数量
*@param			width		图像宽度
*@param			height		图像高度
*@param	[in]	m_lvec		图像L分量矩阵
*@param	[in]	m_avec		图像A分量矩阵
*@param	[in]	m_bvec		图像B分量矩阵
*@param	[in]	dev_klabels		图像标定矩阵
*@param [in]	dev_img_mask		未使用
*@param	[out]	dev_sigmal		对L分量统计求和
*@param	[out]	dev_sigmaa		对A分量统计求和
*@param	[out]	dev_sigmab		对B分量统计求和
*@param	[out]	dev_sigmax		对X分量统计求和
*@param	[out]	dev_sigmay		对Y分量统计求和
*@param	[out]	dev_clustersize	 未使用 	
*
*/
/*------------------------------------------------------------------------------------------*/
void StatisticsThetaMLXY_Seed_collect_CPU_ALL(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*       host_sita_n,
	double*       host_m_n,
	double*       host_L_n,
	double*       host_X_n,
	double*       host_Y_n,	
	int*				host_klabels,
	unsigned int*       host_img_mask,
    double*	      host_kseed_sita_n,
	double*	      host_kseed_m_n,
	double*	      host_kseed_L_n,
	double*       host_kseed_X_n,
	double*	      host_kseed_Y_n)
{
      double*			  host_sigmaSita=new double[kseedsSize];
	  double*			  host_sigmaM=new double[kseedsSize];
	  double*			  host_sigmaL=new double[kseedsSize];
	  double*			  host_sigmaX=new double[kseedsSize];
	  double*		      host_sigmaY=new double[kseedsSize];
	  double*			  host_clustersize=new double[kseedsSize];
	memset(host_sigmaSita,0,kseedsSize * sizeof(double));
	memset(host_sigmaM,0,kseedsSize * sizeof(double));
	memset(host_sigmaL,0,kseedsSize * sizeof(double));
	memset(host_sigmaX,0,kseedsSize * sizeof(double));
	memset(host_sigmaY,0,kseedsSize * sizeof(double));	
	memset(host_clustersize,0,kseedsSize*sizeof(double));
	{
		int ind(0);
		for(register int r = 0; r < height; r++ )
		{
			for(register  int c = 0; c < width; c++ )
			{
				if (host_img_mask==nullptr){
					host_sigmaSita[host_klabels[ind]] +=host_sita_n[ind];
					host_sigmaM[host_klabels[ind]] += host_m_n[ind];
					host_sigmaL[host_klabels[ind]] += host_L_n[ind];
					host_sigmaX[host_klabels[ind]] += host_X_n[ind];
					host_sigmaY[host_klabels[ind]] += host_Y_n[ind];
					host_clustersize[host_klabels[ind]] += 1.0;
				}
				if (host_img_mask!=nullptr&&host_img_mask[ind]==0x000000000){
					host_sigmaSita[host_klabels[ind]] +=host_sita_n[ind];
					host_sigmaM[host_klabels[ind]] += host_m_n[ind];
					host_sigmaL[host_klabels[ind]] += host_L_n[ind];
					host_sigmaX[host_klabels[ind]] += host_X_n[ind];
					host_sigmaY[host_klabels[ind]] += host_Y_n[ind];
					host_clustersize[host_klabels[ind]] += 1.0;
				}				
				//------------------------------------
				//edgesum[klabels[ind]] += edgemag[ind];
				//------------------------------------
				
				ind++;
			}
		}
		///////////////////////////////////////////////
		for(int spi=0;spi<kseedsSize;spi++){
			   host_kseed_sita_n[spi]=host_sigmaSita[spi]/host_clustersize[spi];
	           host_kseed_m_n[spi]=host_sigmaM[spi]/host_clustersize[spi];
	           host_kseed_L_n[spi]=host_sigmaL[spi]/host_clustersize[spi];
	           host_kseed_X_n[spi]=host_sigmaX[spi]/host_clustersize[spi];
	           host_kseed_Y_n[spi]=host_sigmaY[spi]/host_clustersize[spi];
		}
	}
	delete []  host_sigmaSita;
	delete []  host_sigmaM;
	delete []  host_sigmaL;
	delete []  host_sigmaX;
	delete []  host_sigmaY;
	delete []  host_clustersize;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，默认问K^2（平方数）个数
*
*@param			kseedsSize		种子数量
*@param			width		图像宽度
*@param			height		图像高度
*@param	[in]	m_lvec		图像L分量矩阵
*@param	[in]	m_avec		图像A分量矩阵
*@param	[in]	m_bvec		图像B分量矩阵
*@param	[in]	dev_klabels		图像标定矩阵
*@param [in]	dev_img_mask		未使用
*@param	[out]	dev_sigmal		对L分量统计求和
*@param	[out]	dev_sigmaa		对A分量统计求和
*@param	[out]	dev_sigmab		对B分量统计求和
*@param	[out]	dev_sigmax		对X分量统计求和
*@param	[out]	dev_sigmay		对Y分量统计求和
*@param	[out]	dev_clustersize	 未使用 	
*
*/
/*------------------------------------------------------------------------------------------*/
void StatisticsThetaMLXY_Seed_collect_CPU_Incompletion(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	unsigned int*       dev_img_mask,
	double*	           dev_kseed_sita_n,
	double*	           dev_kseed_m_n,
	double*	           dev_kseed_L_n,
	double*            dev_kseed_X_n,
	double*	           dev_kseed_Y_n)
{
	
	cudaError_t cudaStatus;
	unsigned int*       host_img_mask=nullptr;
	int*				host_klabels=new int[width*height];
	double*				host_sigmal=new double[kseedsSize];
	double*				host_sigmaa=new double[kseedsSize];
	double*				host_sigmab=new double[kseedsSize];
	double*				host_sigmax=new double[kseedsSize];
	double*				host_sigmay=new double[kseedsSize];
	double*				host_clustersize=new double[kseedsSize];

#if 1
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (dev_img_mask==nullptr){
		host_img_mask=nullptr;
	}else{
		 host_img_mask=new unsigned int[width*height];
		 cudaStatus = cudaMemcpy( host_img_mask,dev_img_mask, width*height * sizeof(unsigned int), cudaMemcpyDeviceToHost);
	}
	 cudaStatus = cudaMemcpy(host_klabels,dev_klabels, width*height * sizeof(int), cudaMemcpyDeviceToHost);
	memset(host_sigmal,0,kseedsSize * sizeof(double));
	memset(host_sigmaa,0,kseedsSize * sizeof(double));
	memset(host_sigmab,0,kseedsSize * sizeof(double));
	memset(host_sigmax,0,kseedsSize * sizeof(double));
	memset(host_sigmay,0,kseedsSize * sizeof(double));	
	memset(host_clustersize,0,kseedsSize*sizeof(double));
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
	{
		int ind(0);
		for(register int r = 0; r < height; r++ )
		{
			for(register  int c = 0; c < width; c++ )
			{
				if (host_img_mask==nullptr){
					host_sigmal[host_klabels[ind]] += m_lvec[ind];
					host_sigmaa[host_klabels[ind]] += m_avec[ind];
					host_sigmab[host_klabels[ind]] += m_bvec[ind];
					host_sigmax[host_klabels[ind]] += c;
					host_sigmay[host_klabels[ind]] += r;
					host_clustersize[host_klabels[ind]] += 1.0;
				}
				if (host_img_mask!=nullptr&&host_img_mask[ind]==0x000000000){
					host_sigmal[host_klabels[ind]] += m_lvec[ind];
					host_sigmaa[host_klabels[ind]] += m_avec[ind];
					host_sigmab[host_klabels[ind]] += m_bvec[ind];
					host_sigmax[host_klabels[ind]] += c;
					host_sigmay[host_klabels[ind]] += r;
					host_clustersize[host_klabels[ind]] += 1.0;
				}				
				//------------------------------------
				//edgesum[klabels[ind]] += edgemag[ind];
				//------------------------------------
				
				ind++;
			}
		}
#if 1
				
				double *inv=new double[kseedsSize];
				{
					for( int k = 0; k < kseedsSize; k++ )
					{
						if(host_clustersize[k] <= 0 ) host_clustersize[k] = 1;
						inv[k] = 1.0/host_clustersize[k];//computing inverse now to multiply, than divide later
						////////////////////////////////////
						host_sigmal[k] = host_sigmal[k]*inv[k];
						host_sigmaa[k] = host_sigmaa[k]*inv[k];
						host_sigmab[k] = host_sigmab[k]*inv[k];
						host_sigmax[k] = host_sigmax[k]*inv[k];
						host_sigmay[k] = host_sigmay[k]*inv[k];
						//------------------------------------
						//edgesum[k] *= inv[k];
						//------------------------------------
							ConvertLab2oml(
							width,
							height,
							host_sigmal[k],
							host_sigmaa[k],
							host_sigmab[k],
							host_sigmax[k],
							host_sigmay[k],
							&host_sigmal[k],
							&host_sigmaa[k],
							&host_sigmab[k],
							&host_sigmax[k],
							&host_sigmay[k]);
					}
				}
				delete []inv;
#endif
	}
#if 1
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (dev_img_mask==nullptr){
		host_img_mask=nullptr;
	}else{
		cudaStatus = cudaMemcpy( dev_img_mask,host_img_mask, width*height * sizeof(int), cudaMemcpyHostToDevice);
	}
	
	cudaStatus = cudaMemcpy(dev_kseed_sita_n, host_sigmal, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);	
	cudaStatus = cudaMemcpy(dev_kseed_m_n, host_sigmaa, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);	
	cudaStatus = cudaMemcpy( dev_kseed_L_n, host_sigmab, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);	
	cudaStatus = cudaMemcpy(dev_kseed_X_n, host_sigmax, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);	
	cudaStatus = cudaMemcpy(dev_kseed_Y_n, host_sigmay, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
	delete [] host_img_mask;
	delete [] host_klabels;
	delete [] host_sigmal;
	delete [] host_sigmaa;
	delete [] host_sigmab;
	delete [] host_sigmax;
	delete [] host_sigmay;
	delete [] host_clustersize;
 ;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect_L(
	const int			kseedSize,
	const int			width,
	const int			height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	__shared__ double temp[4096];
	assert(kseedSize<=4096);
	{
		int ind=threadIdx.x+blockIdx.x*blockDim.x;
		int offset=blockDim.x*gridDim.x;
		temp[threadIdx.x]=temp[threadIdx.x+1024]=temp[threadIdx.x+2048]=temp[threadIdx.x+3072]=0;
		__syncthreads();
		while(ind<width*height){
			int labels_ind=dev_klabels[ind];
			assert(labels_ind>=0&&labels_ind<kseedSize);
			atomicAdd(&temp[labels_ind],m_lvec[ind]);
			ind+=offset;
		}
		__syncthreads();
		atomicAdd(&dev_sigmal[threadIdx.x],temp[threadIdx.x]);
		atomicAdd(&dev_sigmal[threadIdx.x+1024],temp[threadIdx.x+1024]);
		atomicAdd(&dev_sigmal[threadIdx.x+2048],temp[threadIdx.x+2048]);
		atomicAdd(&dev_sigmal[threadIdx.x+3072],temp[threadIdx.x+3072]);
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，默认问K^2（平方数）个数
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect_gpu_search(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*				kseedsx,
	double*				kseedsy,
	double*				dev_m_lvec,
	double*				dev_m_avec,
	double*				dev_m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	int SeedIdx=threadIdx.x+blockIdx.x*blockDim.x;
	int offset=blockDim.x*gridDim.x;

	while(SeedIdx<kseedsSize){
		////////////////////////////////////////
		int kseedWH=sqrt((float)kseedsSize);
		int x_step=width/(kseedWH);
		int y_step=height/(kseedWH);
		/////////////////////////////////////////
		int x_min=max((int)(kseedsx[SeedIdx]-x_step),(int)0);
		int x_max=min((int)(kseedsx[SeedIdx]+x_step),(int)width);
		int y_min=max((int)(kseedsy[SeedIdx]-y_step),(int)0);
		int y_max=min((int)(kseedsy[SeedIdx]+y_step),(int)height);
		/////////////////////////////////////////

		for (register int xi=x_min;xi<x_max;xi++){
			for (register int yi=y_min;yi<y_max;yi++){
				int ImgIdx=xi+yi*width;
				int labels_t=dev_klabels[ImgIdx];
#if 1
				if (labels_t==SeedIdx){
					dev_sigmal[SeedIdx] += dev_m_lvec[ImgIdx];
					dev_sigmaa[SeedIdx] += dev_m_avec[ImgIdx];
					dev_sigmab[SeedIdx] += dev_m_bvec[ImgIdx];
					dev_sigmax[SeedIdx] += xi;
					dev_sigmay[SeedIdx] += yi;
					dev_clustersize[SeedIdx] += 1.0;
				}
#endif
			}
		}

		
		/////////////////////////////////////////
			SeedIdx+=offset;
	}
	
	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*收集全图的种子，从零开始全图搜索
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_collect_gpu_search_AllImg(
	const int			kseedsSize,
	const int			width,
	const int			height,
	double*				dev_m_lvec,
	double*				dev_m_avec,
	double*				dev_m_bvec,
	int*				dev_klabels,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize)
{
	int SeedIdx=threadIdx.x+blockIdx.x*blockDim.x;
	int offset=blockDim.x*gridDim.x;
	while(SeedIdx<kseedsSize){
		/*--------------------------------------*/
		int kseedWH=sqrt((float)kseedsSize);
		int x_step=width/(kseedWH);
		int y_step=height/(kseedWH);
		/*--------------------------------------*/
		int x_min=0;
		int x_max=width;
		int y_min=0;
		int y_max=height;
		/*--------------------------------------*/
		for (register int xi=x_min;xi<x_max;xi++){
			for (register int yi=y_min;yi<y_max;yi++){
				int ImgIdx=xi+yi*width;
				int labels_t=dev_klabels[ImgIdx];
#if 1
				if (labels_t==SeedIdx){
					dev_sigmal[SeedIdx] += dev_m_lvec[ImgIdx];
					dev_sigmaa[SeedIdx] += dev_m_avec[ImgIdx];
					dev_sigmab[SeedIdx] += dev_m_bvec[ImgIdx];
					dev_sigmax[SeedIdx] += xi;
					dev_sigmay[SeedIdx] += yi;
					dev_clustersize[SeedIdx] += 1.0;
				}
#endif
			}
		}
		/*--------------------------------------*/
		SeedIdx+=offset;
	}
}
/*------------------------------------------------------------------------------------------*/
/**
*计算新的图块的中心   
*
*
*@param		    	   kseedSize			种子数量	
*@param				    m_width				图像宽度	
*@param				    m_height			图像高度	
*@param		[in]		dev_sigmal			对L分量统计求和
*@param		[in]		dev_sigmaa			图像A分量矩阵
*@param		[in]		dev_sigmab			图像B分量矩阵
*@param		[in]		dev_sigmax			对X分量统计求和
*@param		[in]		dev_sigmay			对Y分量统计求和
*@param		[in]		dev_clustersize		超像素图块的面积大小
*@param		[out]		dev_kseedsl		    种子L分量
*@param		[out]		dev_kseedsa		    图像A分量
*@param		[out]		dev_kseedsb		    图像B分量
*@param		[out]		dev_kseedsx		    种子X分量
*@param		[out]		dev_kseedsy		    种子Y分量
*@param		[out]		dev_kseed_sita_n	图像的角度分量
*@param		[out]		dev_kseed_m_n	    图像的模长分量
*@param		[out]		dev_kseed_L_n	    图像的亮度分量
*@param		[out]		dev_kseed_X_n       图像的X坐标分量
*@param		[out]		dev_kseed_Y_n	    图像的Y坐标分量
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void StatisticsLABXY_Seed_calculate(
	const int			kseedSize,
	const int			m_width,
	const int			m_height,
	double*				dev_sigmal,
	double*				dev_sigmaa,
	double*				dev_sigmab,
	double*				dev_sigmax,
	double*				dev_sigmay,
	double*				dev_clustersize,
	double*				dev_kseedsl,
	double*				dev_kseedsa,
	double*				dev_kseedsb,
	double*				dev_kseedsx,
	double*				dev_kseedsy,
	double*				dev_kseed_sita_n,
	double*				dev_kseed_m_n,
	double*				dev_kseed_L_n,
	double*				dev_kseed_X_n,
	double*				dev_kseed_Y_n)
{
	int ki=blockIdx.x*blockDim.x+threadIdx.x;
	int offset=blockDim.x*gridDim.x;
	while(ki<kseedSize){

		{
				if (dev_clustersize[ki]<=0)  dev_clustersize[ki]=1;
				double inv_k=1.0/dev_clustersize[ki];
				/////////////////////////////////////////////////
				assert(dev_clustersize[ki]>=0&&dev_clustersize[ki]<=m_width*m_height);
				///////////////////////////////////////////////////
				dev_kseedsl[ki] = dev_sigmal[ki]*inv_k;
				dev_kseedsa[ki] = dev_sigmaa[ki]*inv_k;
				dev_kseedsb[ki] = dev_sigmab[ki]*inv_k;
				dev_kseedsx[ki] = dev_sigmax[ki]*inv_k;
				dev_kseedsy[ki] = dev_sigmay[ki]*inv_k;
				///////////////////////////////////////////////////
#if 1
					ConvertLab2oml(
					m_width,
					m_height,
					dev_kseedsl[ki],
					dev_kseedsa[ki],
					dev_kseedsb[ki],
					dev_kseedsx[ki],
					dev_kseedsy[ki],
					&dev_kseed_sita_n[ki],
					&dev_kseed_m_n[ki],
					&dev_kseed_L_n[ki],
					&dev_kseed_X_n[ki],
					&dev_kseed_Y_n[ki]);
#endif
				
		}
		ki+=offset;

	}
	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*@param			kseedsSize    种子个数
*@param			m_width       图像宽度
*@param			m_height      图像高度
*@param			dev_kseedsl   图像的L分量
*@param			dev_kseedsa   图像的A分量
*@param			dev_kseedsb   图像的B分量
*@param			dev_kseedsx   图像的X坐标分量
*@param			dev_kseedsy   图像的X坐标分量
*@param			dev_kseeds_sita_n  图像的角度分量
*@param			dev_kseeds_m_n     图像的模长分量
*@param			dev_kseeds_L_n     图像的亮度分量
*@param			dev_kseeds_X_n     图像的X坐标分量
*@param			dev_kseeds_Y_n     图像的Y坐标分量
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void PerformSuperpixelSLIC_Init_ColorConvert(
	const int			kseedsSize,
	const int			m_width,
	const int			m_height,
	double*				dev_kseedsl,
	double*				dev_kseedsa,
	double*				dev_kseedsb,
	double*				dev_kseedsx,
	double*				dev_kseedsy,
	double*				dev_kseeds_sita_n,
	double*				dev_kseeds_m_n,
	double*				dev_kseeds_L_n,
	double*				dev_kseeds_X_n,
	double*				dev_kseeds_Y_n)
{
	///////////////////////////////////////////
	int ind=blockIdx.x*blockDim.x+threadIdx.x;
	int step=blockDim.x*gridDim.x;
	//////////////////////////////////////////
	while(ind<kseedsSize){
			/////////////////////////////////////
#if 1
			ConvertLab2oml(
				m_width,
				m_height,
				dev_kseedsl[ind],
				dev_kseedsa[ind],
				dev_kseedsb[ind],
				dev_kseedsx[ind],
				dev_kseedsy[ind],
				&dev_kseeds_sita_n[ind],
				&dev_kseeds_m_n[ind],
				&dev_kseeds_L_n[ind],
				&dev_kseeds_X_n[ind],
				&dev_kseeds_Y_n[ind]);
#endif
			ind+=step;
	}
	///////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*将LAB色彩装换到角度、模长、亮度 、X、Y组成的分量
*
*@param   kseedsSize  种子个数
*@param   m_width     图像宽度
*@param   m_height    图像高度
*@param  [in]  dev_m_lvec  图像的L分量
*@param  [in] dev_m_avec  图像的A分量
*@param  [in] dev_m_bvec  图像的B分量
*@param  [out] dev_sita_n  图像的角度分量
*@param  [out] dev_m_n	  图像的模长分量
*@param  [out] dev_L_n     图像的亮度分量
*@param  [out] dev_X_n     图像的X坐标分量
*@param  [out] dev_Y_n     图像的Y坐标分量
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void PerformSuperpixelSLIC_ColorConvert(
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				dev_m_lvec,
	double*				dev_m_avec,
	double*				dev_m_bvec,
	double*				dev_sita_n,
	double*				dev_m_n,
	double*				dev_L_n,
	double*				dev_X_n,
	double*				dev_Y_n)
{
	///////////////////////////////////////////
	int xi=blockIdx.x*blockDim.x+threadIdx.x;
	int yj=blockIdx.y*blockDim.y+threadIdx.y;
	int ind=xi+yj*m_width;
	//////////////////////////////////////////
	if(xi<m_width&&
		xi>=0&&
		yj>=0&&
		yj<m_height){
		/////////////////////////////////////
#if 1
			ConvertLab2oml(
				m_width,
				m_height,
				dev_m_lvec[ind],
				dev_m_avec[ind],
				dev_m_bvec[ind],
				xi,
				yj,
				&dev_sita_n[ind],
				&dev_m_n[ind],
				&dev_L_n[ind],
				&dev_X_n[ind],
				&dev_Y_n[ind]);
#endif

		///////////////////////////////////
	}
	///////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*将LAB色彩装换到角度、模长、亮度 、X、Y组成的分量
*
*@param   kseedsSize  种子个数
*@param   m_width     图像宽度
*@param   m_height    图像高度
*@param  [in]  dev_m_lvec  图像的L分量
*@param  [in] dev_m_avec  图像的A分量
*@param  [in] dev_m_bvec  图像的B分量
*@param  [out] dev_sita_n  图像的角度分量
*@param  [out] dev_m_n	  图像的模长分量
*@param  [out] dev_L_n     图像的亮度分量
*@param  [out] dev_X_n     图像的X坐标分量
*@param  [out] dev_Y_n     图像的Y坐标分量
*
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_ColorConvert_gpu(
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				dev_m_lvec,
	double*				dev_m_avec,
	double*				dev_m_bvec,
	double*				dev_sita_n,
	double*				dev_m_n,
	double*				dev_L_n,
	double*				dev_X_n,
	double*				dev_Y_n)
{
#if  _DEBUG
	cudaEvent_t start,stop;
	cudaError_t cudaStatus;
	float costtime_ms=0;
	float costtime_us=0;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	///////////////////////////////////////////////////////////////////////////////////////
	cudaEventRecord(start,0);
#endif
	{
		dim3    threadsPerBlock(16,16);
		dim3    numBlock((m_width+threadsPerBlock.x-1)/threadsPerBlock.x,(m_height+threadsPerBlock.y-1)/threadsPerBlock.y);
		PerformSuperpixelSLIC_ColorConvert<<<numBlock,threadsPerBlock>>>(
			kseedsSize,
			m_width,
			m_height,
			dev_m_lvec,
			dev_m_avec,
			dev_m_bvec,
			dev_sita_n,
			dev_m_n,
			dev_L_n,
			dev_X_n,
			dev_Y_n);
	}
	////////////////////////////////////////////////////////////////////////////////////////
	cudaGetLastError_Sync_CUI();
#if _DEBUG
	cudaStatus=cudaEventRecord(stop,0);	
	cudaGetLastError_Sync_CUI();
	cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
	costtime_us=costtime_ms*1000;
#endif
	cudaGetLastError_Sync_CUI();
#if _DEBUG
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
#endif

}
/*------------------------------------------------------------------------------------------*/
/**
*利用GPU实现超像素算法
*
*@param			alpha			角度系数
*@param			betta			模长系数
*@param			gama			亮度系数
*@param			fai				距离参数
*@param			kseedsSize		种子个数 
*@param			m_width			图像宽度
*@param			m_height		图像高度
*@param		[]	host_m_lvec		图像L分量
*@param		[]	host_m_avec		图像A分量
*@param		[]	host_m_bvec		图像B分量
*@param		[]	host_kseedsl	种子的L分量
*@param		[]	host_kseedsa	种子的A分量
*@param		[]	host_kseedsb	种子的B分量
*@param		[]	host_kseedsx	种子的X坐标分量
*@param		[]	host_kseedsy	种子的Y坐标分量
*@param		[]	host_klabels	图像的标定信息
*@param			STEP
*@param		[]	host_edgemag
*@param  		M
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_gpu(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				host_m_lvec,
	double*				host_m_avec,
	double*				host_m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels,
	const int			STEP,
	double*				host_edgemag,
	const double		M)
{
	cudaError_t cudaStatus;
	///////////////////////////////////////////
	double*				dev_kseedsl;
	double*				dev_kseedsa;
	double*				dev_kseedsb;
	double*				dev_kseedsx;
	double*				dev_kseedsy;
	int*				dev_klabels;
	double*				dev_m_lvec;
	double*				dev_m_avec;
	double*				dev_m_bvec;
	double*				dev_sita_n;
	double*				dev_m_n;
	double*				dev_L_n;
	double*				dev_X_n;
	double*				dev_Y_n;
	double*				dev_edgemag=nullptr;
	///////////////////////////////////////////
	double* dev_distvec;
	///////////////////////////////////////////
	assert(cudaInit_CUI()==true);

	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop,0);
	int blocks=prop.multiProcessorCount;

	{
		cudaStatus = cudaMalloc((void**)&dev_kseedsl, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsb, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsx, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsy, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_klabels,m_width*m_height * sizeof(int));
		cudaStatus = cudaMalloc((void**)&dev_m_lvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_avec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_bvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_distvec, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_sita_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_L_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_X_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_Y_n, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMemcpy(dev_kseedsl, host_kseedsl, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsa, host_kseedsa, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsb, host_kseedsb, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsx, host_kseedsx, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsy, host_kseedsy, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_klabels, host_klabels, m_width*m_height * sizeof(int), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_lvec, host_m_lvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_avec, host_m_avec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_bvec, host_m_bvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		////////////////////////////////////////////////////////////////////////////////
	}
	double* dev_sigmal;
	double* dev_sigmaa;
	double* dev_sigmab;
	double* dev_sigmax;
	double* dev_sigmay;
	double* dev_clustersize;
	/////////////////////////////////////////////////////////////////////////////////////
	double*  dev_kseed_sita_n;
	double*  dev_kseed_m_n;
	double*  dev_kseed_L_n;
	double*  dev_kseed_X_n;
	double*  dev_kseed_Y_n;
	/////////////////////////////////////////////////////////////////////////////////////
	{
		cudaStatus = cudaMalloc((void**)&dev_sigmal, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmaa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmab, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmax, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmay, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_clustersize, kseedsSize * sizeof(double));
		cudaStatus = cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));
		cudaGetLastError_Sync_CUI();
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_kseed_sita_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_m_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_L_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_X_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_Y_n, kseedsSize * sizeof(double));
	}
	cudaEvent_t start,stop;
	float costtime_ms=0;
	float costtime_us=0;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
#if 1
	///////////////////////////////////////////
	PerformSuperpixelSLIC_ColorConvert_gpu(
		kseedsSize,
		m_width,
		m_height,
		dev_m_lvec,
		dev_m_avec,
		dev_m_bvec,
		dev_sita_n,
		dev_m_n,
		dev_L_n,
		dev_X_n,
		dev_Y_n);
	//////////////////////////////////////////
	PerformSuperpixelSLIC_Init_ColorConvert<<<1,256>>>(
		kseedsSize,
		m_width,
		m_height,
		dev_kseedsl,
		dev_kseedsa,
		dev_kseedsb,
		dev_kseedsx,
		dev_kseedsy,
		dev_kseed_sita_n,
		dev_kseed_m_n,
		dev_kseed_L_n,
		dev_kseed_X_n,
		dev_kseed_Y_n);
	//////////////////////////////////////////
#endif

	for( int itr = 0; itr < 10; itr++ )
	{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		{
			cudaStatus=cudaEventRecord(start,0);
#if 0
			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+15)/threadsPerBlock.x,(m_height+15)/threadsPerBlock.y);
			SetMatrix<<<numBlock,threadsPerBlock>>>(dev_distvec,m_width,m_height,1.7976931348623158e+308);
#else
			SetMatrix_Efficient<<<16,16*16>>>(dev_distvec,m_width,m_height,1.7976931348623158e+308);
#endif
			
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
		}
		
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			cudaStatus=cudaEventRecord(start,0);
#if 0
			SetMinimumOnLab<<<(kseedsSize+511)/512,512>>>(
				kseedsSize,
				alpha,
				betta,
				gama,
				fai,
				m_width,
				m_height,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_kseedsl,
				dev_kseedsa,
				dev_kseedsb,
				dev_kseedsx,
				dev_kseedsy,
				dev_klabels,
				dev_distvec,
				STEP,
				M);
#else
			dim3    threadsPerBlock(32,32);
			dim3    numBlock((m_width+31)/threadsPerBlock.x,(m_height+31)/threadsPerBlock.y);
			SetMinimumOnLab_AllSeeds<<<numBlock,threadsPerBlock>>>(
				kseedsSize,
				alpha,
				betta,
				gama,
				fai,
				m_width,
				m_height,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_sita_n,
				dev_m_n,
				dev_L_n,
				dev_X_n,
				dev_Y_n,
				dev_kseedsl,
				dev_kseedsa,
				dev_kseedsb,
				dev_kseedsx,
				dev_kseedsy,
				dev_kseed_sita_n,
				dev_kseed_m_n,
				dev_kseed_L_n,
				dev_kseed_X_n,
				dev_kseed_Y_n,
				dev_klabels,
				dev_distvec);
#endif
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			/*cudaStatus=cudaEventRecord(start,0);*/
			/*---------------------------------------------------------------------------------*/
//			const int numk=kseedsSize;
			cudaMemset(dev_sigmal,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmaa,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmab,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmax,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmay,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			/*----------------------------------------------------------------------------------*/
			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+15)/threadsPerBlock.x,(m_height+15)/threadsPerBlock.y);
			unsigned int *mutex; 
			unsigned int zero = 0; 
			cudaMalloc( (void**)&mutex, sizeof(unsigned int) ); 
			cudaMemcpy(mutex, &zero, sizeof(unsigned int), cudaMemcpyHostToDevice );
#if 0
			cudaStatus=cudaEventRecord(start,0);
			//1225.2045ms
			StatisticsLABXY_Seed_collect<<<numBlock,threadsPerBlock>>>(
				mutex,
				kseedsSize,
				m_width,
				m_height,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_klabels,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
#endif
#if 0
			//69.114082ms
			StatisticsLABXY_Seed_collect_CPU(
				kseedsSize,
				m_width,
				m_height,
				host_m_lvec,
				host_m_avec,
				host_m_bvec,
				dev_klabels,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
#endif
#if 1
			cudaStatus=cudaEventRecord(start,0);
			//344.65720ms
			StatisticsLABXY_Seed_collect_new2014_11_3<<<blocks*2,1024>>>(
				mutex,
				kseedsSize,
				m_width,
				m_height,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_klabels,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
#endif
#if 0
			cudaStatus=cudaEventRecord(start,0);
			dim3    threadsPerBlock_Quad(32,32);
			dim3    numBlock_Quad(4,4);
			StatisticsLABXY_Seed_collect_blocks<<<numBlock_Quad,threadsPerBlock_Quad>>>(
				kseedsSize,
				m_width,
				m_height,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_klabels,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;

#endif
			cudaStatus=cudaEventRecord(start,0);
			cudaGetLastError_Sync_CUI();
			StatisticsLABXY_Seed_calculate<<<1,512>>>(
				kseedsSize,
				m_width,
				m_height,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize,
				dev_kseedsl,
				dev_kseedsa,
				dev_kseedsb,
				dev_kseedsx,
				dev_kseedsy,
				dev_kseed_sita_n,
				dev_kseed_m_n,
				dev_kseed_L_n,
				dev_kseed_X_n,
				dev_kseed_Y_n);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
		}
		
	}
	cudaMemcpy(host_klabels,dev_klabels,m_width*m_height*sizeof(int),cudaMemcpyDeviceToHost);
	{
	cudaFree(dev_kseedsl);
	cudaFree(dev_kseedsa);
	cudaFree(dev_kseedsb);
	cudaFree(dev_kseedsx);
	cudaFree(dev_kseedsy);
	cudaFree(dev_klabels);
	cudaFree(dev_m_lvec);
	cudaFree(dev_m_avec);
	cudaFree(dev_m_bvec);
	cudaFree(dev_distvec);
	////////////////////////
	cudaFree(dev_sita_n);
	cudaFree(dev_m_n);
	cudaFree(dev_L_n);
	cudaFree(dev_X_n);
	cudaFree(dev_Y_n);
		{
			cudaFree(dev_sigmal);
			cudaFree(dev_sigmaa);
			cudaFree(dev_sigmab);
			cudaFree(dev_sigmax);
			cudaFree(dev_sigmay);
			cudaFree(dev_clustersize);
			//////////////////////////
			cudaFree(dev_kseed_sita_n) ;
			cudaFree(dev_kseed_m_n);
			cudaFree(dev_kseed_L_n);
			cudaFree(dev_kseed_X_n);
			cudaFree(dev_kseed_Y_n);
		}
	}
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	assert(cudaDeInit_CUI()==true);
	
}
/*------------------------------------------------------------------------------------------*/
/**
*cuda方法实行超像素算法。
*
*
*@param    alpha  角度参数alpha
*@param    betta  模值betta
*@param    gama   亮度gama
*@param    fai    XY距离
*@param    kseedsSize  种子个数
*@param    m_width   图像宽度
*@param    m_height  图像高度
*@param	   m_lvec  图像L分量
*@param	   m_avec  图像A分量
*@param	   m_bvec  图像B分量
*@param	   kseedsl  种子L分量
*@param	   kseedsa  种子A分量
*@param	   kseedsb  种子B分量
*@param	   kseedsx  种子X分量
*@param	   kseedsy  种子Y分量
*@param	   klabels  图像图块的标定图像
*@param	   STEP     未使用
*@param	   edgemag  未使用
*@param	   M        未使用密度因素
*
*
*@note
*利用GPU实现超像素算法
*小图1.8S  大图7.2S
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_gpu_simplify(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,   
	const int m_height,
	double*				host_m_lvec,
	double*				host_m_avec,
	double*				host_m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels,
	const int			STEP,
	double*				host_edgemag,
	const double		M)
{
	cudaError_t cudaStatus;
	///////////////////////////////////////////
	double*				dev_kseedsl;
	double*				dev_kseedsa;
	double*				dev_kseedsb;
	double*				dev_kseedsx;
	double*				dev_kseedsy;
	int*				dev_klabels;
	double*				dev_m_lvec;
	double*				dev_m_avec;
	double*				dev_m_bvec;
	double*				dev_sita_n;
	double*				dev_m_n;
	double*				dev_L_n;
	double*				dev_X_n;
	double*				dev_Y_n;
	double*				dev_edgemag=nullptr;
	///////////////////////////////////////////
	double* dev_distvec;
	///////////////////////////////////////////
	assert(cudaInit_CUI()==true);
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop,0);
	int blocks=prop.multiProcessorCount;
	{
		cudaStatus = cudaMalloc((void**)&dev_kseedsl, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsb, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsx, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsy, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_klabels,m_width*m_height * sizeof(int));
		cudaStatus = cudaMalloc((void**)&dev_m_lvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_avec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_bvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_distvec, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_sita_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_L_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_X_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_Y_n, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMemcpy(dev_kseedsl, host_kseedsl, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsa, host_kseedsa, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsb, host_kseedsb, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsx, host_kseedsx, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsy, host_kseedsy, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_klabels, host_klabels, m_width*m_height * sizeof(int), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_lvec, host_m_lvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_avec, host_m_avec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_bvec, host_m_bvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		////////////////////////////////////////////////////////////////////////////////
	}
	double* dev_sigmal;
	double* dev_sigmaa;
	double* dev_sigmab;
	double* dev_sigmax;
	double* dev_sigmay;
	double* dev_clustersize;
	/////////////////////////////////////////////////////////////////////////////////////
	double*  dev_kseed_sita_n;
	double*  dev_kseed_m_n;
	double*  dev_kseed_L_n;
	double*  dev_kseed_X_n;
	double*  dev_kseed_Y_n;
	/////////////////////////////////////////////////////////////////////////////////////
	{
		cudaStatus = cudaMalloc((void**)&dev_sigmal, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmaa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmab, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmax, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmay, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_clustersize, kseedsSize * sizeof(double));
		cudaStatus=cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));
		cudaGetLastError_Sync_CUI();
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_kseed_sita_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_m_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_L_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_X_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_Y_n, kseedsSize * sizeof(double));
	}
	cudaEvent_t start,stop;
	float costtime_ms=0;
	float costtime_us=0;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
#if 1
	///////////////////////////////////////////
	PerformSuperpixelSLIC_ColorConvert_gpu(
		kseedsSize,
		m_width,
		m_height,
		dev_m_lvec,
		dev_m_avec,
		dev_m_bvec,
		dev_sita_n,
		dev_m_n,
		dev_L_n,
		dev_X_n,
		dev_Y_n);
	//////////////////////////////////////////
	PerformSuperpixelSLIC_Init_ColorConvert<<<1,256>>>(
		kseedsSize,
		m_width,
		m_height,
		dev_kseedsl,
		dev_kseedsa,
		dev_kseedsb,
		dev_kseedsx,
		dev_kseedsy,
		dev_kseed_sita_n,
		dev_kseed_m_n,
		dev_kseed_L_n,
		dev_kseed_X_n,
		dev_kseed_Y_n);
	cudaGetLastError_Sync_CUI();
	//////////////////////////////////////////
#endif
	for( int itr = 0; itr <10; itr++ )
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		{
			cudaStatus=cudaEventRecord(start,0);
			SetMatrix_Efficient<<<16,16*16>>>(dev_distvec,m_width,m_height,1.7976931348623158e+308);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			cudaStatus=cudaEventRecord(start,0);
			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+threadsPerBlock.x-1)/threadsPerBlock.x,(m_height+threadsPerBlock.y-1)/threadsPerBlock.y);

			SetMinimumOnThetaMLXY_9Seeds<<<numBlock,threadsPerBlock>>>(		
					kseedsSize,
					alpha,
					betta,
					gama,
					fai,
					m_width,
					m_height,			
					dev_sita_n,
					dev_m_n,
					dev_L_n,
					dev_X_n,
					dev_Y_n,				
					dev_kseed_sita_n,
					dev_kseed_m_n,
					dev_kseed_L_n,
					dev_kseed_X_n,
					dev_kseed_Y_n,
					dev_klabels,
					dev_distvec);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{			
#if 1
			cudaStatus=cudaEventRecord(start,0);
			/*---------------------------------------------------------------------------------*/
			//			const int numk=kseedsSize;
			cudaMemset(dev_sigmal,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmaa,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmab,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmax,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_sigmay,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));
			cudaGetLastError_Sync_CUI();
			/*----------------------------------------------------------------------------------*/
			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+15)/threadsPerBlock.x,(m_height+15)/threadsPerBlock.y);
			cudaStatus=cudaEventRecord(start,0);
			cudaGetLastError_Sync_CUI();
//69.114082ms
			StatisticsLABXY_Seed_collect_CPU(
				kseedsSize,
				m_width,
				m_height,
				host_m_lvec,
				host_m_avec,
				host_m_bvec,
				dev_klabels,
				nullptr,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
						cudaStatus=cudaEventRecord(start,0);
			cudaGetLastError_Sync_CUI();
			StatisticsLABXY_Seed_calculate<<<1,512>>>(
				kseedsSize,
				m_width,
				m_height,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize,
				dev_kseedsl,
				dev_kseedsa,
				dev_kseedsb,
				dev_kseedsx,
				dev_kseedsy,
				dev_kseed_sita_n,
				dev_kseed_m_n,
				dev_kseed_L_n,
				dev_kseed_X_n,
				dev_kseed_Y_n);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
			
#else

			cudaStatus=cudaEventRecord(start,0);
			cudaGetLastError_Sync_CUI();
			StatisticsLABXY_Seed_collect_gpu_search<<<(kseedsSize+511)/512,512>>>(
				kseedsSize,
				m_width,
				m_height,
				dev_kseedsx,
				dev_kseedsy,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_klabels,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
#endif
		}
	}
#if 1
	////////////////////////////////////////////////////////////////////////////////////////
	cudaStatus=cudaMemcpy(host_klabels,dev_klabels,m_width*m_height*sizeof(int),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsl,dev_kseedsl, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsa,dev_kseedsa, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsb,dev_kseedsb, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsx,dev_kseedsx, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsy,dev_kseedsy, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	{
		cudaFree(dev_kseedsl);
		cudaFree(dev_kseedsa);
		cudaFree(dev_kseedsb);
		cudaFree(dev_kseedsx);
		cudaFree(dev_kseedsy);
		cudaFree(dev_klabels);
		cudaFree(dev_m_lvec);
		cudaFree(dev_m_avec);
		cudaFree(dev_m_bvec);
		cudaFree(dev_distvec);
		////////////////////////
		cudaFree(dev_sita_n);
		cudaFree(dev_m_n);
		cudaFree(dev_L_n);
		cudaFree(dev_X_n);
		cudaFree(dev_Y_n);
		{
			cudaFree(dev_sigmal);
			cudaFree(dev_sigmaa);
			cudaFree(dev_sigmab);
			cudaFree(dev_sigmax);
			cudaFree(dev_sigmay);
			cudaFree(dev_clustersize);
			//////////////////////////
			cudaFree(dev_kseed_sita_n) ;
			cudaFree(dev_kseed_m_n);
			cudaFree(dev_kseed_L_n);
			cudaFree(dev_kseed_X_n);
			cudaFree(dev_kseed_Y_n);
		}
	}
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	assert(cudaDeInit_CUI()==true);
}
/*------------------------------------------------------------------------------------------*/
/**
*cuda方法实行超像素算法。
*
*
*@param    alpha  角度参数alpha
*@param    betta  模值betta
*@param    gama   亮度gama
*@param    fai    XY距离
*@param    kseedsSize  种子个数
*@param    m_width   图像宽度
*@param    m_height  图像高度
*@param	   m_lvec  图像L分量
*@param	   m_avec  图像A分量
*@param	   m_bvec  图像B分量
*@param	   kseedsl  种子L分量
*@param	   kseedsa  种子A分量
*@param	   kseedsb  种子B分量
*@param	   kseedsx  种子X分量
*@param	   kseedsy  种子Y分量
*@param	   klabels  图像图块的标定图像
*@param	   STEP     未使用
*@param	   edgemag  未使用
*@param	   M        未使用密度因素
*
*
*@note
*利用GPU实现超像素算法
*小图1.8S  大图7.2S
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_gpu_simplify2(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,   
	const int m_height,
	double*				host_m_lvec,
	double*				host_m_avec,
	double*				host_m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels,
	const int			STEP,
	double*				host_edgemag,
	const double		M)
{
	cudaError_t cudaStatus;
	///////////////////////////////////////////
	double*				dev_kseedsl;
	double*				dev_kseedsa;
	double*				dev_kseedsb;
	double*				dev_kseedsx;
	double*				dev_kseedsy;
	int*				dev_klabels;
	double*				dev_m_lvec;
	double*				dev_m_avec;
	double*				dev_m_bvec;
	double*				dev_sita_n;
	double*				dev_m_n;
	double*				dev_L_n;
	double*				dev_X_n;
	double*				dev_Y_n;
	double*				dev_edgemag=nullptr;
	///////////////////////////////////////////
	double* dev_distvec;
	///////////////////////////////////////////
	assert(cudaInit_CUI()==true);

	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop,0);
	int blocks=prop.multiProcessorCount;

	{
		cudaStatus = cudaMalloc((void**)&dev_kseedsl, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsb, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsx, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsy, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_klabels,m_width*m_height * sizeof(int));
		cudaStatus = cudaMalloc((void**)&dev_m_lvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_avec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_bvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_distvec, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_sita_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_L_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_X_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_Y_n, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMemcpy(dev_kseedsl, host_kseedsl, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsa, host_kseedsa, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsb, host_kseedsb, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsx, host_kseedsx, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseedsy, host_kseedsy, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_klabels, host_klabels, m_width*m_height * sizeof(int), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_lvec, host_m_lvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_avec, host_m_avec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_bvec, host_m_bvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		////////////////////////////////////////////////////////////////////////////////
	}

	double* dev_clustersize;
	/////////////////////////////////////////////////////////////////////////////////////
	double*  dev_kseed_sita_n;
	double*  dev_kseed_m_n;
	double*  dev_kseed_L_n;
	double*  dev_kseed_X_n;
	double*  dev_kseed_Y_n;
	/////////////////////////////////////////////////////////////////////////////////////
	{

		cudaStatus = cudaMalloc((void**)&dev_clustersize, kseedsSize * sizeof(double));
		cudaStatus=cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));
		cudaGetLastError_Sync_CUI();
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_kseed_sita_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_m_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_L_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_X_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_Y_n, kseedsSize * sizeof(double));
	}
	cudaEvent_t start,stop;
	float costtime_ms=0;
	float costtime_us=0;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
#if 1
	///////////////////////////////////////////
	PerformSuperpixelSLIC_ColorConvert_gpu(
		kseedsSize,
		m_width,
		m_height,
		dev_m_lvec,
		dev_m_avec,
		dev_m_bvec,
		dev_sita_n,
		dev_m_n,
		dev_L_n,
		dev_X_n,
		dev_Y_n);
	//////////////////////////////////////////
	PerformSuperpixelSLIC_Init_ColorConvert<<<1,256>>>(
		kseedsSize,
		m_width,
		m_height,
		dev_kseedsl,
		dev_kseedsa,
		dev_kseedsb,
		dev_kseedsx,
		dev_kseedsy,
		dev_kseed_sita_n,
		dev_kseed_m_n,
		dev_kseed_L_n,
		dev_kseed_X_n,
		dev_kseed_Y_n);
	cudaGetLastError_Sync_CUI();
	//////////////////////////////////////////
#endif
	for( int itr = 0; itr <2; itr++ )
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		{
			cudaStatus=cudaEventRecord(start,0);
			SetMatrix_Efficient<<<16,16*16>>>(dev_distvec,m_width,m_height,1.7976931348623158e+308);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			cudaStatus=cudaEventRecord(start,0);
			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+threadsPerBlock.x-1)/threadsPerBlock.x,(m_height+threadsPerBlock.y-1)/threadsPerBlock.y);

			SetMinimumOnThetaMLXY_9Seeds<<<numBlock,threadsPerBlock>>>(		
					kseedsSize,
					alpha,
					betta,
					gama,
					fai,
					m_width,
					m_height,			
					dev_sita_n,
					dev_m_n,
					dev_L_n,
					dev_X_n,
					dev_Y_n,				
					dev_kseed_sita_n,
					dev_kseed_m_n,
					dev_kseed_L_n,
					dev_kseed_X_n,
					dev_kseed_Y_n,
					dev_klabels,
					dev_distvec);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		{			

			StatisticsThetaMLXY_Seed_collect_CPU_Incompletion(
								kseedsSize,
									m_width,
									m_height,
									host_m_lvec,
									host_m_avec,
									host_m_bvec,
									dev_klabels,
								    NULL,
									dev_kseed_sita_n,
									dev_kseed_m_n,
									dev_kseed_L_n,
									dev_kseed_X_n,
									dev_kseed_Y_n);
		}
	}
#if 1
	////////////////////////////////////////////////////////////////////////////////////////
	cudaStatus=cudaMemcpy(host_klabels,dev_klabels,m_width*m_height*sizeof(int),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsl,dev_kseedsl, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsa,dev_kseedsa, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsb,dev_kseedsb, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsx,dev_kseedsx, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
	cudaStatus=cudaMemcpy(host_kseedsy,dev_kseedsy, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);
#endif
	///////////////////////////////////////////////////////////////////////////////////////
	{
		cudaFree(dev_kseedsl);
		cudaFree(dev_kseedsa);
		cudaFree(dev_kseedsb);
		cudaFree(dev_kseedsx);
		cudaFree(dev_kseedsy);
		cudaFree(dev_klabels);
		cudaFree(dev_m_lvec);
		cudaFree(dev_m_avec);
		cudaFree(dev_m_bvec);
		cudaFree(dev_distvec);
		////////////////////////
		cudaFree(dev_sita_n);
		cudaFree(dev_m_n);
		cudaFree(dev_L_n);
		cudaFree(dev_X_n);
		cudaFree(dev_Y_n);
		{
			//////////////////////////
			cudaFree(dev_kseed_sita_n) ;
			cudaFree(dev_kseed_m_n);
			cudaFree(dev_kseed_L_n);
			cudaFree(dev_kseed_X_n);
			cudaFree(dev_kseed_Y_n);
		}
	}
	cudaEventDestroy(start);
	cudaEventDestroy(stop);
	assert(cudaDeInit_CUI()==true);
}
/*------------------------------------------------------------------------------------------*/
/**
*cuda方法实行超像素算法。
*
*
*@param    alpha  角度参数alpha
*@param    betta  模值betta
*@param    gama   亮度gama
*@param    fai    XY距离
*@param    kseedsSize  种子个数
*@param    m_width   图像宽度
*@param    m_height  图像高度

*@param	   klabels  图像图块的标定图像
*@param	   STEP     未使用
*@param	   edgemag  未使用
*@param	   M        未使用密度因素
*
*
*@note
*利用GPU实现超像素算法
*小图1.8S  大图7.2S
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_ThetaMLXY_gpu_simplify(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,   
	const int m_height,
	double*     host_sita_n,
	double*     host_m_n,
	double*     host_L_n,
	double*     host_X_n,
	double*     host_Y_n,
	double*     host_kseedsTheta,
	double*     host_kseedsM,
	double*     host_kseedsL,
	double*     host_kseedsX,
	double*     host_kseedsY,
	int*		host_klabels,
	const int			STEP)
{
	cudaError_t cudaStatus;

	double*  dev_kseed_sita_n;
	double*  dev_kseed_m_n;
	double*  dev_kseed_L_n;
	double*  dev_kseed_X_n;
	double*  dev_kseed_Y_n;	
	double*	 dev_sita_n;
	double*	 dev_m_n;
	double*	 dev_L_n;
	double*	 dev_X_n;
	double*	 dev_Y_n;
	int*     dev_klabels;
	double*  dev_distvec;
	assert(cudaInit_CUI()==true);
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop,0);
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_klabels,m_width*m_height * sizeof(int));
		cudaStatus = cudaMalloc((void**)&dev_distvec, m_width*m_height* sizeof(double));

		cudaStatus = cudaMalloc((void**)&dev_kseed_sita_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_m_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_L_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_X_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_Y_n, kseedsSize* sizeof(double));

		cudaStatus = cudaMalloc((void**)&dev_sita_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_L_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_X_n, m_width*m_height* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_Y_n, m_width*m_height* sizeof(double));
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMemcpy(dev_klabels, host_klabels, m_width*m_height * sizeof(int), cudaMemcpyHostToDevice);
		
		cudaStatus = cudaMemcpy(dev_kseed_sita_n, host_kseedsTheta, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseed_m_n, host_kseedsM, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseed_L_n, host_kseedsL, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseed_X_n, host_kseedsX, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_kseed_Y_n, host_kseedsY, kseedsSize * sizeof(double), cudaMemcpyHostToDevice);

		cudaStatus = cudaMemcpy(dev_sita_n, host_sita_n, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_n, host_m_n,m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_L_n, host_L_n,m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_X_n, host_X_n,m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_Y_n, host_Y_n,m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
	cudaEvent_t start,stop;
	float costtime_ms=0;
	float costtime_us=0;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	for( int itr = 0; itr <10; itr++ )
	{
		{
			cudaStatus=cudaEventRecord(start,0);
			SetMatrix_Efficient<<<16,16*16>>>(dev_distvec,m_width,m_height,1.7976931348623158e+308);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
		}
			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+threadsPerBlock.x-1)/threadsPerBlock.x,(m_height+threadsPerBlock.y-1)/threadsPerBlock.y);
#if 1
			SetMinimumOnThetaMLXY_9Seeds<<<numBlock,threadsPerBlock>>>(			
							kseedsSize,
							alpha,
							betta,
							gama,
							fai,
							m_width,
							m_height,			
							dev_sita_n,
							dev_m_n,
							dev_L_n,
							dev_X_n,
							dev_Y_n,				
							dev_kseed_sita_n,
							dev_kseed_m_n,
							dev_kseed_L_n,
							dev_kseed_X_n,
							dev_kseed_Y_n,
							dev_klabels,
							dev_distvec);

			cudaGetLastError_Sync_CUI();

			StatisticsThetaMLXY_Seed_collect_CPU(
							kseedsSize,
							m_width,
							m_height,
							host_sita_n,
							host_m_n,
							host_L_n,
							host_X_n,
							host_Y_n,	
							dev_klabels,
    						dev_kseed_sita_n,
							dev_kseed_m_n,
							dev_kseed_L_n,
							dev_kseed_X_n,
							dev_kseed_Y_n);
#endif
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);
			costtime_us=costtime_ms*1000;
}	
		cudaMemcpy(host_klabels,dev_klabels,m_width*m_height*sizeof(int),cudaMemcpyDeviceToHost);		
		cudaMemcpy(host_kseedsTheta,dev_kseed_sita_n,kseedsSize * sizeof(double),cudaMemcpyDeviceToHost);		
		cudaMemcpy(host_kseedsM,dev_kseed_m_n,kseedsSize * sizeof(double),cudaMemcpyDeviceToHost);		
		cudaMemcpy(host_kseedsL,dev_kseed_L_n,kseedsSize * sizeof(double),cudaMemcpyDeviceToHost);		
		cudaMemcpy(host_kseedsX,dev_kseed_X_n,kseedsSize * sizeof(double),cudaMemcpyDeviceToHost);		
		cudaMemcpy(host_kseedsY,dev_kseed_Y_n,kseedsSize * sizeof(double),cudaMemcpyDeviceToHost);

	    cudaFree(dev_sita_n);
		cudaFree(dev_m_n);
		cudaFree(dev_L_n);
		cudaFree(dev_X_n);
		cudaFree(dev_Y_n);
		cudaFree(dev_kseed_sita_n) ;
		cudaFree(dev_kseed_m_n);
		cudaFree(dev_kseed_L_n);
		cudaFree(dev_kseed_X_n);
		cudaFree(dev_kseed_Y_n);
		cudaFree(dev_distvec);
		cudaFree(dev_klabels);
	assert(cudaDeInit_CUI()==true);
}
/*------------------------------------------------------------------------------------------*/
/**
*绘制轮廓核函数
*
*@param		[in,out]	ubuff  图像数据
*@param		[in]		labels 图像labels
*@param					width  图像宽度
*@param					height 图像高度
*@param					color_in   颜色内边界颜色
*@param					color_out  颜色外边界颜色
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void DrawContoursAroundSegments_thread(
	unsigned int*			ubuff,
	int*					labels,
	const int				width,
	const int				height,
	const unsigned int		color_in,
	const unsigned int      color_out) 
{
	int k =blockIdx.x*blockDim.x+threadIdx.x;
	int j =blockIdx.y*blockDim.y+threadIdx.y;
	int mainindex = j*width + k;
	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
	////////////////////////////////////////////////
		int np(0);
		if (k>=0&&k<width&&j>=0&&j<height){
				for(register int i = 0; i < 8; i++ ){
					int x = k + dx8[i];
					int y = j + dy8[i];
					if( (x >= 0 && x < width) && (y >= 0 && y < height) ){
								int index = y*width + x;
								//if( false == istaken[index] )//comment this to obtain internal contours
								{
									if( labels[mainindex] != labels[index] ){
										np++;
										//ubuff[index] =0xff000000; //2pixel外线
										ubuff[index] =color_out; //2pixel外线
									}
								}
					}
				}
				if( np > 1 ){
						ubuff[mainindex] =color_in;//2pixel内线
				}
		}		
}
/*------------------------------------------------------------------------------------------*/
/**
*利用GPU方法绘制轮廓到图像上
*@param	  [in,out] ubuff     图像
*@param	  [in] labels    labels矩阵
*@param	   width     图像宽度
*@param	   height    图像高度
*@param	   color_in  轮廓内边界颜色
*@param    color_out 轮廓外边界颜色
*
*/
/*------------------------------------------------------------------------------------------*/
void DrawContoursAroundSegments_gpu(
	unsigned int*			ubuff,
	int*					labels,
	const int				width,
	const int				height,
	const unsigned int	color_in,
	const unsigned int  color_out)
{
	unsigned int* ubuff_dev;
	int*  labels_dev;
	cudaError_t cudaStatus;
	assert(cudaInit_CUI()==true);
	cudaStream_t stream;//流的结构体

	cudaStatus=cudaStreamCreate(&stream);	
	cudaStatus=cudaMalloc((void**)&ubuff_dev, width*height*sizeof(unsigned int));
	cudaStatus=cudaMalloc((void**)&labels_dev,width*height*sizeof(int));

	cudaStatus = cudaMemcpy(ubuff_dev,ubuff, width*height*sizeof(unsigned int), cudaMemcpyHostToDevice);
	cudaStatus = cudaMemcpy(labels_dev,labels,width*height*sizeof(int), cudaMemcpyHostToDevice);
	/////////////////////////////////////////////////////////////////////////////////////////
	dim3    threadsPerBlock(16,16);
	dim3    numBlock((width+threadsPerBlock.x-1)/threadsPerBlock.x,(height+threadsPerBlock.y-1)/threadsPerBlock.y);
	DrawContoursAroundSegments_thread<<<numBlock,threadsPerBlock>>>(ubuff_dev,
											labels_dev,
											width,
											height,
											color_in,
											color_out);
	cudaGetLastError_Sync_CUI();
	cudaMemcpy(ubuff,ubuff_dev,width*height*sizeof(unsigned int),cudaMemcpyDeviceToHost);

	cudaStatus=cudaStreamDestroy(stream);
	cudaFree(ubuff_dev);
	cudaFree(labels_dev);
	/////////////////////////////////////////////////////////////////////////////////////////
	assert(cudaDeInit_CUI()==true);
}
/*------------------------------------------------------------------------------------------*/
/**
*Normal  0x00 00 00 00 
*MASK    0xff ff ff ff
*设置超像素的屏蔽数据\n
*屏蔽掉轮廓
*@param
*@param	[out]	dev_mask      被屏蔽的轮廓
*@param	[in]	dev_labels    labels矩阵
*@param		width         图像宽度
*@param		height        图像高度
*@param     Pixel         超像素
*/
/*------------------------------------------------------------------------------------------*/
void InitMaskTemplate(
	unsigned int*			dev_mask,
	int*					dev_labels,
	const int				width,
	const int				height,
	const int                Pixel)
{
	int color_in;
	int color_out;
	if (Pixel==2){
		color_in=0xffffffff;
		color_out=0x00000000;
	}else if(Pixel==4){		
		color_in=0xffffffff;
		color_out=0xffffffff;
	}
	
	cudaMemset(dev_mask,0,sizeof(unsigned int)*width*height);
	dim3    threadsPerBlock(16,16);
	dim3    numBlock((width+threadsPerBlock.x-1)/threadsPerBlock.x,(height+threadsPerBlock.y-1)/threadsPerBlock.y);
	DrawContoursAroundSegments_thread<<<numBlock,threadsPerBlock>>>(dev_mask,
		dev_labels,
		width,
		height,
		color_in,
		color_out);
	cudaGetLastError_Sync_CUI();
}
/*------------------------------------------------------------------------------------------*/
/**
*
*利用GPU方法获取种子
*.cu本地调用
*
*@param			 kseedsSize   种子个数
*@param			 m_width      图像宽度
*@param			 m_height     图像高度
*@param 	[in]	 host_m_lvec  种子L分量
*@param 	[in]	 host_m_avec  种子A分量
*@param 	[in]	 host_m_bvec  种子B分量
*@param 	[out]	 host_kseedsl  种子L分量
*@param 	[out]	 host_kseedsa  种子A分量
*@param 	[out]	 host_kseedsb  种子B分量
*@param 	[out]	 host_kseedsx  种子X分量
*@param 	[out]	 host_kseedsy  种子Y分量
*@param 	[in]	 host_klabels  图像图块的标定图像
*
*/
/*------------------------------------------------------------------------------------------*/
void  GetSeedsLabxy_gpu(
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				host_m_lvec,
	double*				host_m_avec,
	double*				host_m_bvec,
	double*				host_kseedsl,
	double*				host_kseedsa,
	double*				host_kseedsb,
	double*				host_kseedsx,
	double*				host_kseedsy,
	int*				host_klabels)
{
	cudaEvent_t start,stop;
	float costtime_ms=0;
	float costtime_us=0;
	cudaError_t cudaStatus;
	unsigned int*       mask_img;
	double*				dev_kseedsl;
	double*				dev_kseedsa;
	double*				dev_kseedsb;
	double*				dev_kseedsx;
	double*				dev_kseedsy;
	int*				dev_klabels;
	double*			dev_m_lvec;
	double*			dev_m_avec;
	double*			dev_m_bvec;
	{
		cudaEventCreate(&start);
		cudaEventCreate(&stop);
		cudaStatus=cudaMalloc((void**)&mask_img,sizeof(unsigned int)*m_width*m_height);
		cudaStatus = cudaMalloc((void**)&dev_kseedsl, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsb, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsx, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseedsy, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_klabels,m_width*m_height * sizeof(int));
		cudaStatus = cudaMalloc((void**)&dev_m_lvec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_avec,m_width*m_height * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_m_bvec,m_width*m_height * sizeof(double));
#if 1
		cudaStatus = cudaMemset(dev_kseedsl,0, kseedsSize * sizeof(double));
		cudaStatus = cudaMemset(dev_kseedsa,0, kseedsSize * sizeof(double));
		cudaStatus = cudaMemset(dev_kseedsb,0, kseedsSize * sizeof(double));
		cudaStatus = cudaMemset(dev_kseedsx,0, kseedsSize * sizeof(double));
		cudaStatus = cudaMemset(dev_kseedsy,0, kseedsSize * sizeof(double));
#endif
		cudaStatus = cudaMemcpy(dev_klabels, host_klabels, m_width*m_height * sizeof(int), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_lvec, host_m_lvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_avec, host_m_avec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
		cudaStatus = cudaMemcpy(dev_m_bvec, host_m_bvec, m_width*m_height * sizeof(double), cudaMemcpyHostToDevice);
	}
	
	double*			dev_sigmal;
	double*			dev_sigmaa;
	double*			dev_sigmab;
	double*			dev_sigmax;
	double*			dev_sigmay;
	double*			dev_clustersize;
	double*				dev_kseed_sita_n;
	double*				dev_kseed_m_n;
	double*				dev_kseed_L_n;
	double*				dev_kseed_X_n;
	double*			    dev_kseed_Y_n;
	{
		cudaStatus = cudaMalloc((void**)&dev_sigmal, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmaa, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmab, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmax, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_sigmay, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_clustersize, kseedsSize * sizeof(double));
		cudaStatus=cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));
		cudaGetLastError_Sync_CUI();
		////////////////////////////////////////////////////////////////////////////////
		cudaStatus = cudaMalloc((void**)&dev_kseed_sita_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_m_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_L_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_X_n, kseedsSize * sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_Y_n, kseedsSize * sizeof(double));
	}
		/*----------------------------------------------------------------------------------*/
			cudaStatus =cudaMemset(dev_sigmal,0,kseedsSize*sizeof(double));			
			cudaStatus =cudaMemset(dev_sigmaa,0,kseedsSize*sizeof(double));			
			cudaStatus =cudaMemset(dev_sigmab,0,kseedsSize*sizeof(double));			
			cudaStatus =cudaMemset(dev_sigmax,0,kseedsSize*sizeof(double));			
			cudaStatus =cudaMemset(dev_sigmay,0,kseedsSize*sizeof(double));			
			cudaStatus =cudaMemset(dev_clustersize,0,kseedsSize*sizeof(double));			
		/*----------------------------------------------------------------------------------*/

			InitMaskTemplate(mask_img,dev_klabels,m_width,m_height,4);

			dim3    threadsPerBlock(16,16);
			dim3    numBlock((m_width+15)/threadsPerBlock.x,(m_height+15)/threadsPerBlock.y);
			cudaStatus=cudaEventRecord(start,0);
			cudaGetLastError_Sync_CUI();
#if 0
			StatisticsLABXY_Seed_collect_gpu_search_AllImg<<<(kseedsSize+511)/512,512>>>(
				kseedsSize,
				m_width,
				m_height,
				dev_m_lvec,
				dev_m_avec,
				dev_m_bvec,
				dev_klabels,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
#else
			StatisticsLABXY_Seed_collect_CPU(
				kseedsSize,
				m_width,
				m_height,
				host_m_lvec,
				host_m_avec,
				host_m_bvec,
				dev_klabels,
				mask_img,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize);
#endif
			
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;			
			cudaStatus=cudaEventRecord(start,0);
			cudaGetLastError_Sync_CUI();
			StatisticsLABXY_Seed_calculate<<<1,512>>>(
				kseedsSize,
				m_width,
				m_height,
				dev_sigmal,
				dev_sigmaa,
				dev_sigmab,
				dev_sigmax,
				dev_sigmay,
				dev_clustersize,
				dev_kseedsl,
				dev_kseedsa,
				dev_kseedsb,
				dev_kseedsx,
				dev_kseedsy,
				dev_kseed_sita_n,
				dev_kseed_m_n,
				dev_kseed_L_n,
				dev_kseed_X_n,
				dev_kseed_Y_n);
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventRecord(stop,0);	
			cudaGetLastError_Sync_CUI();
			cudaStatus=cudaEventElapsedTime(&costtime_ms,start,stop);	
			costtime_us=costtime_ms*1000;
#if 1
		////////////////////////////////////////////////////////////////////////////////////////
		cudaStatus=cudaMemcpy(host_klabels,dev_klabels,m_width*m_height*sizeof(int),cudaMemcpyDeviceToHost);	
		cudaStatus=cudaMemcpy(host_kseedsl,dev_kseedsl, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
		cudaStatus=cudaMemcpy(host_kseedsa,dev_kseedsa, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
		cudaStatus=cudaMemcpy(host_kseedsb,dev_kseedsb, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
		cudaStatus=cudaMemcpy(host_kseedsx,dev_kseedsx, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);	
		cudaStatus=cudaMemcpy(host_kseedsy,dev_kseedsy, kseedsSize*sizeof(double),cudaMemcpyDeviceToHost);
#endif
		{
			cudaEventDestroy(start);
			cudaEventDestroy(stop);
			cudaFree(mask_img);
			cudaFree(dev_kseedsl);
			cudaFree(dev_kseedsa);
			cudaFree(dev_kseedsb);
			cudaFree(dev_kseedsx);
			cudaFree(dev_kseedsy);
			cudaFree(dev_klabels);
			cudaFree(dev_m_lvec);
			cudaFree(dev_m_avec);
			cudaFree(dev_m_bvec);
		/*	cudaFree(dev_distvec);*/
			////////////////////////
			/*cudaFree(dev_sita_n);
			cudaFree(dev_m_n);
			cudaFree(dev_L_n);
			cudaFree(dev_X_n);
			cudaFree(dev_Y_n);*/
			{
				cudaFree(dev_sigmal);
				cudaFree(dev_sigmaa);
				cudaFree(dev_sigmab);
				cudaFree(dev_sigmax);
				cudaFree(dev_sigmay);
				cudaFree(dev_clustersize);
				//////////////////////////
				cudaFree(dev_kseed_sita_n) ;
				cudaFree(dev_kseed_m_n);
				cudaFree(dev_kseed_L_n);
				cudaFree(dev_kseed_X_n);
				cudaFree(dev_kseed_Y_n);
			}
		}
}
/*------------------------------------------------------------------------------------------*/
/**
*
*利用GPU方法获取种子
*.cu本地调用
*
*@param			 kseedsSize   种子个数
*@param			 m_width      图像宽度
*@param			 m_height     图像高度
*@param 	[in]	 host_m_lvec  种子L分量
*@param 	[in]	 host_m_avec  种子A分量
*@param 	[in]	 host_m_bvec  种子B分量
*@param 	[out]	 host_kseedsl  种子L分量
*@param 	[out]	 host_kseedsa  种子A分量
*@param 	[out]	 host_kseedsb  种子B分量
*@param 	[out]	 host_kseedsx  种子X分量
*@param 	[out]	 host_kseedsy  种子Y分量
*@param 	[in]	 host_klabels  图像图块的标定图像
*
*/
/*------------------------------------------------------------------------------------------*/
void  GetSeedsThetaMLXY_gpu(
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*     host_sita_n,
	double*     host_m_n,
	double*     host_L_n,
	double*     host_X_n,
	double*     host_Y_n,
	double*     host_kseedsTheta,
	double*     host_kseedsM,
	double*     host_kseedsL,
	double*     host_kseedsX,
	double*     host_kseedsY,
	int*		host_klabels)
{
	/*		cudaStatus = cudaMalloc((void**)&dev_kseed_sita_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_m_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_L_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_X_n, kseedsSize* sizeof(double));
		cudaStatus = cudaMalloc((void**)&dev_kseed_Y_n, kseedsSize* sizeof(double));*/

}
/*------------------------------------------------------------------------------------------*/
/**
*计算图块的连接矩阵\n
*.cu本地调用
*
*@param	[in]	host_labels      labels矩阵
*@param		    NumLabels       label个数
*@param	[out]	host_Matrix_E   连接矩阵
*@param		    width         图像宽度
*@param		    height        图像高度
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void Nighbour_E_matrix_thread(
	int*			labels,
	const  int		NumLabels,
	UINT32 *		Matrix_E,
	const int		width,
	const int		height)
{
#if 0
int k =blockIdx.x*blockDim.x+threadIdx.x;
	int j =blockIdx.y*blockDim.y+threadIdx.y;
	int mainindex = j*width + k;
	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
	////////////////////////////////////////////////
	int cind(0);
//	static int DoCount=0;
	for (register int ii=0;ii<NumLabels;ii++) {
		Matrix_E[ii*NumLabels+ii]=0;
	}

	int np(0);
	for(register  int i = 0; i < 8; i++ ){
		int x = k + dx8[i];
		int y = j + dy8[i];
		if( (x >= 0 && x < width) && (y >= 0 && y <height) ){
			int index = y*width + x;
			if( labels[mainindex] != labels[index] ){
				UINT32  matrix_x=labels[index];
				UINT32  matrix_y=labels[mainindex];
				Matrix_E[matrix_x*NumLabels+matrix_y]=++Matrix_E[matrix_y*NumLabels+matrix_x];
				if (Matrix_E[matrix_x*NumLabels+matrix_y]>999*2){
					Matrix_E[matrix_x*NumLabels+matrix_y]=Matrix_E[matrix_y*NumLabels+matrix_x]=999*2;
				}
			}
		}
	}
	mainindex++;
	for(register  int i = 0; i <NumLabels; i++ ){
		for(register  int j = 0; j <NumLabels; j++ ){			
			Matrix_E[i*NumLabels+j]=Matrix_E[i*NumLabels+j]>0?1:0;
		}
	}
	{
		double  threshold;		//计算超像素面积
		threshold=4*sqrt((float)width*height/NumLabels);	//周长
		threshold=threshold/8; //8分之一周长

		for(register  int i = 0; i <NumLabels; i++ ){
			for(register  int j = 0; j <NumLabels; j++ ){
				if (Matrix_E[i*NumLabels+j]>0){
					Matrix_E[i*NumLabels+j]=1;     
				}else{
					Matrix_E[i*NumLabels+j]=0;    
				}
			}
		}
	}
#endif
	int k =blockIdx.x*blockDim.x+threadIdx.x;
	int j =blockIdx.y*blockDim.y+threadIdx.y;
	int mainindex = j*width + k;
	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
	/*********************************************************************************************/
	if( (k >= 0 && k < width) && (j >= 0 && j <height) ){
			for(register  int i = 0; i < 8; i++ ){
					int x = k + dx8[i];
					int y = j + dy8[i];
					if( (x >= 0 && x < width) && (y >= 0 && y <height) ){
						int index = y*width + x;
						if( labels[mainindex] != labels[index] ){
							UINT32  matrix_x=labels[index];
							UINT32  matrix_y=labels[mainindex];
							Matrix_E[matrix_x*NumLabels+matrix_y]=Matrix_E[matrix_y*NumLabels+matrix_x]=1;
							//if (matrix_x==matrix_y) assert(Matrix_E[matrix_x*NumLabels+matrix_y]==0);
						}
					}
				}
	}
	/*********************************************************************************************/
}
/*------------------------------------------------------------------------------------------*/
/**
*计算图块的连接矩阵\n
*C函数调用
*
*@param	[in]	host_labels      labels矩阵
*@param		    NumLabels       label个数
*@param	[out]	host_Matrix_E   连接矩阵
*@param		    width         图像宽度
*@param		    height        图像高度
*
*/
/*------------------------------------------------------------------------------------------*/
void Get_Nighbour_E_matrix_gpu(
	int*			host_labels,
	const  int		NumLabels,
	UINT32 *		host_Matrix_E,
	const int		width,
	const int		height)
{
	/*---------------------------*/
	cudaError_t cudaStatus;
	int*			dev_labels;
	UINT32 *		dev_Matrix_E;
	/*---------------------------*/
	cudaStatus = cudaMalloc((void**)&dev_labels, width*height * sizeof(int));
	cudaStatus = cudaMalloc((void**)&dev_Matrix_E, NumLabels*NumLabels* sizeof(UINT32));
	cudaStatus=cudaMemcpy(dev_labels,host_labels,width*height*sizeof(int),cudaMemcpyHostToDevice);
	cudaStatus=cudaMemcpy(dev_Matrix_E,host_Matrix_E,NumLabels*NumLabels*sizeof(UINT32),cudaMemcpyHostToDevice);
	/*--------------------------------------------*/
	dim3    threadsPerBlock(16,16);
	dim3    numBlock((width+threadsPerBlock.x-1)/threadsPerBlock.x,(height+threadsPerBlock.y-1)/threadsPerBlock.y);
	 Nighbour_E_matrix_thread<<<numBlock,threadsPerBlock>>>(dev_labels,
		NumLabels,
		dev_Matrix_E,
		width,
		height);
	cudaGetLastError_Sync_CUI();
	/*--------------------------------------------*/
	cudaStatus=cudaMemcpy(host_Matrix_E,dev_Matrix_E,NumLabels*NumLabels*sizeof(UINT32),cudaMemcpyDeviceToHost);
	cudaFree(dev_labels);
	cudaFree(dev_Matrix_E);
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
		
		  int thread_id=0;
#if _DEBUG
		  int device_count;
		  cudaGetDeviceCount(&device_count);
#endif

		
#if _MSC_VER
		  thread_id =::GetCurrentThreadId();
#elif linux||__linux||__linux__||__GNUC__
		  //thread_id=(struct pthread_fake *)pthread_self()->tid;
		  thread_id=syscall( __NR_gettid );
#else
		  thread_id=-1;
		  assert(0);
#endif

	return thread_id;
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
//int GetCudaNum(){
//
//}

/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/