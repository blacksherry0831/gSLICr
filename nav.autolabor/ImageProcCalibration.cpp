#include "ImageProcCalibration.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcCalibration::ImageProcCalibration()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcCalibration::~ImageProcCalibration()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImageProcCalibration::IsValidQImage(const QImage& _img)
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
void ImageProcCalibration::ImageProc(QImage _img, const QDateTime _time)
{

	if(this->IsValidQImage(_img)) {

		if (this->IsLatestImage(_time,1000)) {
					
			ProcImageFrame01(_img, _time);
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
bool ImageProcCalibration::IsLatestImage(const QDateTime & _time,const int64 _ms)
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
void ImageProcCalibration::ProcImageFrame(const QImage& _img, const QDateTime& _time)
{
	
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcCalibration::ProcImageFrame01(const QImage & _img, const QDateTime & _time)
{
	QImage  qimg=_img.copy();
	CvSize img_sz_t = cvSize(qimg.width(), qimg.height());
	const uchar* data_t = qimg.bits();
	const int step_t = qimg.bytesPerLine();
	IplImage* img_t = cvCreateImageHeader(img_sz_t, IPL_DEPTH_8U, 4);
	cvSetData(img_t,(void*) data_t, step_t);
	{
		m_imgProcCal.IncFrame();
		if (m_imgProcCal.IsDetectFrame()) {
			int find;
			m_imgProcCal.Init_Intrinsics_Distortion(img_t);
			m_imgProcCal.Calculate_Intrinsics_Distortion(img_t,find);
			m_imgProcCal.DrawProgressBar(img_t);

			m_imgProcCal.calibration_image(img_t);

			emit sig_1_frame_bgra(qimg, _time);
						
		}

		

	}
	cvReleaseImageHeader(&img_t);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/