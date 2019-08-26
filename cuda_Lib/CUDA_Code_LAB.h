#ifndef _CUDA_CODE_LAB_H
#define _CUDA_CODE_LAB_H
/////////////////////////////////////////
/***************************************/
#include <cpp_def_type.h>
/***************************************/

#ifdef __cplusplus
extern "C" {
#endif 
/*-------------------------------------------------------------*/
void  PerformSuperpixelSLIC_cuda_lab(
	
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
	
	const double		_invwt);

/*-------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////
#endif



