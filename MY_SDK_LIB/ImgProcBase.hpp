 #pragma once
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
#include "opencv_stl.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class ImgProcBase
{
public:
	ImgProcBase(void);
	~ImgProcBase(void);
public:
	static int  RECT_isEffective(const CvRect * _rect);
	static void RECT_adjWidth4(CvRect * _rect);
public:
public:
	static const CvScalar BLACK;
	static const CvScalar BLACK_RGB;
	static const CvScalar WHITE_RGB;





};