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
	this->initUICfg();

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

	const int		topicLen = 5;
	const QString	topic[topicLen] = {
		ROS_topic_f_cam_svg_pointcloud,
		ROS_topic_f_cam_tsign_pose_red,
		ROS_topic_f_cam_tsign_pose_yellow,
		ROS_topic_f_cam_tsign_pose_green,
		ROS_topic_f_cam_tsign_pointcloud

	};
	const QString	topicType[topicLen] = {
		SensorMsgsPointCloud::sensor_msgs__PointCloud ,
		geometry_msgs_PoseStamped::geometry_msgs__PoseStamped,
		geometry_msgs_PoseStamped::geometry_msgs__PoseStamped,
		geometry_msgs_PoseStamped::geometry_msgs__PoseStamped,
		SensorMsgsPointCloud::sensor_msgs__PointCloud ,
	};
	
	for (size_t ti = 0; ti < topicLen; ti++){
		if (!mIsAdvertiseTopic[ti]) {
			mIsAdvertiseTopic[ti] = advertiseTopicOne(topic[ti], topicType[ti]);
		}
	}
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int MainWindow::advertiseTopicOne(
	const QString _topic,
	const QString _type)
{
	advertise_a_topic a_topic(
		this,
		_topic,
		_type);
	const int IsAdvertise = mCarHardware->WebSocketSendMessageEx(a_topic.toJsonStr());	
	return IsAdvertise;	
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

	memset(this->mIsAdvertiseTopic, 0, sizeof(this->mIsAdvertiseTopic));
	
	//全局变量初始化
	Quanju::x = 1;
	Quanju::y = 0;
	Quanju::v1 = 0.125;
	Quanju::v2 = 0.8;
	Quanju::change = 0;

	this->mAirViewTf=QSharedPointer<ImgProcAirView>(new ImgProcAirView());

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
void MainWindow::initUICfg()
{
	this->mMW_CFG = QSharedPointer<MW_CFG_KV>(new MW_CFG_KV());

	this->mMW_CFG->InitLoad();

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

	connect(ui->actionCollectOnceTopDown, SIGNAL(triggered(bool)), mImageProcTopDownSVG.get(), SLOT(SetSaveImageOnce(bool)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuConnect()
{
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initMenuImageProcessing()
{
	connect(ui->actionImageCalibration, SIGNAL(triggered(bool)), mImageProcCalSVG.get(), SLOT(setImageProc(bool)));
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
	const QObject* rcv = mImageProcTopDownSVG.get();
		
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

	const float cam2board	= this->mMW_CFG->getFrontCamDst2Board();
	const float board_h		= this->mMW_CFG->getFrontCamBoardH();
	const float board_w		= this->mMW_CFG->getFrontCamBoardW();
	const float board_c		= this->mMW_CFG->getFrontCamSzBoardCell();
	const float map_sz		= this->mMW_CFG->getFrontCamSzMap();

	const std::vector<QString> a_x = this->mMW_CFG->getFrontCamAffineX_QStr();
	const std::vector<QString> a_y = this->mMW_CFG->getFrontCamAffineY_QStr();

	ui->doubleSpinBox_DstBoard2Camera->setValue(cam2board);
	ui->spinBox_BoardSize_H->setValue(board_h);
	ui->spinBox_BoardSize_W->setValue(board_w);

	ui->doubleSpinBox_SquareSize->setValue(board_c);;
	ui->comboBox_MapSize->setCurrentIndex(map_sz);

#if 1
	ui->lineEdit_P0_X->setText(a_x.at(0));
	ui->lineEdit_P0_Y->setText(a_y.at(0));

	ui->lineEdit_P1_X->setText(a_x.at(1));
	ui->lineEdit_P1_Y->setText(a_y.at(1));

	ui->lineEdit_P2_X->setText(a_x.at(2));
	ui->lineEdit_P2_Y->setText(a_y.at(2));

	ui->lineEdit_P3_X->setText(a_x.at(3));
	ui->lineEdit_P3_Y->setText(a_y.at(3));
	
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
	mCarHardware = QSharedPointer<CarHardware>(new CarHardware(URL_ROS_WS));
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
void MainWindow::ShowOneFrameBgraOrg(
	QSharedPointer<QImage> _img_ptr,
	const QDateTime _time)
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
void MainWindow::ShowOneFrameCalibrateOrg(QSharedPointer<QImage> _img_ptr, const QDateTime _time)
{
	ShowOneFrameOnLabel(_img_ptr.data(), &_time, ui->label_calibration_org);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::ShowOneFrameTopDownOrg(QSharedPointer<QImage> _img_ptr, const QDateTime _time)
{
	ShowOneFrameOnLabel(_img_ptr.data(), &_time, ui->label_top_down_org);
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

}
/*----------------------------------------------------------------*/
/**
*停止录屏
*/
/*----------------------------------------------------------------*/
void MainWindow::on_stop_clicked()
{

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
void MainWindow::publishPointCloud(
	QString _topic,
	QString _frame_base,
	QString _frame_sensor,
	QVector<QVector3D> _ptc)
{
	SensorMsgsPointCloud pointscloud_t(
		this,
		_topic,
		_frame_sensor);

	pointscloud_t.setPoints(_ptc);
	mCarHardware->WebSocketSendMessageEx(pointscloud_t.toJsonStr());
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::publishPointCloud_FrameCamrea(
	QString _topic,
	QVector<QVector3D> _ptc)
{
	publishPointCloud(
		_topic,
		ROS_frame_id_base,
		ROS_frame_id_camera,
		_ptc);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::publishPose(
	QString _topic, 
	QVector3D _p3t,
	QVector4D _p4t)
{
	geometry_msgs_PoseStamped  ts_pose(ROS_frame_id_camera);
	ts_pose.setTopic(_topic);
	ts_pose.setPose(_p3t,_p4t);

	const QString poseMsg = ts_pose.toPubMsgsPoseJsonStr();
	
	mCarHardware->WebSocketSendMessageEx(poseMsg);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::publishTF_Camera()
{
	geometry_msgs_TransformStamped tf_camera_front(ROS_frame_id_base, ROS_frame_id_camera);
	tf_tfMessage tf_t;
	tf_t.setTransformStamped(tf_camera_front);
	mCarHardware->WebSocketSendMessageEx(tf_t.toJsonStr());
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::PublishPointCloud_TS(QVector<QVector3D> _ptc)
{
	advertiseTopic();
	publishTF_Camera();
	publishPointCloud_FrameCamrea(
		ROS_topic_f_cam_tsign_pointcloud,
		_ptc);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::PublishPose_TS(QString _color,QVector3D _p3t, QVector4D _p4t)
{
	advertiseTopic();
	publishTF_Camera();

	const QString	topic[3] = {		
		ROS_topic_f_cam_tsign_pose_red,
		ROS_topic_f_cam_tsign_pose_yellow,
		ROS_topic_f_cam_tsign_pose_green,
	};

	for each(auto var in topic) {	
		if (var.contains(_color)) {
			this->publishPose(var,_p3t,_p4t);
		}
	}
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::PublishPointCloud_SVG(QVector<QVector3D> _ptc)
{
	advertiseTopic();	
	publishTF_Camera();
	publishPointCloud_FrameCamrea(
		ROS_topic_f_cam_svg_pointcloud,
		_ptc);
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
	this->initThreadWorkConnect_Calibration_Org();

	this->initThreadWorkConnect_TopDown();
	this->initThreadWorkConnect_TopDown_Org();

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
	

	this->initThreadWorkConnect_ImageShow_CalSvg();
	this->initThreadWorkConnect_ImageShow_CalOrg();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_ImageShow_CalOrg()
{
	QObject* cal = mImageProcCalOrg.get();
	QObject* topDown = mImageProcTopDownOrg.get();

	connect(cal,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameCalibrateOrg(QSharedPointer<QImage>, QDateTime)));
	
	connect(topDown,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameTopDownOrg(QSharedPointer<QImage>, QDateTime)));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_ImageShow_CalSvg()
{
	QObject* cal = mImageProcCalSVG.get();
	QObject* birdSvg = mImageProcTopDownSVG.get();

	connect(cal,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		this,
		SLOT(ShowOneFrameCalibrate(QSharedPointer<QImage>, QDateTime)));
	
	connect(birdSvg,
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
		SIGNAL(sig_out_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		mImageProcCalSVG.get(),
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_Calibration_Org()
{
	connect(mImageProcSVG.get(),
		SIGNAL(sig_org_frame_bgra(QSharedPointer<QImage>, QDateTime)),
		mImageProcCalOrg.get(),
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
	QObject* procCal = mImageProcCalSVG.get();
	QObject* topDown = mImageProcTopDownSVG.get();
	
	Q_ASSERT(procCal != Q_NULLPTR);
	Q_ASSERT(topDown != Q_NULLPTR);
	
	connect(procCal,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		topDown,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));
	
	connect(topDown,
		SIGNAL(sig_point_cloud(QVector<QVector3D>)),
		this,
		SLOT(PublishPointCloud_SVG(QVector<QVector3D>)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void MainWindow::initThreadWorkConnect_TopDown_Org()
{
	QObject* procCal = mImageProcCalOrg.get();
	QObject* topDown = mImageProcTopDownOrg.get();

	Q_ASSERT(procCal != Q_NULLPTR);
	Q_ASSERT(topDown != Q_NULLPTR);

	connect(procCal,
		SIGNAL(sig_1_frame_bgra_ref(QSharedPointer<QImage>, QDateTime)),
		topDown,
		SLOT(ImageProc(QSharedPointer<QImage>, QDateTime)));

	connect(topDown,
		SIGNAL(sig_point_cloud(QVector<QVector3D>)),
		this,
		SLOT(PublishPointCloud_TS(QVector<QVector3D>)));

	connect(topDown,
		SIGNAL(sig_pose_position_orientation(QString,QVector3D, QVector4D)),
		this,
		SLOT(PublishPose_TS(QString,QVector3D, QVector4D)));

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
	mImagePlayer= QSharedPointer<VideoPlayer>(new VideoPlayer(URL_RTSP_STREAM.toStdString()));
	mImagePlayer->SetScale(IMG_W, IMG_H);
	
	mImageProcSVG=QSharedPointer<SVG_PROC_IMAGE>(new SVG_PROC_IMAGE());
	mImageProcCalSVG=QSharedPointer<ImageProcCalibration>(new ImageProcCalibration());

	mImageProcTopDownSVG=QSharedPointer<ImageProcTopDownSVG>(new ImageProcTopDownSVG());
	mImageProcTopDownSVG->setAirViewTf(mAirViewTf);	

	mImageProcCalOrg = QSharedPointer<ImageProcCalibration>(new ImageProcCalibration());

	mImageProcTopDownOrg = QSharedPointer<ImageProcTopDownTrafficSign>(new ImageProcTopDownTrafficSign());
	mImageProcTopDownOrg->setAirViewTf(mAirViewTf);

	m_thread_obj.push_back(mImageProcSVG);
	m_thread_obj.push_back(mImageProcCalSVG);
	m_thread_obj.push_back(mImageProcTopDownSVG);

	m_thread_obj.push_back(mImageProcCalOrg);
	m_thread_obj.push_back(mImageProcTopDownOrg);
		
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
	 ImageProcTopDown* rcv_top_down = mImageProcTopDownSVG.get();

	rcv_top_down->setCalGndMode(!_s);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/