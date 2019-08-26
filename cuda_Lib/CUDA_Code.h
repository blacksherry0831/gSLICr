#ifndef _CUDA_CODE
#define _CUDA_CODE
/***************************************/
#include "cpp_basic.h"
/***************************************/
#include "cpp_def_type.h"
/***************************************/
#include "cpp_def_debug.h"
/***************************************/
#ifdef __cplusplus
extern "C" {
#endif 
/*-------------------------------------------------------------*/
void  PerformSuperpixelSLIC_cuda(
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
	double*				kseedsl,
	double*				kseedsa,
	double*				kseedsb,
	double*				kseedsx,
	double*				kseedsy,
	int*				klabels,
	const int			STEP,
	double*				edgemag,
	const double		M);
void  PerformSuperpixelSLIC_ThetaMLXY_cuda(
	float alpha,
	float betta,
	float gama,
	float fai,
	const int kseedsSize,
	const int m_width,
	const int m_height,
	double*     sita_n,
	double*     m_n,
	double*     L_n,
	double*     X_n,
	double*     Y_n,
	double*     kseedsTheta,
	double*     kseedsM,
	double*     kseedsL,
	double*     kseedsX,
	double*     kseedsY,
	int*	    klabels,
	const int	STEP);
/*-------------------------------------------------------------*/
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
	int*				klabels);
/*-------------------------------------------------------------*/
void Get_Nighbour_E_matrix_cuda(
	int*					labels,
	const  int		NumLabels,
	UINT32 *Matrix_E,
	const int			width,
	const int			height,	
	const std::string		filename,
	const std::string		path);
/*-------------------------------------------------------------*/
void DrawContoursAroundSegments_cuda(
	unsigned int*			ubuff,
	int*					labels,
	const int				width,
	const int				height,
	const unsigned int		color );
/*-------------------------------------------------------------*/
void HarrTransformLet_MatrixSub_cuda(
	unsigned char *matrixA, 
	unsigned char *matrixB, 
	int height, 
	int width, 
	unsigned char *result);
/*-------------------------------------------------------------*/
void classify_SkyVerticalGround_cuda(
	double horizontal_line,
	INT32*	Matrix_Category_Lable,
	double* SkyWeightArray_host,
	double* VerticalWeightArray_host,
	double* GroundWeightArray_host,
	double* SkyWeightSp_host,
    double* VerticalWeightSp_host,
    double* GroundWeightSp_host,
	int*    labels,
	int     Numlabels,
	int Width,
	int Height);
	/*-------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

////////////////////////////////////////////////
#endif



