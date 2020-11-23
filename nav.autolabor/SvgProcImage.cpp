#include "SvgProcImage.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
SVG_PROC_IMAGE::SVG_PROC_IMAGE()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
SVG_PROC_IMAGE::~SVG_PROC_IMAGE()
{
	
}
/*-----------------------------------------*/
/**
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
*/
/*-----------------------------------------*/
void SVG_PROC_IMAGE::ProcImageSVG(QSharedPointer<QImage> _img_p, const QDateTime & _time)
{
	QSharedPointer<QImage> img_svg = QSharedPointer<QImage>(new QImage(_img_p->width(), _img_p->height(), _img_p->format()));
	
	if (1) {
		SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(_img_p, img_svg);
	}else {
		
	}

	emit sig_org_frame_bgra(_img_p,_time);
	emit sig_out_frame_bgra(img_svg, _time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void SVG_PROC_IMAGE::ImageProc(QSharedPointer<QImage> _img_p, const QDateTime _time)
{
	if (General::IsEmptyQImage(_img_p.get())) {

		if (this->IsLatestImage(_time)) {

			ProcImageSVG(_img_p, _time);
			
		}
		else
		{

		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/

