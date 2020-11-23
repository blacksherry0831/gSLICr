#include "ImageProcTopDown.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDown::ImageProcTopDown()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDown::~ImageProcTopDown()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::init_param()
{
	this->mCalGndMode=false;
	this->mReCalGndPlane=false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector<QVector3D> ImageProcTopDown::getPointCloud(const IplImage * _img)
{
	QVector<QVector3D> pts;

	const int W = _img->width;
	const int H = _img->height;
	const int STEP = _img->widthStep;
	const int CH = _img->nChannels;
	const float mpp = this->m_imgProcAirV.MetersPerPixel();
	const int C_X = W / 2;
	const int C_Y = H-1;

	const QVector3D cam_c(C_X,C_Y,0);

	for (int xi = 0; xi < W; xi++){
		int yi;
		
		for (yi=H-2; yi >0; yi--){
					const char* c_ptr = _img->imageData+ yi*STEP+xi*CH;
					const int* i_ptr =(const int *) c_ptr ;
					const int data_t = i_ptr[0];
					if (data_t== 0xE0ff0000){
						QVector3D  pt = toCamreaCoord(QVector3D(xi, yi, 0), cam_c, mpp);
#if 0
					PushPointAddAxisZ(pt,pts,3);
#else
						pts.push_back(pt);
#endif // 0

						
						
						break;

					}
		}
#if 0
		if (yi == 0) {
			QVector3D  pt=	toCamreaCoord(QVector3D(xi,yi,0), cam_c,mpp);
			pts.push_back(pt);
		}
#endif // 0


	}
 
	return pts;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDown::toCamreaCoord(QVector3D _pt, QVector3D _base, const float _mpp)
{
	const float ymi = (_base.x() - _pt.x())*_mpp;
	const float xmi = (_base.y() - _pt.y())*_mpp;
	const QVector3D  pt(xmi, ymi, 0);
	return pt;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::PushPointAddAxisZ(
	const QVector3D & _pt,
	QVector<QVector3D>& _pts,
	const int Z_range)
{
	const float X = _pt.x();
	const float Y = _pt.y();
	const float Z = _pt.z();
	const float Z_b  = Z_range / 2;
	const float STEP = 0.1F;

	for (float zi =0; zi < Z_b; zi+=STEP){
		const QVector3D pt(X,Y,Z+zi);
		_pts.push_back(pt);
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::PushPoint(const QVector3D & _pt, QVector<QVector3D>& _pts)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector<QVector3D> ImageProcTopDown::Cvt2PolarCoord(QVector<QVector3D> _xy)
{
	const int SCALE = 5;
	const int RANGE = 360;
	
	QVector<QVector3D>  polar_t(RANGE *SCALE,QVector3D(0,0,0));

	for each (QVector3D p in _xy)
	{
		Q_ASSERT(p.y() != 0 || p.x() != 0);
		const float rho   = std::sqrtf(p.x()*p.x() + p.y()*p.y());
		const float theta = std::atan2f(p.y(), p.x()); 
		//(-pi,pi]
		const int   thIdx = qFloor(SCALE*(theta+PI) *180.0/PI);
		const int   rho_old = polar_t.at(thIdx).x();

		if (rho_old == 0) {
			polar_t[thIdx].setX(rho);
			polar_t[thIdx].setY(theta);
		}else if (rho_old>rho) {
			polar_t[thIdx].setX(rho);
			polar_t[thIdx].setY(theta);
		}else{
			Q_ASSERT(rho_old<rho);
		}


	}

	return  polar_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector<QVector3D> ImageProcTopDown::Cvt2CartesianCoord(QVector<QVector3D> _rt)
{
	QVector<QVector3D>  cartes_t;
	
	for each (QVector3D p in _rt)
	{
		const float   rho    = p.x();
		const float   theta  = p.y();

		if (rho>0){
			const float   x = rho * cosf(theta);
			const float   y = rho * sinf(theta);
			cartes_t.push_back(QVector3D(x,y,0));
		}
		
	}
	
	return cartes_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::emit_sig_point_cloud(IplImage * _src)
{
#if 1
	/*clock_t start, stop;
	double duration;
	start = clock();
	{*/
	QVector<QVector3D> pts = this->getPointCloud(_src);

	QVector<QVector3D> polar_pts = this->Cvt2PolarCoord(pts);
	pts = this->Cvt2CartesianCoord(polar_pts);

	emit sig_point_cloud(pts);
	/*}
	stop = clock();
	duration = ((double)(stop - start)) / CLK_TCK;
	start = stop;*/
#endif 
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::ImageProc(
	QSharedPointer<QImage> _img_p,
	const QDateTime _t)
{
	if (General::IsEmptyQImage(_img_p)) {

		if (General::IsLatestImage(_t, 1000)) {

			ProcImageFrame(_img_p, _t);
		
		}else {
			qDebug() << "Calibration time out" << endl;
		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::ProcImageFrame(
	QSharedPointer<QImage> _img_p,
	const QDateTime & _time)
{
	QSharedPointer<QImage> bird_p = QSharedPointer<QImage>(new QImage(_img_p->width(),_img_p->height(),_img_p->format()));

	IplImage* img_src_t = createImageHeader(_img_p);
	IplImage* img_dst_t = createImageHeader(bird_p);
	{
#if 1
		this->m_imgProcAirV.initHomography(img_src_t);
		this->m_imgProcAirV.generateHomography(img_src_t);
		bool IsBirdCvt=this->m_imgProcAirV.BirdsImage(img_src_t, img_dst_t);

		if (IsBirdCvt) {
			emit sig_1_frame_bgra_ref(bird_p, _time);
		}else{
			emit sig_1_frame_bgra_ref(_img_p, _time);
		}
		this->emit_sig_point_cloud(img_dst_t);
#endif // 1		
	}
	cvReleaseImageHeader(&img_src_t);
	cvReleaseImageHeader(&img_dst_t);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setBoardSize_W(const int _w)
{
	this->m_imgProcAirV.setBoardSize_W(_w);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setBoardSize_H(const int _h)
{
	this->m_imgProcAirV.setBoardSize_H(_h);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setDstBoard2Camera(const double _dst)
{
	this->m_imgProcAirV.setDstBoard2Camera(_dst);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setSquareSize(const double _sz)
{
	this->m_imgProcAirV.setCellSize(_sz);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setMapSize(const double _sz)
{
	this->m_imgProcAirV.setCellPixel(_sz);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setMapSize(const QString _sz)
{
	this->setMapSize(_sz.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setCalGndMode(bool _m)
{
	this->mCalGndMode=_m;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setReCalGndPlane(bool _m)
{
	this->mReCalGndPlane = _m;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::reCalGndPlane()
{
	this->setReCalGndPlane(true);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage * ImageProcTopDown::createImageHeader(QSharedPointer<QImage> _img_p)
{
	CvSize img_sz_t = cvSize(_img_p->width(), _img_p->height());
	const uchar* data_t = _img_p->bits();
	const int step_t = _img_p->bytesPerLine();
	Q_ASSERT(step_t % 4 == 0);
	IplImage* img_t = cvCreateImageHeader(img_sz_t, IPL_DEPTH_8U, 4);
	cvSetData(img_t, (void*)data_t, step_t);
	return img_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/