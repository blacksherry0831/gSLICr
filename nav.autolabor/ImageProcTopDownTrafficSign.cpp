#include "ImageProcTopDownTrafficSign.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDownTrafficSign::ImageProcTopDownTrafficSign()
{
	this->initTrafficSignTemplete();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDownTrafficSign::~ImageProcTopDownTrafficSign()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::ImageProc(
	QSharedPointer<QImage> _img_p,
	const QDateTime _t)
{
	if (General::IsEmptyQImage(_img_p)) {

		if (General::IsLatestImage(_t, 1000)) {

			ProcImageFrame(_img_p, _t);

		}
		else {
			qDebug() << "Calibration time out" << endl;
		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::initTrafficSignTemplete()
{
	const std::string path = "X:\\ImageDataBase\\TrafficSignSample\\TrafficSignTemplate";
	mTS_Param.setTempletePath(path);

	mTS_Temp.setTrafficSignParam(&mTS_Param);

	mTS_Properties = mTS_Temp.TempleteLoadHu();

	mTS_Temp.TempleteSaveHu(mTS_Properties);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::ProcImageFrame(
	QSharedPointer<QImage> _img_p,
	const QDateTime & _time)
{
	QSharedPointer<QImage> bird_p = QSharedPointer<QImage>(new QImage(_img_p->width(), _img_p->height(), _img_p->format()));

	IplImage* img_src_t = createImageHeader(_img_p);
	IplImage* img_dst_t = createImageHeader(bird_p);
	{
		const bool IsBirdCvt = airViewBirdsImg(img_src_t, img_dst_t);

		if (IsBirdCvt) {		
			trafficSign(img_dst_t);
		}

		SaveQImageOnce(bird_p);
		
		this->emit_sig_1_frame_air_view(IsBirdCvt, bird_p, _img_p, _time);		
			
	}
	cvReleaseImageHeader(&img_src_t);
	cvReleaseImageHeader(&img_dst_t);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDownTrafficSign::getCameraPos(const IplImage * _src)
{
	const int W = _src->width;
	const int H = _src->height;
	const int C_X = W / 2;
	const int C_Y = H - 1;
	const QVector3D cam_c(C_X, C_Y, 0);
	return cam_c;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDownTrafficSign::cvt2CamreaCoord(const IplImage * _src, QVector3D _c)
{
	const QVector3D cam_c=getCameraPos(_src);
	const float mpp = airViewMetersPerPixel();
	const QVector3D  pt = toBaseCoord(QVector3D(_c.x(), _c.y(), 0), cam_c, mpp);
	return pt;
}
/*-----------------------------------------*/
/**
*角度制
*/
/*-----------------------------------------*/
double ImageProcTopDownTrafficSign::cvt2CamreaAngle(const double _a)
{
	return -M_PI/2.0-_a;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector<QVector3D> ImageProcTopDownTrafficSign::cvtPointCloud2CamreaCoord(
	const IplImage * _src,
	std::vector<cv::Point> _pts)
{
	QVector<QVector3D> pts;

	const QVector3D cam_c = getCameraPos(_src);
	const float mpp = airViewMetersPerPixel();

	for each (auto v in _pts){
		const QVector3D  pt = toBaseCoord(QVector3D(v.x, v.y, 0), cam_c, mpp);
		pts.push_back(pt);
	}

	return pts;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector4D ImageProcTopDownTrafficSign::cvtYaw2Quater(const double _y)
{
	Q_ASSERT(std::abs(_y)<=2*M_PI+1E-3);

	QVector4D  quater;
	quater.setX(0);
	quater.setY(0 );
	quater.setZ(sin(_y / 2));
	quater.setW(cos(_y / 2));
	return quater;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::trafficSign(IplImage* _src)
{
	mTS_tsm.CloneImage(_src);
	mTS_tsm.cutTempleteArea(mTS_Param.getBlockSize());

	std::vector<TrafficSignResult>  results = mTS_tsm.MatchHu(mTS_Properties,0);
	
	for each(auto tsr in results){

		tsr.DrawArrow(_src);
				
		this->emit_pose(_src,&tsr);
		this->emit_pointcloud(_src, &tsr);


	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDownTrafficSign::toBaseCoord(
	QVector3D _pt,
	QVector3D _base,
	const float _mpp)
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
void ImageProcTopDownTrafficSign::emit_sig_1_frame_air_view(
	const bool _airView,
	QSharedPointer<QImage> _av,
	QSharedPointer<QImage> _src,
	const QDateTime _time)
{
	if (_airView) {
		emit sig_1_frame_bgra_ref(_av, _time);
	}
	else {
		emit sig_1_frame_bgra_ref(_src, _time);
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::emit_pose_position_orientation(
	QString	_color,
	const QVector3D _c,
	const double  _a)
{
	const QVector4D	quater= cvtYaw2Quater(_a);
	emit sig_pose_position_orientation(_color,_c, quater);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::emit_pose(
	const IplImage* _src,
	const TrafficSignResult* _r)
{
	const CvPoint	center	= _r->getRectCenter();
	const double	angle	= _r->getAngle();
	const QString	color	= QString::fromStdString(_r->getColorStr());
	const QVector3D		cam_pt = cvt2CamreaCoord(_src, QVector3D(center.x, center.y, 0));
	const double		cam_angle = cvt2CamreaAngle(angle);

	this->emit_pose_position_orientation(color,cam_pt, cam_angle);


}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownTrafficSign::emit_pointcloud(
	const IplImage * _src,
	const TrafficSignResult * _r)
{
	std::vector<cv::Point> pts= _r->BinImgPoints_ImgCoord();
	QVector<QVector3D> pts3d=cvtPointCloud2CamreaCoord(_src,pts);
	emit sig_point_cloud(pts3d);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/