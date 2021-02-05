#include "ImageProcTopDownSVG.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDownSVG::ImageProcTopDownSVG()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImageProcTopDownSVG::~ImageProcTopDownSVG()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDownSVG::getCameraPos(const IplImage * _src)
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
QVector<QVector3D> ImageProcTopDownSVG::getPointCloud(const IplImage * _img)
{
	const QVector3D cam_c = getCameraPos(_img);
	const float mpp = airViewMetersPerPixel();
	

	QVector<QVector3D> pts;

	const int W = _img->width;
	const int H = _img->height;
	const int STEP = _img->widthStep;
	const int CH = _img->nChannels;
		
	for (int xi = 0; xi < W; xi++) {
				int yi;
				for (yi = H - 2; yi >0; yi--) {
							const char* c_ptr = _img->imageData + yi*STEP + xi*CH;
							const int* i_ptr = (const int *)c_ptr;
							const int data_t = i_ptr[0];
							if (data_t == 0xE0ff0000) {
										const QVector3D  pt = toBaseCoord(QVector3D(xi, yi, 0), cam_c, mpp);
										pts.push_back(pt);				
										break;
							}
				}
	}
	return pts;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDownSVG::toBaseCoord(
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
QVector<QVector3D> ImageProcTopDownSVG::Cvt2PolarCoord(QVector<QVector3D> _xy)
{
	const int SCALE = 5;
	const int RANGE = 360;

	QVector<QVector3D>  polar_t(RANGE *SCALE, QVector3D(0, 0, 0));

	for each (QVector3D p in _xy)
	{
		Q_ASSERT(p.y() != 0 || p.x() != 0);
		const float rho = std::sqrtf(p.x()*p.x() + p.y()*p.y());
		const float theta = std::atan2f(p.y(), p.x());
		//(-pi,pi]
		const int   thIdx = qFloor(SCALE*(theta + PI) *180.0 / PI);
		const int   rho_old = polar_t.at(thIdx).x();

		if (rho_old == 0) {
			polar_t[thIdx].setX(rho);
			polar_t[thIdx].setY(theta);
		}
		else {

			if (rho_old>rho) {
				polar_t[thIdx].setX(rho);
				polar_t[thIdx].setY(theta);
			}
			else {
				Q_ASSERT(rho_old <= rho);
			}

		}




	}

	return  polar_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector<QVector3D> ImageProcTopDownSVG::Cvt2CartesianCoord(QVector<QVector3D> _rt)
{
	QVector<QVector3D>  cartes_t;

	for each (QVector3D p in _rt)
	{
		const float   rho = p.x();
		const float   theta = p.y();

		if (rho>0) {
			const float   x = rho * cosf(theta);
			const float   y = rho * sinf(theta);
			cartes_t.push_back(QVector3D(x, y, 0));
		}

	}

	return cartes_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImageProcTopDownSVG::emit_sig_point_cloud(IplImage * _src)
{
#if 1
	/*clock_t start, stop;
	double duration;
	start = clock();
	{*/
	QVector<QVector3D> pts = this->getPointCloud(_src);
	QVector<QVector3D> polar_pts = this->Cvt2PolarCoord(pts);
	QVector<QVector3D> pts_short = this->Cvt2CartesianCoord(polar_pts);
	emit sig_point_cloud(pts_short);
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
void ImageProcTopDownSVG::emit_sig_1_frame_air_view(
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
void ImageProcTopDownSVG::ImageProc(
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
void ImageProcTopDownSVG::ProcImageFrame(
	QSharedPointer<QImage> _img_p,
	const QDateTime & _time)
{
	QSharedPointer<QImage> bird_p = QSharedPointer<QImage>(new QImage(_img_p->width(), _img_p->height(), _img_p->format()));

	IplImage* img_src_t = createImageHeader(_img_p);
	IplImage* img_dst_t = createImageHeader(bird_p);
	{
#if 1
		const bool IsBirdCvt = airViewBirdsImg(img_src_t,img_dst_t);
	
		SaveQImageOnce(bird_p);

		this->emit_sig_1_frame_air_view(IsBirdCvt, bird_p, _img_p, _time);
				
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
void ImageProcTopDownSVG::PushPointAddAxisZ(
	const QVector3D & _pt,
	QVector<QVector3D>& _pts,
	const int Z_range)
{
	const float X = _pt.x();
	const float Y = _pt.y();
	const float Z = _pt.z();
	const float Z_b = Z_range / 2;
	const float STEP = 0.1F;

	for (float zi = 0; zi < Z_b; zi += STEP) {
		const QVector3D pt(X, Y, Z + zi);
		_pts.push_back(pt);
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
QVector3D ImageProcTopDownSVG::cvt2CamreaCoord(const IplImage * _src, QVector3D _c)
{
	
	const QVector3D cam_c=getCameraPos(_src);
	const float mpp = airViewMetersPerPixel();
	const QVector3D  pt = toBaseCoord(_c, cam_c, mpp);
	return pt;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/