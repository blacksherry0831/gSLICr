#pragma once
#ifndef _PreProcImageOrg_H_
#define _PreProcImageOrg_H_
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QDateTime>
#include <QQueue>
/*-----------------------------------------*/
#include "DriveAuto.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class PreProcImageOrg : public QObject
{
    Q_OBJECT

public:
	Q_INVOKABLE explicit PreProcImageOrg(QObject *parent = nullptr);
	~PreProcImageOrg();
private:
	bool mSafeArea;
public:
	void SetResize(const int _w,const int _h);
public:
signals:
	void sig_1_frame_bgra(QImage, QDateTime);
public slots :
	void ImageProc(QImage _img, QDateTime _time);

};

#endif
