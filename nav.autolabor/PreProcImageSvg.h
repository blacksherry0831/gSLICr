#pragma once
#ifndef _PreProcImageSvg_H_
#define _PreProcImageSvg_H_
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <queue>
#include <QQueue>
#include <QDateTime>
/*-----------------------------------------*/
#include "DriveAuto.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class PreProcImageSvg : public QObject
{
    Q_OBJECT

public:
	Q_INVOKABLE explicit PreProcImageSvg(QObject *parent = nullptr);
	~PreProcImageSvg();
private:
	bool mSafeArea;
public:
	void SetResize(const int _w,const int _h);
public:
signals:
	void sig_1_frame_bgra(QImage, QDateTime);
public slots :
	void ImageProc(QImage _img, const QDateTime _time);
	void DrawSafeArea(const bool _r);

};

#endif
