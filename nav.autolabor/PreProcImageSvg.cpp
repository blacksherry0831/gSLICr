#include "PreProcImageSvg.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageSvg::PreProcImageSvg(QObject *parent) :QObject(parent)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageSvg::~PreProcImageSvg()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageSvg::SetResize(const int _w, const int _h)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageSvg::ImageProc(QImage _img, const QDateTime _time)
{
	if (mSafeArea)
	{
		DriveAuto::DrawSafeArea(_img);
	}

	emit sig_1_frame_bgra(_img,_time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/