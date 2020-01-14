#include "SVG_PROC.h"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
SVG_PROC::SVG_PROC()
{
	M_THREAD_RUN = true;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
SVG_PROC::~SVG_PROC()
{
	M_THREAD_RUN = false;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::startServer()
{
	M_THREAD_RUN = true;
	this->start();
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::closeServer()
{
	M_THREAD_RUN = false;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
bool SVG_PROC::IsValidQImage(const QImage _img)
{
	if (_img.width()+_img.height()==0) {
		return false;
	}
	else
	{
		return true;
	}

	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::SetQImage(const QImage _img)
{
	mImgQ.setQImage(_img);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::run()
{
	while (M_THREAD_RUN)
	{
		run_thread_work();
	}
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::run_thread_work()
{
	const int SZ=mImgQ.QueueSize();
	
	QImage img_t;
		
	if (SZ==0){
		msleep(1);
	}else if (SZ>0) {
		
		img_t = mImgQ.getQImage();
		if (IsValidQImage(img_t)) {
			ProcImage(img_t);
		}
		mImgQ.clear();

	}else{
		Q_ASSERT(0);
	}

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::ProcImage(const QImage _img)
{
	ProcImageSVG(_img);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC::ProcImageSVG(const QImage _img)
{
	QImage img_svg(_img.width(), _img.height(), _img.format());

	SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(_img, img_svg);

	emit sig_1_frame_svg_bgra(img_svg);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
