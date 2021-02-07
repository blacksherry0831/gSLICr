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
#include <videoplayer.h>
/*-----------------------------------------*/
#include "PreProcImageOrg.h"
#include "PreProcImageSvg.h"
#include "SvgProcImage.h"
#include "DrivePolicy.h"
#include "DriveHardware.h"
#include "CarHardware.h"
#include "mw_cfg_kv.hpp"
/*-----------------------------------------*/
#include "ImageProcCalibration.hpp"
/*-----------------------------------------*/
#include "ImageProcTopDownSVG.hpp"
#include "ImageProcTopDownTrafficSign.hpp"
/*-----------------------------------------*/
#include "ROS_LIB/sensor_msgs_PointCloud.hpp"
#include "ROS_LIB/geometry_msgs_Pose.hpp"
#include "ROS_LIB/geometry_msgs_PoseStamped.hpp"
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
	std::vector<bool> mIsAdvertiseTopic;
private:
	QStringList	getTopicAllFrontCam();
	QStringList	getTopicTypeAllFrontCam();
	void advertiseTopic();
	int  advertiseTopicOne(const QString _topic,const QString _type);
	void advertiseTopic_PublishTF();
private:
	void initParam();
	void initObject();
	void initUICfg();
	void initRegisterMetaType();
private:
	void initMenu();
	void initMenuVideoDecoder();
	void initMenuShow();
	void initMenuRun();
	void initMenuCollect();
	void initMenuConnect();
	void initMenuImageProcessing();
private:
	const int IMG_W=1920;
	const int IMG_H=1080;
private:
	const QString	URL_ROS_WS				=	"ws://192.168.99.200:9090";
	const QString	URL_RTSP_STREAM			=	"rtsp://192.168.99.201/stream1";
private:
	const QString	ROS_frame_id_base		=	"base_link";
	const QString	ROS_frame_id_camera		=	"base_front_camera_link";
private:
	const QString	ROS_topic_f_cam_svg_pointcloud		=	"/cam_front_svg_pointcloud";
private:
	const QString	ROS_topic_f_cam_tsign_pose_red		=	"/cam_front_tsign_pose_red";	
	const QString	ROS_topic_f_cam_tsign_pose_green	=	"/cam_front_tsign_pose_green";
	const QString	ROS_topic_f_cam_tsign_pose_yellow	=	"/cam_front_tsign_pose_yellow";
private:
	const QString	ROS_topic_f_cam_tsign_pc_red		=	"/cam_front_tsign_pc_red";
	const QString	ROS_topic_f_cam_tsign_pc_green		=	"/cam_front_tsign_pc_green";
	const QString	ROS_topic_f_cam_tsign_pc_yellow		=	"/cam_front_tsign_pc_yellow";
private:
	const QVector3D	ROS_TF_cam_Trans= QVector3D(0.35,0,0);
private:
	void initMainWindowUI();
	void initMainWindowUI_Connect();
	void initMainWindowUI_Tab_CfgCroundPlane();
private:
	
	
private:
	void connectTabCfg();
	void connectTabCfgGroundPlane();
	void connectTabCfgCameraCalibration();
private:
	void initUiValueGroundPlane();
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

	void ShowOneFrameCalibrateOrg(QSharedPointer<QImage> _img_ptr, const QDateTime _time);
	void ShowOneFrameTopDownOrg(QSharedPointer<QImage> _img_ptr, const QDateTime _time);
	
	void ShowOneFrameOnLabel(QImage * _img, const QDateTime * _time, QLabel * _qlab);
	
	void RcvOneFrameBgraOrg(QImage _img,const QDateTime _time);
	void RcvOneFrameBgraSvg(QImage _img,const QDateTime _time);
	   	
	void menu_show_run_direction(bool _v);
	void menu_run_auto(bool _r);
	void menu_run_current_once(bool _r);

	void publishPointCloud(
		QString _topic,
		QString _frame_base,
		QString _frame_sensor,
		QVector<QVector3D> _ptc);

	void publishPointCloud_FrameCamrea(
		QString _topic,
		QVector<QVector3D> _ptc);

	void publishPose(
		QString		_topic,
		QVector3D	_p3t, 
		QVector4D	_p4t);
	
public slots:
	void SetCalGndMode(bool _s);
public:
	void publishTF_Camera();
public slots:
	void PublishPointCloud_SVG(QVector<QVector3D> _ptc);
	void PublishPointCloud_TS(QString _color, QVector<QVector3D> _ptc);
	void PublishPose_TS(QString _color,QVector3D _p3t, QVector4D _p4t);

	
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
		QSharedPointer<MW_CFG_KV>							mMW_CFG;
private:
		QSharedPointer<ImgProcAirView>					mAirViewTf;
private:
		PreProcImageOrg ppImageOrg;
		PreProcImageSvg ppImageSvg;
private:
		QSharedPointer<VideoPlayer>						mImagePlayer;    //ffpmeg编解码
private:
		QSharedPointer<SVG_PROC_IMAGE>					mImageProcSVG;
		QSharedPointer<ImageProcCalibration>			mImageProcCalSVG;
		QSharedPointer<ImageProcTopDownSVG>				mImageProcTopDownSVG;
		QSharedPointer<ImageProcCalibration>			mImageProcCalOrg;
		QSharedPointer<ImageProcTopDownTrafficSign>		mImageProcTopDownOrg;
		
private:
		QSharedPointer<CarHardware>				mCarHardware;
private:
	    QVector<QSharedPointer<QObject>>		m_thread_obj;
	    QVector<QSharedPointer<QThread>>		m_thread_pool;
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
	void initThreadWorkConnect_ImageShow_CalOrg();
	void initThreadWorkConnect_ImageShow_CalSvg();
	
	void initThreadWorkConnect_Calibration();
	void initThreadWorkConnect_Calibration_Org();
	
	void initThreadWorkConnect_SVG();
	void initThreadWorkConnect_TopDown();
	void initThreadWorkConnect_TopDown_Org();

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