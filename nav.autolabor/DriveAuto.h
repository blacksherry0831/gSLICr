#pragma once
#ifndef _DriveAuto_H_
#define _DriveAuto_H_
/*-----------------------------------------*/
#include <QThread>
#include <QImage>
#include <queue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>
#include <QPainter>
#include <QPen>
#include <QPoint>
/*-----------------------------------------*/
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
/*-----------------------------------------*/
#include "DrivePolicy.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class DriveAuto : public QObject
{
    Q_OBJECT

public:
	Q_INVOKABLE explicit DriveAuto(QObject *parent = nullptr);
	~DriveAuto();

	static void DrawSafeArea(QImage& _img);
	static void DrawSafeArea_1920_1080(QImage& _img);
	static void DrawSafeArea_960_540(QImage& _img);

	static void DrawRunDirection(QImage& _img,RunCmd _run_dir);
	static void DrawRunDirection(QImage& _img,bool _run, RunCmd _run_dir);

	static void CalSafeArea(QImage& _img);
	static void CalSafeArea_1920_1080(QImage& _img);
	static void CalSafeArea_960_540(QImage& _img);

	static int Qimage2cvMat(QImage& _img);

};

#endif
