#pragma once
#ifndef _DrivePolicy_H_
#define _DrivePolicy_H_
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <QQueue>
#include <QPainter>
#include <QPen>
#include <QDateTime>
#include <QDebug>
/*-----------------------------------------*/
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
/*-----------------------------------------*/
#include "MY_SDK_LIB/TimeMeasure.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class DrivePolicy : public QObject
{
	Q_OBJECT
	Q_ENUMS(RunCmd)
public:

	enum RunCmd
	{
		GO_DOWN,
		GO_DOWN_LEFT,
		GO_DOWN_RIGHT,
		GO_RIGHT,
		GO_LEFT,
		GO_UP_RIGHT,
		GO_UP_LEFT,
		GO_UP,
		GO_NONE,
	};
public:
	Q_INVOKABLE explicit DrivePolicy(QObject *parent = nullptr);
	~DrivePolicy();
public:
signals:
	   void sig_run_cmd(DrivePolicy::RunCmd,QDateTime);
	   void sig_1_frame_bgra(QImage, QDateTime);
	   void sig_1_frame_bgra_once(QImage&, QDateTime&);
private:
	QPolygonF polygon1;   //安全区a1
	QPolygonF polygon2;   //安全区a2
	QPolygonF polygon3;   //安全区a3
	QPolygonF polygon4;   //安全区a4
	QPolygonF polygon5;   //安全区a5
	QPolygonF polygon6;   //安全区a6
private:
	int a1;  //障碍物与安全区a1的交叉面积 像素点个数
	int a2;  //障碍物与安全区a2的交叉面积
	int a3;  //障碍物与安全区a3的交叉面积
	int a4;  //障碍物与安全区a4的交叉面积
	int a5;  //障碍物与安全区a5的交叉面积
	int a6;  //障碍物与安全区a6的交叉面积
	int none;  //障碍物与安全区的不交叉面积
public:
	static bool IsLatestImage(const QDateTime& _time, const int64& _ms = 1000);
public:
	void ClearArea();
	void InitArea_1920_1080();
	void InitArea_960_540();
public:	
	void CalSafeArea_1920_1080(const QImage& _img);
	void CalSafeArea_960_540(const QImage& _img);
	int Qimage2cvMat(QImage& _img);
	void policy(const QImage & _img,const QDateTime & _time);
public slots:
	void CalSafeAreaLatest(const QImage & _img, const QDateTime & _time);
	void CalSafeAreaFast(const QImage & _img, const QDateTime & _time);
	void CalSafeArea(const QImage _img, const QDateTime _time);

};

Q_DECLARE_METATYPE(DrivePolicy::RunCmd);

#endif