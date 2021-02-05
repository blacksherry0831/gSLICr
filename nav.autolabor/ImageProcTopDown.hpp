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
#include "QT_SDK_LIB/QBase.h"
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
	QString mPaths;
	bool mSaveImageOnce;
private:
	QSharedPointer<ImgProcAirView> mAirViewTf;
public:
	void init_param();
	void InitImageSavePath();
private:	
signals:	
	void sig_1_frame_bgra_ref(QSharedPointer<QImage>, const QDateTime);
public slots :	
	void ImageProc(QSharedPointer<QImage> _img_p, const QDateTime _time);
public:
	void  setAirViewTf(QSharedPointer<ImgProcAirView> _av);
protected:	
	bool  airViewBirdsImg(IplImage * _src, IplImage * _dst);

	float airViewMetersPerPixel();

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
public slots:
	void setCalGndMode(bool _m);
	void setReCalGndPlane(bool _c);
	void reCalGndPlane();
public slots:
	void set_X_P0(const double _v);
	void set_X_P1(const double _v);
	void set_X_P2(const double _v);
	void set_X_P3(const double _v);

	void set_Y_P0(const double _v);
	void set_Y_P1(const double _v);
	void set_Y_P2(const double _v);
	void set_Y_P3(const double _v);

	void set_X_P0(const QString& _v);
	void set_X_P1(const QString& _v);
	void set_X_P2(const QString& _v);
	void set_X_P3(const QString& _v);

	void set_Y_P0(const QString& _v);
	void set_Y_P1(const QString& _v);
	void set_Y_P2(const QString& _v);
	void set_Y_P3(const QString& _v);
public slots:
	void SetSaveImageOnce(const bool _s);
	void SetSaveImageOnce();
public:
	static	IplImage * createImageHeader(QSharedPointer<QImage> _img_p);
	void SaveQImage(const QSharedPointer<QImage> _img);
	void SaveQImageOnce(const QSharedPointer<QImage> _img);
		
};

Q_DECLARE_METATYPE(QVector<QVector3D>);