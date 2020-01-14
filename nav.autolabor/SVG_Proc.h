#pragma once
#ifndef _SVG_PROC_H
#define _SVG_PROC_H
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <queue>
#include <QJsonDocument>
#include <QJsonObject>
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
class SVG_PROC : public QThread
{
    Q_OBJECT
public:
    explicit SVG_PROC();
    ~SVG_PROC();
signals:
	void sig_1_frame_svg_bgra(QImage); //每获取到一帧图像 就发送此信号
private:
	QImage_Q  mImgQ;
protected:
	//定义自己需要的方法或变量  
	bool M_THREAD_RUN;
public:
	void startServer();
	void closeServer();
public:
	bool IsValidQImage(const QImage _img);
public:
	void SetQImage(const QImage _img);
public:
	void ProcImage(const QImage _img);
	void ProcImageSVG(const QImage _img);
protected:
    virtual void run();
	virtual	void run_thread_work();
};

#endif // SAVEPICTURE_H
