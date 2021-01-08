#pragma once
#ifndef _PreProcImageOrg_H_
#define _PreProcImageOrg_H_
/*-----------------------------------------*/
#include <QDir>
#include <QThread>
#include <QImage>
#include <QDateTime>
#include <QQueue>
#include <QCoreApplication>
/*-----------------------------------------*/
#include "DriveAuto.h"
/*-----------------------------------------*/
#include "QT_SDK_LIB/QBase.h"
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
	bool mSaveImage;
	bool mSaveImageOnce;
private:
	QString mPaths;
public:
	void InitImageSavePath();
public:
	void SaveQImage(const QImage & _img);
	void SaveQImage(const QSharedPointer<QImage> _img);

	void SetResize(const int _w,const int _h);
public:
signals:
	void sig_1_frame_bgra_ref(QSharedPointer<QImage>, const QDateTime);
public slots :
	
	void ImageProc(QSharedPointer<QImage> _img_ptr, QDateTime _time);
	void DrawSafeArea(const bool _r);
	void SetSaveImage(const bool _s);
	void SetSaveImageOnce(const bool _s);
};

#endif
