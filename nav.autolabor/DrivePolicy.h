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
#include "RunCmd.h"
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
	//Q_ENUMS(RunCmd)
public:

	
public:
	Q_INVOKABLE explicit DrivePolicy(QObject *parent = nullptr);
	~DrivePolicy();
public:
signals:
	   void sig_run_cmd(RunCmd,double,double,QDateTime);
	   void sig_1_frame_bgra(QImage, QDateTime);
	   void sig_1_frame_bgra_once(QImage&, QDateTime&);
private:
	void emit_sig_run_cmd(RunCmd _cmd, double _v1, double _v2, QDateTime _time);
private:
	bool mEnable;
	RunCmd	mRunCmd;
public:
	void SetEnable(bool _en);
private:
	bool IsEnable();
public:
	void EnablePolicy(bool _en);
	RunCmd	PolicyRunCmd();
private:
	const unsigned int  color1 = 0xFFFF00FF;
	const unsigned int  color2 = 0xFFFF0000;
	const unsigned int  color3 = 0xFF218868;
	const unsigned int  color4 = 0xFF20B2AA;
	const unsigned int  color5 = 0xFFCAFF70;
	const unsigned int  color6 = 0xFFEEEE00;
private:
	QPolygonF polygon1;   //安全区a1
	QPolygonF polygon2;   //安全区a2
	QPolygonF polygon3;   //安全区a3
	QPolygonF polygon4;   //安全区a4
	QPolygonF polygon5;   //安全区a5
	QPolygonF polygon6;   //安全区a6
private:
	std::vector<cv::Point>  pointSet1;
	std::vector<cv::Point>  pointSet2;
	std::vector<cv::Point>  pointSet3;
	std::vector<cv::Point>  pointSet4;
	std::vector<cv::Point>  pointSet5;
	std::vector<cv::Point>  pointSet6;
private:
	QImage  mImgArea_960_540;
private:
	int a1;  //障碍物与安全区a1的交叉面积 像素点个数
	int a2;  //障碍物与安全区a2的交叉面积
	int a3;  //障碍物与安全区a3的交叉面积
	int a4;  //障碍物与安全区a4的交叉面积
	int a5;  //障碍物与安全区a5的交叉面积
	int a6;  //障碍物与安全区a6的交叉面积
	int none;  //障碍物与安全区的不交叉面积
private:
	QQueue<RunCmd> mRunCmdQ;
	QQueue<RunCmd> mExecCmdQ;
public:
	void CLearRunCmd();
	void EnqueueRunCmd(const RunCmd _rc);
	void EnqueueExecCmd(const RunCmd _rc);
	void CollectRunCmd(const RunCmd _rc);
public:
	static  int FindMaxPos(std::vector<float> _vec);
public:
	static bool IsLatestImage(const QDateTime& _time, const int64& _ms = 100);
public:
	void ClearArea();
	void InitArea_1920_1080();
	void InitArea_960_540();
	void emitMask_960_540();
	void InitColor();
private:
	void InitImageArea_960_540(); 
	void InitPolygonArea_960_540();
	void InitPointSet_960_540();
private:
	void CountVerticalOnArea(
		const int* _pixel_data,
		const int&  _w,
		const int&  _h,
		const std::vector<cv::Point>& _point_set,
		const int& _v,
		int & _a_count);
public:	
	void CalSafeArea_1920_1080(const QImage& _img);
	void CalSafeArea_960_540(const QImage& _img);
	int Qimage2cvMat(QImage& _img);
	void policy(const QImage & _img,const QDateTime & _time);
	static void policy_speed(QQueue<RunCmd> _RunCmdQ, double & _v1, double & _v2);
	
	RunCmd policy_dir_weight_avg();
	
	void policy_dir_speed(const QImage & _img, const QDateTime & _time);
	void policy_dir(const QImage & _img, const QDateTime & _time);

	void policy_img_normal();	
	
	RunCmd policy_normal();


			
public slots:
	void CalSafeAreaLatest(const QImage & _img, const QDateTime & _time);
	void CalSafeAreaFast(const QImage & _img, const QDateTime & _time);
	void CalSafeArea(const QImage _img, const QDateTime _time);

};

//Q_DECLARE_METATYPE(RunCmd);

#endif