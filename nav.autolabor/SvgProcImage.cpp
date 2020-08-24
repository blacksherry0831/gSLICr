#include "SvgProcImage.h"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
SVG_PROC_IMAGE::SVG_PROC_IMAGE()
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
SVG_PROC_IMAGE::~SVG_PROC_IMAGE()
{
	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
bool SVG_PROC_IMAGE::IsValidQImage(const QImage& _img)
{
	if (_img.width()+_img.height()>0) {
		return true;
	}
	else
	{
		return false;
	}	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC_IMAGE::ImageProc(QImage _img, const QDateTime _time)
{

	if(this->IsValidQImage(_img)) {

		if (this->IsLatestImage(_time)) {

		ProcImageSVG(_img, _time);

					
		}
		else
		{
			
		}

	}

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
bool SVG_PROC_IMAGE::IsLatestImage(const QDateTime & _time,const int64 _ms)
{
	const qint64 ms_diff=_time.msecsTo(QDateTime::currentDateTime());
		
	if (ms_diff<_ms){
		return true;
	}else{
	//	qDebug() << ms_diff<<"ms";
	}
	
	return false;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void SVG_PROC_IMAGE::ProcImageSVG(const QImage& _img, const QDateTime& _time)
{
	QImage img_svg(_img.width(), _img.height(), _img.format());

	if (1) {
		SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(_img, img_svg);
	}else{
		img_svg = _img.copy();
	}
		
	emit sig_1_frame_bgra(img_svg,_time);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/

