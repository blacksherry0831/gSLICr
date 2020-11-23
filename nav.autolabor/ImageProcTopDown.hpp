#pragma once
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QQueue>
#include <QMetaType>
/*-----------------------------------------*/
#include "SGV/SGV_Method.h"
/*-----------------------------------------*/
#include "MY_SDK_LIB/ImgProcAirView.hpp"
/*-----------------------------------------*/
#include "OPENCV_QT_SDK_LIB\OpencvQtBase.h"
/*-----------------------------------------*/
#include "QT_SDK_LIB/QImage_Q.hpp"
/*-----------------------------------------*/
#include "General.hpp"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
class ImageProcTopDown :public QObject
{
    Q_OBJECT
public:
    explicit ImageProcTopDown();
    ~ImageProcTopDown();
private:
	bool mCalGndMode;
	bool mReCalGndPlane;
public:
	void init_param();
private:
	QVector<QVector3D> getPointCloud(const IplImage* _img);
	
	QVector3D toCamreaCoord(
		QVector3D _pt,
		QVector3D _base,
		const float _mpp);
	
	void PushPointAddAxisZ(
		const QVector3D& _pt,
		QVector<QVector3D>& _pts,
		const int Z);
	void PushPoint(
		const QVector3D& _pt,
		QVector<QVector3D>& _pts);

	  QVector<QVector3D> Cvt2PolarCoord(QVector<QVector3D> _xy);
	  QVector<QVector3D> Cvt2CartesianCoord(QVector<QVector3D> _rt);


private:
	void emit_sig_point_cloud(IplImage* _src);
public:
	
signals:
	
	void sig_1_frame_bgra_ref(QSharedPointer<QImage>, const QDateTime);
	void sig_point_cloud(QVector<QVector3D>);
public slots :
	
	void ImageProc(QSharedPointer<QImage> _img_p, const QDateTime _time);
private:
	ImgProcAirView m_imgProcAirV;
	
	void ProcImageFrame(
		QSharedPointer<QImage> _img_p,
		const QDateTime& _time);

public slots :
	void setBoardSize_W(const int _w);
	void setBoardSize_H(const int _h);
	void setDstBoard2Camera(const double _dst);
	void setSquareSize(const double _sz);
	void setMapSize(const double _sz);
	void setMapSize(const QString _sz);
public:
	void setCalGndMode(bool _m);
	void setReCalGndPlane(bool _m);
	void reCalGndPlane();

public:
	static	IplImage * createImageHeader(QSharedPointer<QImage> _img_p);

	
};

Q_DECLARE_METATYPE(QVector<QVector3D>);