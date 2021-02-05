#pragma once
/*-----------------------------------------*/
#include "ImageProcTopDown.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class ImageProcTopDownSVG :public ImageProcTopDown
{
    Q_OBJECT
public:
    explicit ImageProcTopDownSVG();
    ~ImageProcTopDownSVG();
public:
	QVector3D getCameraPos(const IplImage * _src);
public:
	QVector<QVector3D> getPointCloud(const IplImage * _img);

	static QVector3D toBaseCoord(
									QVector3D _pt,
									QVector3D _base,
									const float _mpp);
		
	QVector<QVector3D> Cvt2PolarCoord(QVector<QVector3D> _xy);

	QVector<QVector3D> Cvt2CartesianCoord(QVector<QVector3D> _rt);

	void PushPointAddAxisZ(
		const QVector3D& _pt,
		QVector<QVector3D>& _pts,
		const int Z);

	QVector3D cvt2CamreaCoord(const IplImage * _src, QVector3D _c);
signals:
	void sig_point_cloud(QVector<QVector3D>);
private:
	void emit_sig_point_cloud(IplImage* _src);
	void emit_sig_1_frame_air_view(
		const bool				_airView,
		QSharedPointer<QImage>	_av,
		QSharedPointer<QImage>	_src,
		const QDateTime			_time);
private:
	void ProcImageFrame(QSharedPointer<QImage> _img_p, const QDateTime & _time);
public slots :

	void ImageProc(QSharedPointer<QImage> _img_p, const QDateTime _time);
	
};
