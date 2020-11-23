#pragma once
/*-----------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*-----------------------------------------*/
#include <QMainWindow>
#include <QtWebSockets/QtWebSockets>
#include <QEvent>
#include <QTimer>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QGraphicsScene>
#include <QList>
#include <QPoint>
#include <QPolygonF>
/*-----------------------------------------*/
#include <opencv2\opencv.hpp>
/*-----------------------------------------*/
#include <QT_SDK_LIB/QBase.h>
#include <OPENCV_QT_SDK_LIB\OpencvQtBase.h>
/*-----------------------------------------*/
#include <savepicture.h>
#include <videoplayer.h>
/*-----------------------------------------*/
#include "PreProcImageOrg.h"
#include "PreProcImageSvg.h"
#include "SvgProcImage.h"
#include "DrivePolicy.h"
#include "DriveHardware.h"
#include "CarHardware.h"
/*-----------------------------------------*/
#include "ImageProcCalibration.hpp"
#include "ImageProcTopDown.hpp"
/*-----------------------------------------*/
#include "ROS_LIB/sensor_msgs_PointCloud.hpp"
#include "ROS_LIB/tf_tfMessage.hpp"
#include "ROS_LIB/advertise_a_topic.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
namespace Ui {
class MainWindow;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private:
	bool mIsCarRunAuto;
	bool mShowDirection;
	bool mIsAdvertiseTopic;
private:
	void advertiseTopic();
private:
	void initParam();
	void initObject();
	void initRegisterMetaType();
private:
	void initMenu();
	void initMenuShow();
	void initMenuRun();
	void initMenuCollect();
	void initMenuConnect();
	void initMenuImageProcessing();
private:

private:
	void initMainWindowUI();
	void initMainWindowUI_Connect();
private:
	void initTabCfg();
	void initTabCfgGroundPlane();
	void initTabCfgCameraCalibration();
private:
	void connectTabCfg();
	void connectTabCfgGroundPlane();
	void connectTabCfgCameraCalibration();
private:
	void InitWebSocket();
private slots:
  
	void on_up_clicked();

    void on_STOP_clicked();

    void on_LEFT_clicked();

    void on_RIGHT_clicked();

    void on_DOWN_clicked();

    void on_UP_LEFT_clicked();

    void on_UP_RIGHT_clicked();

    void on_DOWN_LEFT_clicked();

    void on_DOWN_RIGHT_clicked();

    void on_xian_valueChanged(int value);

    void on_jiao_valueChanged(int value);

    void on_comboBox_activated(const QString &arg1);

    void on_start_clicked();

    void on_stop_clicked();
	   
    void on_open_cam_clicked();

    void on_close_cam_clicked();
	  
    void on_obs_box_activated(const QString &arg1);
	
	void run_policy(
		RunCmd _cmd,
		double _speed_v1,
		double _speed_v2,
		const QDateTime _time);

	void run_policy_interval(
		const RunCmd _cmd,
		const double _speed_v1,
		const double _speed_v2,
		const QDateTime _time,
		const int _ms);

	void drive_run_policy(
		const RunCmd& _cmd,
		const double _speed_v1,
		const double _speed_v2);
	
public slots:
    void onconnected();

    void disconnected();

    void errorconnected(QAbstractSocket::SocketError error);

    void changeDial(int i);  //转盘值改变事件

    void release();  //转盘释放事件
	   
	void ShowOneFrameBgraOrg(QSharedPointer<QImage> _img_ptr,const QDateTime _time);
	void ShowOneFrameBgraSvg(QSharedPointer<QImage> _img_ptr,const QDateTime _time);
	
	void ShowOneFrameCalibrate(QSharedPointer<QImage> _img_ptr, const QDateTime _time);
	void ShowOneFrameTopDown(QSharedPointer<QImage> _img_ptr, const QDateTime _time);
	
	void ShowOneFrameOnLabel(QImage * _img, const QDateTime * _time, QLabel * _qlab);
	
	void RcvOneFrameBgraOrg(QImage _img,const QDateTime _time);
	void RcvOneFrameBgraSvg(QImage _img,const QDateTime _time);
	   	
	void menu_show_run_direction(bool _v);
	void menu_run_auto(bool _r);
	void menu_run_current_once(bool _r);
					
	void menu_toggle_calibration_SVG_SRC(bool _f);
public:
	void connect_calibration_SVG();
	void connect_calibration_SRC();
	
	
public slots:
	void PublishPointCloud(QVector<QVector3D> _ptc);
	
private:
    Ui::MainWindow *ui;
	   
    QString path;      //数据文件路径

    int last_key;     //上一次按键的值


		
    QImage mImage;           //记录当前图像 用于展示
               
    int point1_x;
    int point1_y;
    int point2_x;
    int point2_y;
    //斜率
    float k;

    //障碍物 参数
    int obs_x;  //障碍物中心x坐标
    int obs_y;  //障碍物中心y坐标
    int obs_r;      //障碍物半径
private:
		PreProcImageOrg ppImageOrg;
		PreProcImageSvg ppImageSvg;
private:
		QSharedPointer<VideoPlayer>				mImagePlayer;    //ffpmeg编解码
private:
		QSharedPointer<SVG_PROC_IMAGE>			mImageProcSVG;
		QSharedPointer<ImageProcCalibration>	mImageProcCal;
		QSharedPointer<ImageProcTopDown>		mImageProcTopDown;
		
private:
		QSharedPointer<CarHardware>				mCarHardware;
private:
	    QVector<QSharedPointer<QObject>> m_thread_obj;
	    QVector<QSharedPointer<QThread>> m_thread_pool;
public:
	void ThreadWork_Init();
	void ThreadWork_Init_thread();
	void ThreadWork_Init_obj();

	void ThreadWork_Start();
	void ThreadWork_Stop();
	void ThreadWork_Wait();
public:
	
	void initThreadWorkConnect();
	void initThreadWorkConnect_PreImageShow();
	void initThreadWorkConnect_ImageShow();
	void initThreadWorkConnect_Calibration();
	void initThreadWorkConnect_SVG();
	void initThreadWorkConnect_TopDown();

public:
    QRect *m_rect;            //录频区域

    static QImage cvMat2QImage(const cv::Mat& mat);  //Mat转QImage

    static cv::Mat QImage2cvMat(QImage image);       //QImage转Mat

    float convert2dist(int y);        //计算像素点距摄像头的实际距离 y为像素点的纵坐标

protected:
    virtual void keyPressEvent(QKeyEvent *ev);  //按键事件

    void send();           //socket发送消息  按键消息实时发送

    void barChange();      //转盘进度条的显示
	  

};

#endif // MAINWINDOW_H