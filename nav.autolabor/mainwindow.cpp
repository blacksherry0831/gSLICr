#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cloudpanel.h"
#include "roundprogressbar.h"
#include <quanju.h>


#pragma execution_character_set("utf-8")

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

	this->initRegisterMetaType();

	this->initParam();
	this->initObject();
		
	this->initMenu();

	
	this->connectTabCfg();

	this->initMainWindowUI();
	this->initMainWindowUI_Connect();
			
	this->InitWebSocket();
		
	this->initThreadWorkConnect();
	this->ThreadWork_Start();

	this->initUiValueGroundPlane();


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
void MainWindow::advertiseTopic()
{
	const QString	topic_front_camera = "/camera_front_point_cloud";
	const QString	type = "sensor_msgs/PointCloud";
	advertise_a_topic a_topic(this, topic_front_camera, type);
	
	if (!mIsAdvertiseTopic){
				mIsAdvertiseTopic = mCarHardware->WebSocketSendMessageEx(a_topic.toJsonStr());
	}
	
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

	this->mIsAdvertiseTopic = false;

	//全局变量初始化
	Quanju::x = 1;
	Quanju::y = 0;
	Quanju::v1 = 0.125;
	Quanju::v2 = 0.8;
	Quanju::change = 0;

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initObject()
{
	this->ThreadWork_Init();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initRegisterMetaType()
{
	qRegisterMetaType<QVector<QVector3D> >("QVector<QVector3D>");
	qRegisterMetaType<QSharedPointer<QImage> >("QSharedPointer<QImage>");
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenu()
{
	this->initMenuVideoDecoder();
	this->initMenuShow();
	this->initMenuRun();
	this->initMenuCollect();
	this->initMenuConnect();
	this->initMenuImageProcessing();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuVideoDecoder()
{
	connect(ui->actionfps1, SIGNAL(triggered()), mImagePlayer.get(), SLOT(fpsOut1()));
	connect(ui->actionfps5, SIGNAL(triggered()), mImagePlayer.get(), SLOT(fpsOut5()));
	connect(ui->actionfps10, SIGNAL(triggered()), mImagePlayer.get(), SLOT(fpsOut10()));
	connect(ui->actionfps25, SIGNAL(triggered()), mImagePlayer.get(), SLOT(fpsOut25()));
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
	connect(ui->actionCollectOnce, SIGNAL(triggered(bool)), &ppImageOrg, SLOT(SetSaveImageOnce(bool)));

	connect(ui->actionCollectOnceTopDown, SIGNAL(triggered(bool)), mImageProcTopDown.get(), SLOT(SetSaveImageOnce(bool)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuConnect()
{
	connect(ui->action_toggle_calibration_SVG_SRC, SIGNAL(triggered(bool)), this, SLOT(menu_toggle_calibration_SVG_SRC(bool)));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuImageProcessing()
{
	connect(ui->actionImageCalibration, SIGNAL(triggered(bool)), mImageProcCal.get(), SLOT(setImageProc(bool)));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMainWindowUI()
{
	//转盘设置
	ui->dial->setMaximum(300);  //最大值
	ui->dial->setMinimum(0);    //最小值
	ui->dial->setValue(150);    //当前值

	//转盘进度条设置 此为控件
	ui->roundProgressBar->setStartAngle(RoundProgressBar::PositionTop);   //起始角度  正上方
	ui->roundProgressBar->setBarStyle(RoundProgressBar::StyleLine);       //风格
	ui->roundProgressBar->setDecimals(2);                                 //设置小数点位数
	ui->roundProgressBar->setClockwise(true);                            //设置是否顺时针
	ui->roundProgressBar->setOutlinePenWidth(18);                         //设置外圆画笔宽度
	ui->roundProgressBar->setDataPenWidth(10);                            //设置外圆画笔宽度
	ui->roundProgressBar->setTextVisible(false);                          //设置文字是否隐形
	ui->roundProgressBar->setRange(0, 6.4);                                //设置角度范围
	ui->roundProgressBar->setValue(0);                                    //设置当前角度
	
	ui->start->setEnabled(true);  //开始录屏 按钮
	ui->stop->setEnabled(false);  //结束录屏 按钮
	
	ui->tu_startButton->setEnabled(true);
	ui->tu_stopButton->setEnabled(false);

	ui->obs_box->setEnabled(false);
	
	ui->stackedWidget->setCurrentIndex(0);  //初始化模式
												//线速度的刻条显示
	ui->xian->setMinimum(0);
	ui->xian->setMaximum(250);
	ui->xian->setValue(125);
	//角速度的刻条显示
	ui->jiao->setMinimum(0);
	ui->jiao->setMaximum(1600);
	ui->jiao->setValue(800);

	this->initMainWindowUI_Tab_CfgCroundPlane();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMainWindowUI_Connect()
{
	connect(ui->dial, SIGNAL(valueChanged(int)), this, SLOT(changeDial(int)));  //转动的角度值改变的话 调用相应函数
	connect(ui->dial, SIGNAL(sliderReleased()), this, SLOT(release()));         //释放
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMainWindowUI_Tab_CfgCroundPlane()
{
	QIntValidator*  qiv = new QIntValidator(0, 2048, this);

	ui->lineEdit_P0_X->setValidator(qiv);
	ui->lineEdit_P1_X->setValidator(qiv);
	ui->lineEdit_P2_X->setValidator(qiv);
	ui->lineEdit_P3_X->setValidator(qiv);

	ui->lineEdit_P0_Y->setValidator(qiv);
	ui->lineEdit_P1_Y->setValidator(qiv);
	ui->lineEdit_P2_Y->setValidator(qiv);
	ui->lineEdit_P3_Y->setValidator(qiv);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::connectTabCfg()
{
	this->connectTabCfgGroundPlane();
	this->connectTabCfgCameraCalibration();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::connectTabCfgGroundPlane()
{
	const QObject* rcv = mImageProcTopDown.get();
		
	connect(ui->radioButton_CalGndManual, SIGNAL(toggled(bool)), this, SLOT(SetCalGndMode(bool)));
	//connect(ui->radioButton_CalGndAuto, SIGNAL(clicked(bool)), this, SLOT(SetCalGndMode(bool)));
	
	connect(ui->pushButton_ReCalGndPlane,SIGNAL(clicked()),rcv,SLOT(reCalGndPlane()));

	connect(ui->doubleSpinBox_DstBoard2Camera,SIGNAL(valueChanged(double)),rcv,SLOT(setDstBoard2Camera(double)));
	connect(ui->spinBox_BoardSize_H, SIGNAL(valueChanged(int)), rcv, SLOT(setBoardSize_H(int)));
	connect(ui->spinBox_BoardSize_W, SIGNAL(valueChanged(int)), rcv, SLOT(setBoardSize_W(int)));

	connect(ui->doubleSpinBox_SquareSize, SIGNAL(valueChanged(double)), rcv, SLOT(setSquareSize(double)));
	connect(ui->comboBox_MapSize, SIGNAL(currentTextChanged(QString)), rcv, SLOT(setMapSize(QString)));
	
#if 1
	connect(ui->lineEdit_P0_X, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_X_P0(const QString &)));
	connect(ui->lineEdit_P1_X, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_X_P1(const QString &)));
	connect(ui->lineEdit_P2_X, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_X_P2(const QString &)));
	connect(ui->lineEdit_P3_X, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_X_P3(const QString &)));

	connect(ui->lineEdit_P0_Y, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_Y_P0(const QString &)));
	connect(ui->lineEdit_P1_Y, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_Y_P1(const QString &)));
	connect(ui->lineEdit_P2_Y, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_Y_P2(const QString &)));
	connect(ui->lineEdit_P3_Y, SIGNAL(textChanged(const QString &)), rcv, SLOT(set_Y_P3(const QString &)));
#endif
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::connectTabCfgCameraCalibration()
{
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initUiValueGroundPlane()
{
	ui->doubleSpinBox_DstBoard2Camera->setValue(1.0);
	ui->spinBox_BoardSize_H->setValue(11);
	ui->spinBox_BoardSize_W->setValue(8);

	ui->doubleSpinBox_SquareSize->setValue(0.03);;
	ui->comboBox_MapSize->setCurrentIndex(6);

#if 1
	ui->lineEdit_P0_X->setText("933");
	ui->lineEdit_P0_Y->setText("836");

	ui->lineEdit_P1_X->setText("1148");
	ui->lineEdit_P1_Y->setText("830");

	ui->lineEdit_P2_X->setText("890");
	ui->lineEdit_P2_Y->setText("964");

	ui->lineEdit_P3_X->setText("1198");
	ui->lineEdit_P3_Y->setText("956");
	
#endif

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::InitWebSocket()
{
	Q_ASSERT(mCarHardware.isNull());
	mCarHardware = QSharedPointer<CarHardware>(new CarHardware());
	mCarHardware->initConnect();
	mCarHardware->open();
	const QWebSocket* p_ws = mCarHardware->GetWebSocket();
	connect(p_ws, SIGNAL(connected()), this, SLOT(onconnected()));
	connect(p_ws, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(p_ws, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorconnected(QAbstractSocket::SocketError)));
}
/*----------------------------------------------------------------*/
/**
*socket连接成功
*/
/*----------------------------------------------------------------*/
void MainWindow::onconnected()
{
   ui->xieche->setText("小车连接成功！");
}
/*----------------------------------------------------------------*/
/**
*socket失去连接
*/
/*----------------------------------------------------------------*/
void MainWindow::disconnected()
{
	if (ui == nullptr) return;
    ui->xieche->setText("小车失去连接！");
}

//小车连接失败
void MainWindow::errorconnected(QAbstractSocket::SocketError error)
{
	if (ui!=nullptr){
		ui->xieche->setText("小车连接失败！");
		qDebug()<<tr("小车连接失败，失败原因：")<<error<<endl;
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
	
 	mCarHardware->WebSocketSendMessageEx(msgss);

    qDebug()<<msgss<<endl;


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
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameBgraOrg(QSharedPointer<QImage> _img_ptr,const QDateTime _time)
{
	ShowOneFrameOnLabel(_img_ptr.get(), &_time, ui->label_Image);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameBgraSvg(QSharedPointer<QImage> _img_ptr, const QDateTime _time)
{
	ShowOneFrameOnLabel(_img_ptr.get(), &_time, ui->label_Image_svg);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameCalibrate(QSharedPointer<QImage> _img_ptr, const QDateTime _time)
{
	ShowOneFrameOnLabel(_img_ptr.data(), &_time, ui->label_calibration);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameTopDown(QSharedPointer<QImage> _img_ptr, const QDateTime _time)
{
	ShowOneFrameOnLabel(_img_ptr.data(), &_time, ui->label_top_down);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameOnLabel(QImage* _img, const QDateTime* _time, QLabel * _qlab)
{
	if (ui != NULL) {
		QBase::UI_Show_QImage_on_QLabel(_qlab, _img);
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

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::menu_toggle_calibration_SVG_SRC(bool _f)
{
	if (_f){
		connect_calibration_SVG();		
	}else{
		connect_calibration_SRC();
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::connect_calibration_SVG()
{
	const QObject *src = mImageProcSVG.get();
	const QObject *cal = mImageProcCal.data();

	disconnect(src,
		SIGNAL(sig_org_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		cal,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));

	connect(src,
		SIGNAL(sig_out_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		cal,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::connect_calibration_SRC()
{
	const QObject *src = mImageProcSVG.get();
	const QObject *cal = mImageProcCal.data();

	disconnect(src,
		SIGNAL(sig_out_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		cal,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));

	connect(src,
		SIGNAL(sig_org_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		cal,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::PublishPointCloud(QVector<QVector3D> _ptc)
{
	const QString	frame_id_parent = "base_link";
	const QString	frame_id = "base_front_camera_link";
	const QString	topic_front_camera = "/camera_front_point_cloud";
	const QString	type = "sensor_msgs/PointCloud";

	advertiseTopic();

	geometry_msgs_TransformStamped tf_camera_front(frame_id_parent, frame_id);

	tf_tfMessage tf_t;
	tf_t.setTransformStamped(tf_camera_front);

	SensorMsgsPointCloud pointscloud(this, topic_front_camera, frame_id);
	
	//pointscloud.SimulatePointsCircle();
	pointscloud.setPoints(_ptc);

	mCarHardware->WebSocketSendMessageEx(tf_t.toJsonStr());
	mCarHardware->WebSocketSendMessageEx(pointscloud.toJsonStr());
}
/*----------------------------------------------------------------*/
/**
*打开摄像头
*/
/*----------------------------------------------------------------*/
void MainWindow::on_open_cam_clicked()
{
    if(!mImagePlayer->isRunning())
    {
		mImagePlayer->startPlay();
    }
}
/*----------------------------------------------------------------*/
/**
*
*/
/*---------------------------------------------------------------*/
void MainWindow::on_close_cam_clicked()
{
    if(mImagePlayer->isRunning())
    {
		mImagePlayer->stopPaly();
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
void MainWindow::initThreadWorkConnect()
{
	this->initThreadWorkConnect_SVG();
	this->initThreadWorkConnect_Calibration();
	this->initThreadWorkConnect_TopDown();


	this->initThreadWorkConnect_PreImageShow();
	this->initThreadWorkConnect_ImageShow();
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_PreImageShow()
{

	connect(mImageProcSVG.get(),
		SIGNAL(sig_org_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		&ppImageOrg,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));

	connect(mImageProcSVG.get(),
		SIGNAL(sig_out_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		&ppImageSvg,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_ImageShow()
{

	connect(&ppImageOrg,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameBgraOrg(QSharedPointer<QImage>, QDateTime)));
	
	connect(&ppImageSvg,
		SIGNAL(sig_1_frame_RGB32_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameBgraSvg(QSharedPointer<QImage>, QDateTime)));

	connect(mImageProcCal.get(),
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameCalibrate(QSharedPointer<QImage>, QDateTime)));

	QObject* topDown = mImageProcTopDown.get();
	connect(topDown,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameTopDown(QSharedPointer<QImage>, QDateTime)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_Calibration()
{
	
	connect(mImageProcSVG.get(),
		SIGNAL(sig_org_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		mImageProcCal.get(),
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_SVG()
{
	connect(mImagePlayer.get(),
		SIGNAL(sig_1_frame_RGB32_ref(QSharedPointer<QImage>, QDateTime)),
		mImageProcSVG.get(),
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_TopDown()
{
	QObject* procCal = mImageProcCal.get();
	QObject* topDown = mImageProcTopDown.get();
	
	Q_ASSERT(procCal != Q_NULLPTR);
	Q_ASSERT(topDown != Q_NULLPTR);
	
	connect(procCal,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		topDown,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));
	
	connect(topDown,
		SIGNAL(sig_point_cloud(QVector<QVector3D>)),
		this,
		SLOT(PublishPointCloud(QVector<QVector3D>)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Init()
{
	this->ThreadWork_Init_obj();
	this->ThreadWork_Init_thread();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Init_obj()
{
	mImagePlayer= QSharedPointer<VideoPlayer>(new VideoPlayer("rtsp://192.168.99.201/stream1"));
	mImagePlayer->SetScale(1920, 1080);
	
	mImageProcSVG=QSharedPointer<SVG_PROC_IMAGE>(new SVG_PROC_IMAGE());
	mImageProcCal=QSharedPointer<ImageProcCalibration>(new ImageProcCalibration());
	mImageProcTopDown=QSharedPointer<ImageProcTopDown>(new ImageProcTopDown());
			
	m_thread_obj.push_back(mImageProcSVG);
	m_thread_obj.push_back(mImageProcCal);
	m_thread_obj.push_back(mImageProcTopDown);
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Init_thread()
{

	for each (auto obj_p in m_thread_obj)
	{
		QSharedPointer<QThread> thread_t = QSharedPointer<QThread>(new QThread());
		obj_p->moveToThread(thread_t.get());
		m_thread_pool.push_back(thread_t);
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Start()
{
	mImagePlayer->startPlay();
	
	for each (auto thread in  m_thread_pool)
	{
		thread->start();
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Stop()
{
	mImagePlayer->stopPaly();
	
	for each (auto thread in  m_thread_pool)
	{
		thread->quit();
	}
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ThreadWork_Wait()
{
	mImagePlayer->wait();

	for each (auto thread in  m_thread_pool)
	{
		thread->wait();
	}
	
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
	mCarHardware->run_cmd_policy(_cmd,
								_speed_v1,
								_speed_v2);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::SetCalGndMode(bool _s)
{
	 ImageProcTopDown* rcv_top_down = mImageProcTopDown.get();

	rcv_top_down->setCalGndMode(!_s);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/