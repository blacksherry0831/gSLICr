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
	ImgProcCalibrate m_imgProcCal;
	bool mIsImageProc;
public:
	bool IsValidQImage(const QImage& _img);
public:
	static bool IsLatestImage(const QDateTime& _time, const int64 _ms=100);
	void ProcImageFrame(const QImage& _img, const QDateTime& _time);
	void ProcImageFrame01(const QImage& _img, const QDateTime& _time);
signals:
void sig_1_frame_bgra(QImage, QDateTime);
public slots :
void ImageProc(QImage _img, const QDateTime _time);
void setImageProc(bool _f);

};
