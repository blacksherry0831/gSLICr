#pragma once
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QQueue>
/*-----------------------------------------*/
#include "SGV/SGV_Method.h"
/*-----------------------------------------*/
#include "MY_SDK_LIB\ImgProcCalibrate.hpp"
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
class ImageProcCalibration :public QObject
{
    Q_OBJECT
public:
     ImageProcCalibration();
    ~ImageProcCalibration();
private:
	static IplImage* createImageHeader(QSharedPointer<QImage> _img_p);
private:
	ImgProcCalibrate m_imgProcCal;
	bool mIsImageProc;
public:
	void ProcImageFrame(QSharedPointer<QImage> _img_p, const QDateTime& _time);
	void ProcImageFrameNot(QSharedPointer<QImage> _img_p, const QDateTime& _time);
	
signals:
void sig_1_frame_bgra_ref(QSharedPointer<QImage>, const QDateTime);

public slots :

void ImageProc(
	QSharedPointer<QImage> _img_p,
	const QDateTime _t);

void setImageProc(bool _f);

};
