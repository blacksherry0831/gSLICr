#ifndef _CUDA_CODE_LAB_INT_H
#define _CUDA_CODE_LAB_INT_H
/***************************************/
#include <cpp_def_type.h>
/***************************************/

#ifdef __cplusplus
extern "C" {
#endif 
/*-------------------------------------------------------------*/
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
		const unsigned long		_f_d);
/*-------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////
#endif



