#include "ImgProcBase.hpp"
/*-----------------------------------------*/
const CvScalar  ImgProcBase::BLACK = cvScalar(0);
const CvScalar  ImgProcBase::BLACK_RGB = cvScalar(0);
const CvScalar  ImgProcBase::WHITE_RGB = cvScalar(255, 255, 255);
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcBase::ImgProcBase(void)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcBase::~ImgProcBase(void)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcBase::RECT_isEffective(const CvRect * _rect)
{

	if ((_rect->x >= 0) &&
		(_rect->y >= 0) &&
		(_rect->width>0) &&
		(_rect->height>0)) {

		return TRUE;

	}

	return FALSE;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcBase::RECT_adjWidth4(CvRect* _rect)
{
	while (_rect->x % 4 != 0) _rect->x++;

	while (_rect->width % 4 != 0) _rect->width--;

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/