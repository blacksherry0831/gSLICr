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
	const int wOrg = _img_p->width();
	const int hOrg = _img_p->height();
	const int S = 2;
	const int W = wOrg / S;
	const int H = hOrg / S;
	const QImage::Format F = _img_p->format();
		 	
	QSharedPointer<QImage> img_min_p = QSharedPointer<QImage>(new QImage(_img_p->scaled(W,H)));
	QSharedPointer<QImage> img_min_svg = QSharedPointer<QImage>(new QImage(W, H,F));

	if (1) {
		SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(img_min_p, img_min_svg);
	}else {
		
	}
	QSharedPointer<QImage> img_svg = QSharedPointer<QImage>(new QImage(img_min_svg->scaled(wOrg, hOrg)));

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

