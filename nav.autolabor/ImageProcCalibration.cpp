#include "ImageProcCalibration.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcCalibration::ImageProcCalibration()
{
	this->mIsImageProc = false;
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
IplImage * ImageProcCalibration::createImageHeader(QSharedPointer<QImage> _img_p)
{
	CvSize img_sz_t = cvSize(_img_p->width(), _img_p->height());
	const uchar* data_t = _img_p->bits();
	const int step_t = _img_p->bytesPerLine();
	IplImage* img_t = cvCreateImageHeader(img_sz_t, IPL_DEPTH_8U, 4);
	cvSetData(img_t, (void*)data_t, step_t);
	return img_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcCalibration::ProcImageFrame(
	QSharedPointer<QImage> _img_p,
	const QDateTime& _time)
{
	if (this->mIsImageProc) {
				
		IplImage* img_t = createImageHeader(_img_p);
		{
			int find=0;
			m_imgProcCal.InitStorage(img_t);


			m_imgProcCal.IncFrame();
			if (m_imgProcCal.IsDetectFrame()) {				
				m_imgProcCal.Calculate_Intrinsics_Distortion(img_t, find);
				m_imgProcCal.DrawProgressBar(img_t);
				m_imgProcCal.calibration_image(img_t);
				emit sig_1_frame_bgra_ref(_img_p, _time);
			}
		}
		cvReleaseImageHeader(&img_t);

	}
	else {
		emit sig_1_frame_bgra_ref(_img_p, _time);
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcCalibration::ProcImageFrameNot(QSharedPointer<QImage> _img_p, const QDateTime & _time)
{
	emit sig_1_frame_bgra_ref(_img_p, _time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcCalibration::ImageProc(
	QSharedPointer<QImage> _img_p,
	const QDateTime _t)
{
	if (General::IsEmptyQImage(_img_p)) {
		if (General::IsLatestImage(_t, 1000)) {

#if 0
			ProcImageFrame(_img_p, _t);
#else
			ProcImageFrameNot(_img_p, _t);
#endif // 0

		}
		else {
			//qDebug() << "Calibration time out" << endl;
		}
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcCalibration::setImageProc(bool _f)
{
	this->mIsImageProc = _f;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/