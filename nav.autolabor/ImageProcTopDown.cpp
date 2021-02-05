#include "ImageProcTopDown.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDown::ImageProcTopDown()
{
	this->init_param();
	this->InitImageSavePath();
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
	this->mSaveImageOnce = false;
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::InitImageSavePath()
{
	const QString qexeFullPath = QCoreApplication::applicationDirPath();

	const QString PathImageSave = qexeFullPath + "/" + "ImageTopDown" + "/";

	if (QBase::CreateDir(PathImageSave)) {
		this->mPaths = PathImageSave;
	}
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
void ImageProcTopDown::setAirViewTf(QSharedPointer<ImgProcAirView> _av)
{
	this->mAirViewTf = _av;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImageProcTopDown::airViewBirdsImg(IplImage * _src, IplImage * _dst)
{
	this->mAirViewTf->initHomography(_src);
	this->mAirViewTf->generateHomography(_src);
	const bool IsBirdCvt = this->mAirViewTf->BirdsImage(_src, _dst);
	return IsBirdCvt;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
float ImageProcTopDown::airViewMetersPerPixel()
{
	return this->mAirViewTf->MetersPerPixel();
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
		const bool IsBirdCvt = airViewBirdsImg(img_src_t, img_dst_t);

		SaveQImageOnce(bird_p);

		if (IsBirdCvt) {
			emit sig_1_frame_bgra_ref(bird_p, _time);
		}else{
			emit sig_1_frame_bgra_ref(_img_p, _time);
		}
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
	this->mAirViewTf->setBoardSize_W(_w);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setBoardSize_H(const int _h)
{
	this->mAirViewTf->setBoardSize_H(_h);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setDstBoard2Camera(const double _dst)
{
	this->mAirViewTf->setDstBoard2Camera(_dst);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setSquareSize(const double _sz)
{
	this->mAirViewTf->setCellSize(_sz);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setMapSize(const double _sz)
{
	this->mAirViewTf->setCellPixel(_sz);
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
	this->mAirViewTf->setCalGndMode(_m);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::setReCalGndPlane(bool _c)
{
	this->mAirViewTf->setCalibrate(_c);
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
void ImageProcTopDown::set_X_P0(const double _v)
{
	this->mAirViewTf->set_X_P0(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P1(const double _v)
{
	this->mAirViewTf->set_X_P1(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P2(const double _v)
{
	this->mAirViewTf->set_X_P2(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P3(const double _v)
{
	this->mAirViewTf->set_X_P3(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P0(const double _v)
{
	this->mAirViewTf->set_Y_P0(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P1(const double _v)
{
	this->mAirViewTf->set_Y_P1(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P2(const double _v)
{
	this->mAirViewTf->set_Y_P2(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P3(const double _v)
{
	this->mAirViewTf->set_Y_P3(_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P0(const QString & _v)
{
	this->set_X_P0(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P1(const QString & _v)
{
	this->set_X_P1(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P2(const QString & _v)
{
	this->set_X_P2(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_X_P3(const QString & _v)
{
	this->set_X_P3(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P0(const QString & _v)
{
	this->set_Y_P0(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P1(const QString & _v)
{
	this->set_Y_P1(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P2(const QString & _v)
{
	this->set_Y_P2(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::set_Y_P3(const QString & _v)
{
	this->set_Y_P3(_v.toDouble());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::SetSaveImageOnce()
{
	SetSaveImageOnce(true);
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
void ImageProcTopDown::SetSaveImageOnce(const bool _s)
{
	this->mSaveImageOnce = _s;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void  ImageProcTopDown::SaveQImage(const QSharedPointer<QImage> _img)
{
	qint64 t = QDateTime::currentDateTime().toMSecsSinceEpoch();
	QString name = QString("%1").arg(t) + ".png";

	if (!(_img)->save(mPaths + name, "png")) {
		qDebug() << "picture save failed" << endl;
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDown::SaveQImageOnce(const QSharedPointer<QImage> _img)
{
	if (mSaveImageOnce)
	{
		SaveQImage(_img);
		mSaveImageOnce = false;
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/