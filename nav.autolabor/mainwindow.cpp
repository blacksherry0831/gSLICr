#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cloudpanel.h"
#include "roundprogressbar.h"
#include <quanju.h>
#include <QtWebSockets/QtWebSockets>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <service.h>
#include <QKeyEvent>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include "savepicture.h"
#include <QRect>

#pragma execution_character_set("utf-8")

//debug笔记：需控制发指令的线程数，如不控制，可能会导致viodeo线程的挂起！！！！
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->initParam();
    
	this->initMenu();
	
	//socket连接
    url = QUrl("ws://192.168.0.10:9090");
    Quanju::websocket.open(url);
    connect(&Quanju::websocket,SIGNAL(connected()),this,SLOT(onconnected()));
    connect(&Quanju::websocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(&Quanju::websocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(errorconnected(QAbstractSocket::SocketError)));

    connectFlag=false;   //连接成功标志初始化
    ui->shuaxin->setText("打开连接");  //连接按钮初始化

    //转盘进度条设置 此为控件
    ui->roundProgressBar->setStartAngle(RoundProgressBar::PositionTop);   //起始角度  正上方
    ui->roundProgressBar->setBarStyle(RoundProgressBar::StyleLine);       //风格
    ui->roundProgressBar->setDecimals(2);                                 //设置小数点位数
    ui->roundProgressBar->setClockwise(true);                            //设置是否顺时针
    ui->roundProgressBar->setOutlinePenWidth(18);                         //设置外圆画笔宽度
    ui->roundProgressBar->setDataPenWidth(10);                            //设置外圆画笔宽度
    ui->roundProgressBar->setTextVisible(false);                          //设置文字是否隐形
    ui->roundProgressBar->setRange(0,6.4);                                //设置角度范围
    ui->roundProgressBar->setValue(0);                                    //设置当前角度

    //转盘设置
    ui->dial->setMaximum(300);  //最大值
    ui->dial->setMinimum(0);    //最小值
    ui->dial->setValue(150);    //当前值
    connect(ui->dial,SIGNAL(valueChanged(int)),this,SLOT(changeDial(int)));  //转动的角度值改变的话 调用相应函数
    connect(ui->dial,SIGNAL(sliderReleased()),this,SLOT(release()));         //释放

    //获取当前文件路径  数据文件
//    QDir mydir(QDir::currentPath());
//    path=mydir.absolutePath()+"/shuju";
    path="D://shuju";
    QDir dir;
    if(!dir.exists(path))  // 检查目录是否存在，若不存在则新建
    {
        bool res = dir.mkpath(path);
        qDebug() << "新建目录是否成功" << res;
    }

    last_key=1000;   //初始化上一次按键的值

    ui->stackedWidget->setCurrentIndex(0);  //初始化模式

    //线速度的刻条显示
    ui->xian->setMinimum(0);
    ui->xian->setMaximum(250);
    ui->xian->setValue(125);
    //角速度的刻条显示
    ui->jiao->setMinimum(0);
    ui->jiao->setMaximum(1600);
    ui->jiao->setValue(800);

    //全局变量初始化
    Quanju::x=1;
    Quanju::y=0;
    Quanju::v1=0.125;
    Quanju::v2=0.8;
    Quanju::change=0;

	this->initThreadWorkObject();
	this->initThreadWorkConnect();
	this->ThreadWork_Start();

    ui->start->setEnabled(true);  //开始录屏 按钮
    ui->stop->setEnabled(false);  //结束录屏 按钮

    //每隔一段时间 后台显示已经保存的截图张数
    i=0;   //已经保存的截图张数
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    //m_timer->start();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(timeouts()));

    //截图功能
    tuflag = false;  //开始截图标志
    ui->tu_startButton->setEnabled(true);
    ui->tu_stopButton->setEnabled(false);

   
    //模拟障碍物标志初始化


    point1_x=0;
    point1_y=0;
    point2_x=0;
    point2_y=0;
    k=0;
	


    //障碍物 参数初始化
    obs_x = 900;  //障碍物中心x坐标
    obs_y = 600;  //障碍物中心y坐标
    obs_r = 50;      //障碍物半径
    ui->obs_box->setEnabled(false);

    //初始化指令发送标志
    s_flag = 1;        //相同指令发送许可标志；   1为可发生 0为不可发送
    d_flag = 1;        //不同指令发送许可标志；   1为可发生 0为不可发送
    s_timer = new QTimer();    //定时器 用于控制相同指令发送的时间间隔
    s_timer->setInterval(500);
    connect(s_timer,SIGNAL(timeout()),this,SLOT(s_timeout()));
    s_timer -> start();

    //截图进程初始化
    savePicture1 = new SavePicture(path);
    savePicture1->start_s();
    savePicture2 = new SavePicture(path);
    savePicture2->start_s();
    savePicture3 = new SavePicture(path);
    savePicture3->start_s();

    savePictureCount = 0;

#if 0
	TimeMeasure::Config(1, 1);
#else
	TimeMeasure::Config(0, 0);
#endif // 0

	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
MainWindow::~MainWindow()
{
    Quanju::websocket.close();
    Quanju::websocket.deleteLater();
	
	this->ThreadWork_Stop();
	this->ThreadWork_Wait();

    delete ui;
	ui = NULL;

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initParam()
{
	this->mShowDirection = false;
	this->mIsCarRunAuto=false;
	//this->mExecRunCmd = RunCmd::GO_NONE;
	this->mRumCmdTime = QDateTime::currentDateTime();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenu()
{
	this->initMenuShow();
	this->initMenuRun();
	this->initMenuCollect();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuShow()
{
	connect(ui->actionShowSafeArea, SIGNAL(triggered(bool)), &ppImageOrg, SLOT(DrawSafeArea(bool)));
	connect(ui->actionShowSafeArea, SIGNAL(triggered(bool)), &ppImageSvg, SLOT(DrawSafeArea(bool)));
	
	connect(ui->actionShowRunDirection, SIGNAL(triggered(bool)),this, SLOT(menu_show_run_direction(bool)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuRun()
{
	connect(ui->actionRunOnce, SIGNAL(triggered(bool)), this, SLOT(menu_run_current_once(bool)));
	connect(ui->actionRun, SIGNAL(triggered(bool)), this, SLOT(menu_run_auto(bool)));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuCollect()
{
	connect(ui->actionCollectAlways, SIGNAL(triggered(bool)), &ppImageOrg, SLOT(SetSaveImage(bool)));
}
/*----------------------------------------------------------------*/
/**
*socket连接成功
*/
/*----------------------------------------------------------------*/
void MainWindow::onconnected()
{
    connectFlag=true;
    ui->shuaxin->setText("断开连接");
    ui->xieche->setText("小车连接成功！");
}
/*----------------------------------------------------------------*/
/**
*socket失去连接
*/
/*----------------------------------------------------------------*/
void MainWindow::disconnected()
{
    connectFlag=false;
    ui->shuaxin->setText("打开连接");
    ui->xieche->setText("小车失去连接！");
}

//小车连接失败
void MainWindow::errorconnected(QAbstractSocket::SocketError error)
{
    connectFlag=false;
    ui->shuaxin->setText("打开连接");
    ui->xieche->setText("小车连接失败！");
    qDebug()<<tr("小车连接失败，失败原因：")<<error<<endl;
}
/*----------------------------------------------------------------*/
/**
*“刷新”按钮点击事业
*/
/*----------------------------------------------------------------*/
void MainWindow::on_shuaxin_clicked()
{
    if(connectFlag==true)
    {
        ui->xieche->setText("小车断开连接中... ");
        Quanju::websocket.close();
    }
    else if(connectFlag==false)
    {
        ui->xieche->setText("小车建立连接中... ");
        Quanju::websocket.open(url);
    }
}

//停止按钮事件
void MainWindow::on_STOP_clicked()
{
    Quanju::x=0;
    Quanju::y=0;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[0]=1;
    Quanju::change=1;

    barChange();  //转盘外圆改变
    //jietu();      //视频截图

    //开启新线程
    Service *service1 = new Service(0);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//前进按钮
void MainWindow::on_up_clicked()
{
    Quanju::x=1;
    Quanju::y=0;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[1]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    //开启新线程
    Service *service1 = new Service(1);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//后退按钮
void MainWindow::on_DOWN_clicked()
{
    Quanju::x=-1;
    Quanju::y=0;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[2]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(2);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//左 按钮
void MainWindow::on_LEFT_clicked()
{
    Quanju::x=0;
    Quanju::y=1;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[3]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(3);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//右 按钮
void MainWindow::on_RIGHT_clicked()
{
    Quanju::x=0;
    Quanju::y=-1;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[4]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(4);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//上左
void MainWindow::on_UP_LEFT_clicked()
{
    Quanju::x=1;
    Quanju::y=1;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[5]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(5);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//上右
void MainWindow::on_UP_RIGHT_clicked()
{
    Quanju::x=1;
    Quanju::y=-1;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[6]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(6);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//下左
void MainWindow::on_DOWN_LEFT_clicked()
{
    Quanju::x=-1;
    Quanju::y=-1;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[7]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(7);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//下右
void MainWindow::on_DOWN_RIGHT_clicked()
{
    Quanju::x=-1;
    Quanju::y=1;
    Quanju::v1=0.2;
    Quanju::v2=0.4;

    int i=0;
    for(i=0;i<9;i++)
    {
        Quanju::flag[i]=0;
    }
    Quanju::flag[8]=1;
    Quanju::change=1;

    barChange();
    //jietu();

    Service *service1 = new Service(8);
    connect(service1,SIGNAL(send(QString)),this,SLOT(sendmsg(QString)));
    service1->start();
}

//改变线速度刻度条
void MainWindow::on_xian_valueChanged(int value)
{
    Quanju::v1=value*0.001;
    Quanju::change=1;
}

//改变角速度刻度条
void MainWindow::on_jiao_valueChanged(int value)
{
    Quanju::v2=value*0.001;
    Quanju::change=1;

    barChange();
}

//按键事件
void MainWindow::keyPressEvent(QKeyEvent *ev)
{

    if(ev->key() != last_key)
    {
        Quanju::change=1;
        d_flag = 1;
    }

    if(ev->key() == Qt::Key_W)
    {
        Quanju::x=1;
        send();
    }
    if(ev->key() == Qt::Key_S)
    {
        Quanju::x=-1;
        send();
    }
    if(ev->key() == Qt::Key_A)
    {
        Quanju::y=1;
        send();
    }
    if(ev->key() == Qt::Key_D)
    {
        Quanju::y=-1;
        send();
    }
    if(ev->key() == Qt::Key_Q)
    {
        Quanju::x=1;
        Quanju::y=1;
        send();
    }
    if(ev->key() == Qt::Key_E)
    {
        Quanju::x=1;
        Quanju::y=-1;
        send();
    }
    if(ev->key() == Qt::Key_Z)
    {
        Quanju::x=-1;
        Quanju::y=-1;
        send();
    }
    if(ev->key() == Qt::Key_C)
    {
        Quanju::x=-1;
        Quanju::y=1;
        send();
    }
    if(ev->key() == Qt::Key_X)
    {
        Quanju::x=0;
        Quanju::y=0;
        send();
    }
    if(ev->key() == Qt::Key_Up)         //线速度大小调整
    {
      Quanju::v1=Quanju::v1+0.02;
      ui->xian->setValue(Quanju::v1*1000);
      qDebug()<<Quanju::v1<<endl;
    }

    if(ev->key() == Qt::Key_Down)
    {
      Quanju::v1=Quanju::v1-0.02;
      ui->xian->setValue(Quanju::v1*1000);
    }

    if(ev->key() == Qt::Key_Left)      //角速度大小调整
    {
      Quanju::v2=Quanju::v2-0.1;
      ui->jiao->setValue(Quanju::v2*1000);

      barChange();
    }

    if(ev->key() == Qt::Key_Right)
    {
      Quanju::v2=Quanju::v2+0.1;
      ui->jiao->setValue(Quanju::v2*1000);

      barChange();
    }

    last_key = ev->key();

    ev->accept();
}

//按键消息实时发送 socket
void MainWindow::send()
{
	//控制相同命令发送时间为1s
//	QDateTime now_time = QDateTime::currentDateTime();
//	if(now_time.toMSecsSinceEpoch() - last_time.toMSecsSinceEpoch() < 1000 && Quanju::change != 1)
//		return;
//	else
//		last_time = QDateTime::currentDateTime();

    if(s_flag ==0 && d_flag == 0) return;

    QJsonObject json;

    QJsonObject linear;
    linear.insert("x",Quanju::x*Quanju::v1);
    linear.insert("y",0);
    linear.insert("z",0);
    QJsonObject angular;
    angular.insert("x",0);
    angular.insert("y",0);
    angular.insert("z",Quanju::y*Quanju::v2);
    QJsonObject msg;
    msg.insert("linear",linear);
    msg.insert("angular",angular);

    json.insert("op","publish");
    json.insert("topic","/cmd_vel");
    json.insert("msg",msg);
    QJsonDocument json_doc;
    json_doc.setObject(json);
    QString msgss=json_doc.toJson(QJsonDocument::Compact);



    Quanju::websocket.sendTextMessage(msgss);
    Quanju::websocket.flush();
    qDebug()<<msgss<<endl;

    s_flag = 0;
    d_flag = 0;

    if(Quanju::change==1)
    {
        QFile file(path+"/shuju.txt");
        if(!file.open(QIODevice::ReadWrite | QIODevice::Append))
            qDebug()<<file.errorString();
        qDebug()<<path+"/shuju.txt";
        QTextStream out(&file);
        out<<msgss<<" "<<QDateTime::currentDateTime().toMSecsSinceEpoch()<<"\n\r"<<endl;
        file.close();
        Quanju::change=0;

        //jietu();
    }
    barChange();
}

//控制模式选择
void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1=="mode1")
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->jiao->setValue(800);
    }
    else if(arg1=="mode2")
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->jiao->setValue(0);
    }
}

//转盘进度条显示更新
void MainWindow::barChange()
{

    if((Quanju::y==-1 && Quanju::x>=0) || (Quanju::y==1 && Quanju::x<=0) )
    {
        ui->roundProgressBar->setClockwise(true);
    }
    if((Quanju::y==1 && Quanju::x>=0) || (Quanju::y==-1 && Quanju::x<=0))
    {
        ui->roundProgressBar->setClockwise(false);
    }

    ui->roundProgressBar->setValue(Quanju::v2*abs(Quanju::y));

    ui->jiao->setValue(Quanju::v2*1000);   //更新设置角速度刻度条的值
}

//转盘值改变速度值
void MainWindow::changeDial(int i)
{
    if(i<=66)
    {
        ui->dial->setValue(66);
        i=66;
    }
    else if(i>=234)
    {
        ui->dial->setValue(234);
        i=234;
    }

    else if(i>60 && i<=150)
    {
        if(Quanju::x>0)
        Quanju::y=1;
        else
        Quanju::y=-1;

        Quanju::v2=1.6*(150-i)/90;
        //qDebug()<<i<<endl;
        barChange();
    }
    else if(i<240&&i>=150)
    {
        if(Quanju::x>0)
        Quanju::y=-1;
        else
        Quanju::y=1;

        Quanju::v2=1.6*(i-150)/90;
        //qDebug()<<i<<endl;
        barChange();
    }
}

//圆盘
void MainWindow::release()
{
    ui->dial->setValue(150);
}

//图片数据截屏
void MainWindow::jietu()
{
    if (mImage.size().width() <= 0) return;

    if(savePictureCount !=3)
    {
        savePictureCount ++;
        return;
    }

    QImage tmpImg = mImage2;

    Quanju::igs.enqueue(tmpImg.copy());

    QJsonObject json;

    QJsonObject linear;
    linear.insert("x",Quanju::x*Quanju::v1);
    linear.insert("y",0);
    linear.insert("z",0);
    QJsonObject angular;
    angular.insert("x",0);
    angular.insert("y",0);
    angular.insert("z",Quanju::y*Quanju::v2);
    QJsonObject msg;
    msg.insert("linear",linear);
    msg.insert("angular",angular);

    json.insert("op","publish");
    json.insert("topic","/cmd_vel");
    json.insert("msg",msg);
    QJsonDocument json_doc;
    json_doc.setObject(json);
    QString json2msgs=json_doc.toJson(QJsonDocument::Compact);

    Quanju::msgs.enqueue(json2msgs);

    savePictureCount = 0;

}

//线程调用的发消息的槽函数
void MainWindow::sendmsg(QString msg)
{
    Quanju::websocket.sendTextMessage(msg);
    Quanju::websocket.flush();
    qDebug()<<msg<<endl;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::slotGetOneFrame(QImage img)
{
    mImage = img;
    mImage2 = img;
    mImage3 = img;



#if 1
	update();
#endif // 0

   

    if(tuflag)
    {
        jietu();
        i++;   //i为已保存的截图张数
    }
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::DrawRunDirection(QImage & _img, RunCmd _run_dir)
{
	if (mShowDirection)
	{
		DriveAuto::DrawRunDirection(_img, driveHardware.IsRunning(), drivePolicy.PolicyRunCmd());
	}
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameBgraOrg(QImage _img,const QDateTime _time)
{
	if (ui!=NULL){
		this->DrawRunDirection(_img, drivePolicy.PolicyRunCmd());
		QBase::UI_Show_QImage_on_QLabel(ui->label_Image, &_img);
	}	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameBgraSvg(QImage _img, const QDateTime _time)
{
	if (ui != NULL){
		this->DrawRunDirection(_img, drivePolicy.PolicyRunCmd());
		QBase::UI_Show_QImage_on_QLabel(ui->label_Image_svg, &_img);
	}
}
/*----------------------------------------------------------------*/
/**
*录屏
*/
/*----------------------------------------------------------------*/
void MainWindow::on_start_clicked()
{

//    if(m_rect->height()<=0||m_rect->width()<=0)
//    {
//        if(mImage.width()<=0)
//        {
//            qDebug()<<"error no picture";
//            return;
//        }

//        int x = this->geometry().x()+50;
//        int y = this->geometry().y()+75;
//        QImage imge=mImage.scaled(this->size()/1.5,Qt::KeepAspectRatio);
//        int w = imge.width();
//        int h = imge.height();

//        if (x % 2 != 0)
//        {
//            x--;
//            w--;
//        }
//        if (y % 2 != 0)
//        {
//            y--;
//            h--;
//        }
//        if (w % 2 != 0)
//        {
//            w--;
//        }
//        if (h % 2 != 0)
//        {
//            h--;
//        }

//        m_rect->setX(x);
//        m_rect->setY(y);
//        m_rect->setHeight(h);
//        m_rect->setWidth(w);

//        qDebug()<<"x:"<<this->geometry().x()<<" "<<"y:"<<this->geometry().y();
//     }


//    if(m_recordeState==true)
//    {
//        qDebug()<<"is already start!";
//        return;
//    }
//    else
//    {
//        //判断是否已经有m_screenRecorder对象
//        if (m_screenRecorder)
//            delete m_screenRecorder;
//        m_screenRecorder = new ScreenRecorder;
//        m_screenRecorder->setFileName(m_recordPath.toLocal8Bit().data());
//        m_screenRecorder->setVideoFrameRate(25);

//        if (m_screenRecorder->init("screen-capture-recorder",true) == SUCCEED)
//        {
//            qDebug()<<"初始化录屏设备成功";
//            m_screenRecorder->setPicRange(m_rect->x(),m_rect->y(),m_rect->width(),m_rect->height());
//            qDebug()<<m_rect->x()<<" "<<m_rect->x();
//            m_screenRecorder->startRecord();
//            m_recordeState=true;
//            ui->start->setEnabled(false);
//            ui->stop->setEnabled(true);
//        }
//        else
//        {
//            qDebug()<<"提示","出错了,初始化录屏设备失败！";
//            return;
//        }

//        qDebug()<<"开始录制";
//    }
}

//停止录屏
void MainWindow::on_stop_clicked()
{
//    if (m_recordeState != false)
//    {
//        m_screenRecorder->stopRecord();
//        qDebug()<<"停止录制";
//        m_recordeState=false;
//        ui->start->setEnabled(true);
//        ui->stop->setEnabled(false);

//    }
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::RcvOneFrameBgraOrg(QImage _img, const QDateTime _time)
{
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::RcvOneFrameBgraSvg(QImage _img, const QDateTime _time)
{
	
}
/*----------------------------------------------------------------*/
/**
*定时器超时的回调函数
*/
/*----------------------------------------------------------------*/
void MainWindow::timeouts()
{
     qDebug()<<"图片张数:"<<i;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::menu_show_run_direction(bool _v)
{
	this->mShowDirection = _v;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::menu_run_auto(bool _r)
{
	this->mIsCarRunAuto = _r;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::menu_run_current_once(bool _r)
{
	drive_run_policy(drivePolicy.PolicyRunCmd(),1,1);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::run_status_car(bool _s)
{
	if (_s){
				//runing
				if (IsCurrentRunCmdStable()){
					drivePolicy.SetEnable(true);//正常开启策略
				}
				else
				{
					drivePolicy.EnablePolicy(false);//非稳定命令。策略关闭
				}
	}else {
				//stoping
				if (IsCurrentRunCmdStable()) {
					drivePolicy.SetEnable(true);
				}else{
					drivePolicy.EnablePolicy(true);//非稳定命令。策略关闭
				}				
	}

	barChange();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
bool MainWindow::IsCurrentRunCmdStable()
{
	RunCmd cmd_t = drivePolicy.PolicyRunCmd();
	return DriveHardware::IsRunCmdStable(cmd_t);
}
/*----------------------------------------------------------------*/
/**
*截图开始
*/
/*----------------------------------------------------------------*/
void MainWindow::on_tu_startButton_clicked()
{
    tuflag=true;
    ui->tu_startButton->setEnabled(false);
    ui->tu_stopButton->setEnabled(true);

}
/*----------------------------------------------------------------*/
/**
*截图停止
*/
/*----------------------------------------------------------------*/
void MainWindow::on_tu_stopButton_clicked()
{
    tuflag=false;
    ui->tu_startButton->setEnabled(true);
    ui->tu_stopButton->setEnabled(false);
}
/*----------------------------------------------------------------*/
/**
*打开摄像头
*/
/*----------------------------------------------------------------*/
void MainWindow::on_open_cam_clicked()
{
    if(!mPlayer->isRunning())
    {
        mPlayer->startPlay();
    }
}
/*----------------------------------------------------------------*/
/**
*
*/
/*---------------------------------------------------------------*/
void MainWindow::on_close_cam_clicked()
{
    if(mPlayer->isRunning())
    {
        mPlayer->stopPaly();
        mImage = QImage(1920,1080,QImage::Format_RGB888);
        mImage.fill(QColor(240,240,240));
        update();
    }
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkObject()
{
	//视频流接收 多线程
	mPlayer = QSharedPointer<VideoPlayer>(new VideoPlayer());
	mPlayer->SetScale(960, 540);
	
	drivePolicy.moveToThread(&mThreadRunPolicy);
	svgProcImage.moveToThread(&mThreadProcSvg);
	ppImageOrg.moveToThread(&mThreadPreShowBgraOrg);
	ppImageSvg.moveToThread(&mThreadPreShowBgraSvg);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect()
{
	connect(mPlayer.data(), SIGNAL(sig_1_frame_RGB32(QImage, QDateTime)), &ppImageOrg, SLOT(ImageProc(QImage, QDateTime)));
	connect(mPlayer.data(), SIGNAL(sig_1_frame_RGB32(QImage, QDateTime)), &svgProcImage, SLOT(ImageProc(QImage, QDateTime)));
		
	connect(&svgProcImage, SIGNAL(sig_1_frame_bgra(QImage, QDateTime)), &drivePolicy, SLOT(CalSafeArea(QImage, QDateTime)));

	connect(&drivePolicy, SIGNAL(sig_1_frame_bgra(QImage, QDateTime)), &ppImageSvg, SLOT(ImageProc(QImage, QDateTime)));
	
	connect(&drivePolicy,
		SIGNAL(sig_run_cmd(RunCmd,double,double, QDateTime)),
		this,
		SLOT(run_policy(RunCmd,double,double, QDateTime)));
	
	connect(&ppImageOrg, SIGNAL(sig_1_frame_bgra(QImage, QDateTime)), this, SLOT(ShowOneFrameBgraOrg(QImage, QDateTime)));
	connect(&ppImageSvg, SIGNAL(sig_1_frame_bgra(QImage, QDateTime)), this, SLOT(ShowOneFrameBgraSvg(QImage, QDateTime)));

	this->drivePolicy.emitMask_960_540();


	connect(&driveHardware,SIGNAL(running_status(bool)),this,SLOT(run_status_car(bool)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Start()
{
	mPlayer->startPlay();  
	
	mThreadPreShowBgraOrg.start();
	mThreadPreShowBgraSvg.start();
	mThreadProcSvg.start();
	mThreadRunPolicy.start();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Stop()
{
	mPlayer->stopPaly();
	
	mThreadPreShowBgraOrg.quit();
	mThreadPreShowBgraSvg.quit();
	mThreadProcSvg.quit();
	mThreadRunPolicy.quit();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Wait()
{
	mPlayer->wait();

	mThreadPreShowBgraOrg.wait();
	mThreadPreShowBgraSvg.wait();
	mThreadProcSvg.wait();
	mThreadRunPolicy.wait();
}
/*----------------------------------------------------------------*/
/**
*cv::Mat转换成QImage
*/
/*----------------------------------------------------------------*/
QImage MainWindow::cvMat2QImage(const cv::Mat& mat)
{
    if (mat.type() == CV_8UC1)                          // 单通道
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        image.setColorCount(256);                       // 灰度级数256
        for (int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        uchar *pSrc = mat.data;                         // 复制mat数据
        for (int row = 0; row < mat.rows; row++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    else if (mat.type() == CV_8UC3)                     // 3通道
    {
        const uchar *pSrc = (const uchar*)mat.data;     // 复制像素
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);    // R, G, B 对应 0,1,2
        return image.rgbSwapped();                      // rgbSwapped是为了显示效果色彩好一些。
    }
    else if (mat.type() == CV_8UC4)                     // 4通道
    {
        const uchar *pSrc = (const uchar*)mat.data;     // 复制像素
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);        // B,G,R,A 对应 0,1,2,3
        return image.copy();
    }
    else
    {
        return QImage();
    }
}

// QImage转换成cv::Mat
cv::Mat MainWindow::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch (image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
     default:
        break;
    }
    return mat;
}

 //计算像素点距摄像头的实际距离 参数y为像素点的纵坐标
float MainWindow::convert2dist(int y)
{
    //摄像头距地面高度H=115mm
    float H = 115.0;
    //摄像头焦距f=4mm
    float f = 4.0;
    //像素点点距离x x=(H*f/d0)/像素点个数
    float x = (H*f/840)/(780-540);
    //实际距离d d=H*f/h=H*f/(x*像素点个数）
    float d = H*f/(x*abs(y-540));

    return d;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::on_obs_box_activated(const QString &arg1)
{
    if(arg1=="mask1")
    {
        obs_x=900;
        obs_y=600;
        obs_r=50;
    }
    else if(arg1=="mask2")
    {
        obs_x=980;
        obs_y=700;
        obs_r=50;
    }
    else if(arg1=="mask3")
    {
        obs_x=800;
        obs_y=700;
        obs_r=50;
    }
    else if(arg1=="mask4")
    {
        obs_x=900;
        obs_y=880;
        obs_r=50;
    }
    else if(arg1=="mask5")
    {
        obs_x=300;
        obs_y=400;
        obs_r=50;
    }else if(arg1=="mask6")
    {
        obs_x=900;
        obs_y=1040;
        obs_r=50;
    }
}
/*----------------------------------------------------------------*/
/**
*控制相同指令发送的定时器超时函数
*/
/*----------------------------------------------------------------*/
void MainWindow::s_timeout()
{
    s_flag=1;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::run_policy(
	RunCmd _cmd,
	double _speed_v1,
	double _speed_v2,
	QDateTime _time)
{

		if (mIsCarRunAuto) {
			run_policy_interval(
				_cmd,
				_speed_v1,
				_speed_v2,
				_time,
				0);
		}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::run_policy_interval(
	const RunCmd _cmd,
	const double _speed_v1,
	const double _speed_v2,
	const QDateTime _time,
	const int _ms)
{
	const int ms_diff = mRumCmdTime.msecsTo(_time);
	Q_ASSERT(ms_diff > 0);
	if (ms_diff>_ms)
	{
		drive_run_policy(_cmd,_speed_v1,_speed_v2);
		this->mRumCmdTime = _time;
	}
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::drive_run_policy(
	const RunCmd & _cmd,
	const double _speed_v1,
	const double _speed_v2)
{
	driveHardware.run_cmd_policy(_cmd,
								_speed_v1,
								_speed_v2);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/