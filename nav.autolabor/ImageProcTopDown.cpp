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
QVector<QVector3D> ImageProcTopDown::getPointCloud(const IplImage * _img)
{
	QVector<QVector3D> pts;

	const int W = _img->width;
	const int H = _img->height;
	const int STEP = _img->widthStep;
	const int CH = _img->nChannels;
	const float mpp = this->m_imgProcAirV.MetersPerPixel();
	const int C_X = W / 2;
	const int C_Y = H;

	const QVector3D cam_c(C_X,C_Y,0);

	for (int xi = 0; xi < W; xi++){
		int yi;
		
		for (yi=H-1; yi >0; yi--){
					const char* c_ptr = _img->imageData+ yi*STEP+xi*CH;
					const int* i_ptr =(const int *) c_ptr ;
					const int data_t = i_ptr[0];
					if (data_t== 0xE0ff0000){
						QVector3D  pt = toCamreaCoord(QVector3D(xi, yi, 0), cam_c, mpp);
						PushPointAddAxisZ(pt,pts,3);
						break;

					}
		}
#if 1
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
	const float STEP = 0.1;

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
bool ImageProcTopDown::IsValidQImage(const QImage& _img)
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
*/
/*-----------------------------------------*/
void ImageProcTopDown::ImageProc(QImage _img, const QDateTime _time)
{

	if(this->IsValidQImage(_img)) {

		if (this->IsLatestImage(_time,1000)) {
					
			ProcImageFrame(_img, _time);
		}
		else
		{
			qDebug() << "Calibration time out" << endl;
		}

	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImageProcTopDown::IsLatestImage(const QDateTime & _time,const int64 _ms)
{
	const qint64 ms_diff=_time.msecsTo(QDateTime::currentDateTime());
		
	if (ms_diff<_ms){
		return true;
	}else{
		qDebug() << ms_diff<<"ms";
	}
	
	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::ProcImageFrame(const QImage& _img, const QDateTime& _time)
{
	QImage  qimg = _img.copy();
	CvSize img_sz_t = cvSize(qimg.width(), qimg.height());
	const uchar* data_t = qimg.bits();
	const int step_t = qimg.bytesPerLine();
	IplImage* img_t = cvCreateImageHeader(img_sz_t, IPL_DEPTH_8U, 4);
	cvSetData(img_t, (void*)data_t, step_t);
	{

		this->m_imgProcAirV.initHomography(img_t);
		this->m_imgProcAirV.generateHomography(img_t);
		this->m_imgProcAirV.BirdsImage(img_t);
		emit sig_1_frame_bgra(qimg, _time);

		QVector<QVector3D> pts=this->getPointCloud(img_t);

		emit sig_point_cloud(pts);
	}
	cvReleaseImageHeader(&img_t);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/