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
#include "General.hpp"
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
	static bool IsLatestImage(const QDateTime& _time, const int64 _ms=100);
	
	void ProcImageSVG(QSharedPointer<QImage> _img_p, const QDateTime& _time);

signals:
void sig_out_frame_bgra(QSharedPointer<QImage>, QDateTime);
void sig_org_frame_bgra(QSharedPointer<QImage>, QDateTime);

public slots :
void ImageProc(QSharedPointer<QImage> _img_ptr, const QDateTime _time);

};

#endif // SAVEPICTURE_H
