#pragma once
/*-----------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*-----------------------------------------*/
#include <QMainWindow>
#include <QtWebSockets/QtWebSockets>
#include <QEvent>
#include <QTimer>
#include <service.h>
#include <QGraphicsScene>
#include <videoplayer.h>
#include <QList>
#include <QPoint>
#include <QPolygonF>
/*-----------------------------------------*/
#include <opencv2\opencv.hpp>
/*-----------------------------------------*/
#include <QT_SDK_LIB/QBase.h>
/*-----------------------------------------*/
#include <savepicture.h>
#include "SVG_PROC.h"
/*-----------------------------------------*/
#include "PreProcImageOrg.h"
#include "PreProcImageSvg.h"
#include "SvgProcImage.h"
#include "DrivePolicy.h"
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
	bool mIsCarRun;
private:
	void initParam();
private slots:
    void on_shuaxin_clicked();  //刷新socket连接

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

    void on_tu_startButton_clicked();

    void on_tu_stopButton_clicked();

    void on_open_cam_clicked();

    void on_close_cam_clicked();
	    
    void on_moni_button_clicked();

    void on_obs_box_activated(const QString &arg1);

    void s_timeout();


	void run_policy(DrivePolicy::RunCmd _cmd, const QDateTime _time);

public slots:
    void onconnected();

    void disconnected();

    void errorconnected(QAbstractSocket::SocketError error);

    void changeDial(int i);  //转盘值改变事件

    void release();  //转盘释放事件

    void sendmsg(QString msg);   //多线程调用的发送消息函数

    void slotGetOneFrame(QImage img);   //获取图像

	void ShowOneFrameBgraOrg(QImage _img,const QDateTime _time);
	void ShowOneFrameBgraSvg(QImage _img,const QDateTime _time);

	void RcvOneFrameBgraOrg(QImage _img,const QDateTime _time);
	void RcvOneFrameBgraSvg(QImage _img,const QDateTime _time);

    void timeouts();        //定时器超时函数

private:
    Ui::MainWindow *ui;

    QUrl url;          //socket连接的url

    bool connectFlag;  //socket连接成功与否的标志

    Service service;   //线程

    QString path;      //数据文件路径

    int last_key;     //上一次按键的值

	QSharedPointer<VideoPlayer>		mPlayer;    //ffpmeg编解码
		

    QImage mImage;           //记录当前图像 用于展示
    QImage mImage2;          //记录当前图像 用于保存
    QImage mImage3;          //记录当前图像 用于模拟

//    ScreenRecorder *m_screenRecorder; //录频对象
//    bool m_recordeState;   //录频状态
//    QString m_recordPath;    //录频文件路径

    QTimer *m_timer;   //定时器 用来测试1秒多少张图
    int i;              //记录图片张数

    QTimer *s_timer;    //定时器 用于控制相同指令发送的时间间隔
    bool s_flag;        //相同指令发送许可标志；   1为可发生 0为不可发送
    bool d_flag;        //不同指令发送许可标志；   1为可发生 0为不可发送

    bool tuflag;        //开始截图标志
    SavePicture *savePicture1;   //截图保存 进程1
    SavePicture *savePicture2;   //截图保存 进程2
    SavePicture *savePicture3;   //截图保存 进程3
    int savePictureCount;        //用于保存图片计数

    cv::VideoCapture cap;  //摄像头标志符
	
   
    bool moni_flag;     //模拟运动标志

    

    //最近点坐标
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
	DrivePolicy::RunCmd mRunCmd;
 private:
		PreProcImageOrg ppImageOrg;
		PreProcImageSvg ppImageSvg;
private:
		SVG_PROC_IMAGE     svgProcImage;
		DrivePolicy		   drivePolicy;
private:
		QThread mThreadPreShowBgraOrg;
		QThread mThreadPreShowBgraSvg;
private:
		QThread mThreadProcSvg;
		QThread mThreadRunPolicy;
public:
	void initThreadWorkObject();
	void initThreadWorkConnect();
	void ThreadWork_Start();
public:
    QRect *m_rect;            //录频区域

    static QImage cvMat2QImage(const cv::Mat& mat);  //Mat转QImage

    static cv::Mat QImage2cvMat(QImage image);       //QImage转Mat

    float convert2dist(int y);        //计算像素点距摄像头的实际距离 y为像素点的纵坐标

protected:
    virtual void keyPressEvent(QKeyEvent *ev);  //按键事件

    void send();           //socket发送消息  按键消息实时发送

    void barChange();      //转盘进度条的显示

    void jietu();          //视频截图

};

#endif // MAINWINDOW_H
