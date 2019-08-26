#include "CUDA_Code_LAB.h"
/*------------------------------------------------------------------------------------------*/
#include <MY_SDK_LIB/TimeMeasure.hpp>
/*------------------------------------------------------------------------------------------*/
/**
*
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
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" 
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
	int*				host_klabels);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C"
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
	const double		_invwt);

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
*
*
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_cuda_lab(
	const int kseedsSize,
	const int m_width,
	const int m_height,

	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	double*				m_xvec,
	double*				m_yvec,

	double*				kseedsl,
	double*				kseedsa,
	double*				kseedsb,
	double*				kseedsx,
	double*				kseedsy,

	int*				klabels,
	const double		_invwt)
{
			TimeMeasure tm("Superpixel.GPU");

			PerformSuperpixelSLIC_gpu_lab(
				kseedsSize,
				m_width,
				m_height,

				m_lvec,
				m_avec,
				m_bvec,
				m_xvec,
				m_yvec,

				kseedsl,
				kseedsa,
				kseedsb,
				kseedsx,
				kseedsy,

				klabels,
				_invwt);

}
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
	const unsigned int		color_in,
	const unsigned int      color_out);
/*------------------------------------------------------------------------------------------*/
/**
*绘制轮廓到图像并保存到图像
*
*@param	 [in]	ubuff    图像数据
*@param	 [in]	labels   图像labels信息
*@Parma			width    图像宽度
*@param			height   图像高度
*@Parma			color   轮廓颜色
*
*
*/
/*------------------------------------------------------------------------------------------*/
#ifndef BlackColorPNG
#define BlackColorPNG (0xff000000)
#endif
void DrawContoursAroundSegments_cuda(
	unsigned int*			ubuff,
	int*					labels,
	const int				width,
	const int				height,
	const unsigned int		color )
{
#if _MSC_VER &&  USE_CUDA_MUTEX
    LARGE_INTEGER litmp;
	LONGLONG QPart1,QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// 获得初始值
	CUDA_MUTEX.Lock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	pthread_mutex_lock(&CUDA_MUTEX);
#else

#endif	
#if 1
	DrawContoursAroundSegments_gpu(ubuff,labels,width,height,color,BlackColorPNG);
#endif
#if _MSC_VER &&  USE_CUDA_MUTEX
    QueryPerformanceCounter(&litmp);	
	QPart2 = litmp.QuadPart;//获得中止值	
	dfMinus = (double)(QPart2-QPart1);	
	dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒	
	CUDA_MUTEX.Unlock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	 pthread_mutex_unlock(&CUDA_MUTEX);
#else

#endif
	
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
	unsigned char *result);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
void HarrTransformLet_MatrixSub_cuda(
	unsigned char *matrixA, 
	unsigned char *matrixB, 
	int height, 
	int width, 
	unsigned char *result)
{
#if _MSC_VER &&  USE_CUDA_MUTEX
	CUDA_MUTEX.Lock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	pthread_mutex_lock(&CUDA_MUTEX);
#else

#endif
	HarrTransformLet_MatrixSub_gpu(
	matrixA, 
	matrixB, 
	height, 
	width, 
	result);

#if _MSC_VER &&  USE_CUDA_MUTEX
	CUDA_MUTEX.Unlock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	 pthread_mutex_unlock(&CUDA_MUTEX);
#else

#endif

}
/*------------------------------------------------------------------------------------------*/
/**
*
*获取图像的KseedsSize个种子
*
*@param               kseedsSize   种子个数
*@param               m_width      图像看度
*@param               m_height     图像高度
*@param 	[in]	  m_lvec       L分量矩阵
*@param 	[in]	  m_avec       A分量矩阵
*@param 	[in]	  m_bvec       B分量矩阵
*@param 	[out]	  kseedsl      种子的L分量
*@param 	[out]	  kseedsa      种子的A分量
*@param 	[out]	  kseedsb      种子的B分量
*@param 	[out]	  kseedsx      种子的X分量
*@param 	[out]	  kseedsy      种子的Y分量
*@param 	[in]	  klabels      图像分割的Labels
*
*
*/
/*------------------------------------------------------------------------------------------*/
void  GetSeedsLabxy_cuda(
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*				m_lvec,
	double*				m_avec,
	double*				m_bvec,
	double*				kseedsl,
	double*				kseedsa,
	double*				kseedsb,
	double*				kseedsx,
	double*				kseedsy,
	int*				klabels)
{
	TRACE_FUNC();
#if _MSC_VER &&  USE_CUDA_MUTEX
    LARGE_INTEGER litmp;
	LONGLONG QPart1,QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// 获得初始值
	CUDA_MUTEX.Lock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	pthread_mutex_lock(&CUDA_MUTEX);
#else

#endif
	
#if 1
	GetSeedsLabxy_gpu(
		kseedsSize,
		m_width,
		m_height,
		m_lvec,
		m_avec,
		m_bvec,
		kseedsl,
		kseedsa,
		kseedsb,
		kseedsx,
		kseedsy,
		klabels);
#endif
#if _MSC_VER &&  USE_CUDA_MUTEX
    QueryPerformanceCounter(&litmp);	
	QPart2 = litmp.QuadPart;//获得中止值	
	dfMinus = (double)(QPart2-QPart1);	
	dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒
	double dfms=dfTim*1000;//ms
	CUDA_MUTEX.Unlock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	 pthread_mutex_unlock(&CUDA_MUTEX);
#else

#endif
	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void Get_Nighbour_E_matrix_gpu(
	int*			host_labels,
	const  int		NumLabels,
	UINT32 *		host_Matrix_E,
	const int		width,
	const int		height);
/*------------------------------------------------------------------------------------------*/
/**
*并行计算获取E矩阵
*
*@param [in] labels        图像标定
*@param  NumLabels         labels个数
*@param [out] Matrix_E     连接矩阵
*@param  width             图像宽度
*@param  height            图像高度
*@param  filename          文件名
*@param  path              文件路径
*
*/
/*------------------------------------------------------------------------------------------*/
void Get_Nighbour_E_matrix_cuda(
	int*					labels,
	const  int		NumLabels,
	UINT32 *Matrix_E,
	const int			width,
	const int			height,	
	const std::string		filename,
	const std::string		path)
{
	TRACE_FUNC();
#if _MSC_VER &&  USE_CUDA_MUTEX
    LARGE_INTEGER litmp;
	LONGLONG QPart1,QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// 获得初始值
	CUDA_MUTEX.Lock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	pthread_mutex_lock(&CUDA_MUTEX);
#else

#endif
	
#if 1
	Get_Nighbour_E_matrix_gpu(labels,NumLabels,Matrix_E,width,height);
#endif
#if _MSC_VER &&  USE_CUDA_MUTEX
    QueryPerformanceCounter(&litmp);	
	QPart2 = litmp.QuadPart;//获得中止值	
	dfMinus = (double)(QPart2-QPart1);	
	dfTim = dfMinus / dfFreq;// 获得对应的时间值，单位为秒
	CUDA_MUTEX.Unlock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	 pthread_mutex_unlock(&CUDA_MUTEX);
#else

#endif
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C"  void classify_SkyVerticalGround_gpu(
	double horizontal_line,
	INT32*	 Matrix_Category_Lable_host,
	double* SkyWeightArray_host,
	double* VerticalWeightArray_host,
	double* GroundWeightArray_host,
	double* SkyWeightSp_host,
	double* VerticalWeightSp_host,
	double* GroundWeightSp_host,
	int*    labels_host,
	int     Numlabels,
	int Width,
	int Height);
/*------------------------------------------------------------------------------------------*/
/**
*
*@param [out] Matrix_Category_Lable
*
*/
/*------------------------------------------------------------------------------------------*/
void classify_SkyVerticalGround_cuda(
	double horizontal_line,
	INT32*	Matrix_Category_Lable,
	double *SkyWeightArray_host,
	double *VerticalWeightArray_host,
	double *GroundWeightArray_host,
	double*  SkyWeightSp_host,
	double*  VerticalWeightSp_host,
	double*  GroundWeightSp_host,
	int*    labels,
	int     Numlabels,
	int Width,
	int Height)
{
#if _MSC_VER &&  USE_CUDA_MUTEX
	LARGE_INTEGER litmp;
	LONGLONG QPart1,QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart;// 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;// 获得初始值
	CUDA_MUTEX.Lock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	pthread_mutex_lock(&CUDA_MUTEX);
#else

#endif

#if 1
	classify_SkyVerticalGround_gpu(
		horizontal_line,
		Matrix_Category_Lable,
		SkyWeightArray_host,
		VerticalWeightArray_host,
		GroundWeightArray_host,
		SkyWeightSp_host,
		VerticalWeightSp_host,
		GroundWeightSp_host,
		labels,
		Numlabels,
		Width,
		Height);
#endif
#if _MSC_VER &&  USE_CUDA_MUTEX
	QueryPerformanceCounter(&litmp);	
	QPart2 = litmp.QuadPart;//获得中止值	
	dfMinus = (double)(QPart2-QPart1);	
	dfTim = dfMinus / dfFreq*1000;// 获得对应的时间值，单位为MS
	//dfTim = 131.77898596090682 ms
	CUDA_MUTEX.Unlock();
#elif __GNUC__ &&  USE_CUDA_MUTEX
	 pthread_mutex_unlock(&CUDA_MUTEX);
#else

#endif

}