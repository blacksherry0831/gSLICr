#pragma once
#ifndef _SVG_PROC_IMAGE_H
#define _SVG_PROC_IMAGE_H
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QQueue>
/*-----------------------------------------*/
#include "SGV/SGV_Method.h"
/*-----------------------------------------*/
#include "QT_SDK_LIB/QImage_Q.hpp"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
class SVG_PROC_IMAGE :public QObject
{
    Q_OBJECT
public:
    explicit SVG_PROC_IMAGE();
    ~SVG_PROC_IMAGE();
public:
	bool IsValidQImage(const QImage& _img);
public:
	static bool IsLatestImage(const QDateTime& _time, const int64 _ms=100);
	void ProcImageSVG(const QImage& _img, const QDateTime& _time);
signals:
void sig_1_frame_bgra(QImage, QDateTime);
public slots :
void ImageProc(QImage _img, const QDateTime _time);

};

#endif // SAVEPICTURE_H
