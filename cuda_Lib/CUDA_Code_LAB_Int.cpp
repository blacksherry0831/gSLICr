#include "CUDA_Code_LAB_Int.h"
/*------------------------------------------------------------------------------------------*/
#include <MY_SDK_LIB/TimeMeasure.hpp>
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C"
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
	const unsigned long		_f_d);

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
*/
/*------------------------------------------------------------------------------------------*/
void PerformSuperpixelSLIC_cuda_lab_Int_F(
	const int kseedsSize,
	const int m_width,
	const int m_height,

	int*				m_lvec,
	int*				m_avec,
	int*				m_bvec,
	
	int*				kseedsl,
	int*				kseedsa,
	int*				kseedsb,
	int*				kseedsx,
	int*				kseedsy,

	int*				klabels,
	const unsigned long		_f_m,
	const unsigned long		_f_d)
{
			TimeMeasure tm("Superpixel.GPU.Int");

			PerformSuperpixelSLIC_gpu_lab_host_int(
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

				klabels,
				_f_m,
				_f_d);

}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/