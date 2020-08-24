#pragma once
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QQueue>
/*-----------------------------------------*/
#include "SGV/SGV_Method.h"
/*-----------------------------------------*/
#include "MY_SDK_LIB/ImgProcAirView.hpp"
/*-----------------------------------------*/
#include "OPENCV_QT_SDK_LIB\OpencvQtBase.h"
/*-----------------------------------------*/
#include "QT_SDK_LIB/QImage_Q.hpp"
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
	QVector<QVector3D> getPointCloud(const IplImage* _img);
	
	QVector3D toCamreaCoord(
		QVector3D _pt,
		QVector3D _base,
		const float _mpp);
	
	void PushPointAddAxisZ(
		const QVector3D& _pt,
		QVector<QVector3D>& _pts,
		const int Z);
private:
	bool mCalGndMode;
	bool mReCalGndPlane;
public:
	bool IsValidQImage(const QImage& _img);
public:
	static bool IsLatestImage(const QDateTime& _time, const int64 _ms=100);
signals:
	void sig_1_frame_bgra(QImage, QDateTime);
	void sig_point_cloud(QVector<QVector3D>);
public slots :
	void ImageProc(QImage _img, const QDateTime _time);
private:
	ImgProcAirView m_imgProcAirV;
	void ProcImageFrame(const QImage& _img, const QDateTime& _time);
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

	
};
