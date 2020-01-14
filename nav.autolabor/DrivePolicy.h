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
	QPolygonF polygon1;   //��ȫ��a1
	QPolygonF polygon2;   //��ȫ��a2
	QPolygonF polygon3;   //��ȫ��a3
	QPolygonF polygon4;   //��ȫ��a4
	QPolygonF polygon5;   //��ȫ��a5
	QPolygonF polygon6;   //��ȫ��a6
private:
	int a1;  //�ϰ����밲ȫ��a1�Ľ������ ���ص����
	int a2;  //�ϰ����밲ȫ��a2�Ľ������
	int a3;  //�ϰ����밲ȫ��a3�Ľ������
	int a4;  //�ϰ����밲ȫ��a4�Ľ������
	int a5;  //�ϰ����밲ȫ��a5�Ľ������
	int a6;  //�ϰ����밲ȫ��a6�Ľ������
	int none;  //�ϰ����밲ȫ���Ĳ��������
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