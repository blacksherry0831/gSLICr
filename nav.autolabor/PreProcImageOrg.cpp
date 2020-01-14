#include "PreProcImageOrg.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageOrg::PreProcImageOrg(QObject *parent) :QObject(parent)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
PreProcImageOrg::~PreProcImageOrg()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::SetResize(const int _w, const int _h)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void PreProcImageOrg::ImageProc(QImage _img, const QDateTime _time)
{
	if (mSafeArea)
	{
		DriveAuto::DrawSafeArea(_img);
	}

	emit sig_1_frame_bgra(_img, _time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/