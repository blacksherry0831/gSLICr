#include "PreProcImageSvg.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageSvg::PreProcImageSvg(QObject *parent) :QObject(parent)
{
	mSafeArea = false;
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
void PreProcImageSvg::DrawSafeArea(const bool _r)
{
	mSafeArea = _r;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageSvg::ImageProc(
	QSharedPointer<QImage> _img_ptr,
	const QDateTime _time)
{
	if (mSafeArea)
	{
		DriveAuto::DrawSafeArea(_img_ptr);
	}

	emit sig_1_frame_RGB32_ref(_img_ptr, _time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/