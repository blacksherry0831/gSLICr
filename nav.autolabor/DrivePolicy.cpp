#include "DrivePolicy.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DrivePolicy::DrivePolicy(QObject *parent) :QObject(parent)
{
	qRegisterMetaType<DrivePolicy::RunCmd>("DrivePolicy::RunCmd");
	this->InitArea_960_540();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DrivePolicy::~DrivePolicy()
{
	ClearArea();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool DrivePolicy::IsLatestImage(const QDateTime & _time, const int64& _ms)
{
	const qint64 ms_diff = _time.msecsTo(QDateTime::currentDateTime());

	if (ms_diff<_ms) {
		return true;
	}else {
		qDebug() << ms_diff << "ms";
	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::ClearArea()
{
	a1 = a2 = a3 = a4 = a5 = a6 = none = 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::InitArea_1920_1080()
{
	polygon1 << QPointF(847, 620) << QPointF(960, 620) << QPointF(960, 850) << QPointF(540, 850) << QPointF(847, 620);   //安全区a1
	polygon2 << QPointF(960, 620) << QPointF(1073, 620) << QPointF(1380, 850) << QPointF(960, 850) << QPointF(960, 620);  //安全区a2
	polygon3 << QPointF(540, 850) << QPointF(960, 850) << QPointF(960, 1045) << QPointF(280, 1045) << QPointF(540, 850);   //安全区a5
	polygon4 << QPointF(960, 850) << QPointF(1380, 850) << QPointF(1640, 1045) << QPointF(960, 1045) << QPointF(960, 850);   //安全区a6
	polygon5 << QPointF(280, 1045) << QPointF(960, 1045) << QPointF(960, 1075) << QPointF(240, 1075) << QPointF(280, 1045);   //安全区a5
	polygon6 << QPointF(960, 1045) << QPointF(1640, 1045) << QPointF(1680, 1075) << QPointF(960, 1075) << QPointF(960, 1045);   //安全区a6
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::InitArea_960_540()
{
	polygon1 << QPointF(847	/ 2, 620 / 2) << QPointF(960 / 2, 620 / 2) << QPointF(960 / 2, 850 / 2) << QPointF(540 / 2, 850 / 2) << QPointF(847 / 2, 620 / 2);   //安全区a1
	polygon2 << QPointF(960 / 2, 620 / 2) << QPointF(1073 / 2, 620 / 2) << QPointF(1380 / 2, 850 / 2) << QPointF(960 / 2, 850 / 2) << QPointF(960 / 2, 620 / 2);  //安全区a2
	polygon3 << QPointF(540 / 2, 850 / 2) << QPointF(960 / 2, 850 / 2) << QPointF(960 / 2, 1045 / 2) << QPointF(280 / 2, 1045 / 2) << QPointF(540 / 2, 850 / 2);   //安全区a5
	polygon4 << QPointF(960 / 2, 850 / 2) << QPointF(1380 / 2, 850 / 2) << QPointF(1640 / 2, 1045 / 2) << QPointF(960 / 2, 1045 / 2) << QPointF(960 / 2, 850 / 2);   //安全区a6
	polygon5 << QPointF(280 / 2, 1045 / 2) << QPointF(960 / 2, 1045 / 2) << QPointF(960 / 2, 1075 / 2) << QPointF(240 / 2, 1075 / 2) << QPointF(280 / 2, 1045 / 2);   //安全区a5
	polygon6 << QPointF(960 / 2, 1045 / 2) << QPointF(1640 / 2, 1045 / 2) << QPointF(1680 / 2, 1075 / 2) << QPointF(960 / 2, 1075 / 2) << QPointF(960 / 2, 1045 / 2);   //安全区a6
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CalSafeAreaLatest(const QImage & _img, const QDateTime& _time)
{

	if (IsLatestImage(_time,1000)) {
		CalSafeAreaFast(_img,_time);
	}else{
		qDebug() <<"CalSafeAreaFast time out" ;
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CalSafeAreaFast(const QImage & _img, const QDateTime& _time)
{

		const int W = _img.width();
		const int H = _img.height();

		if (1920 == W &&
			1080 == H) {
			CalSafeArea_1920_1080(_img);
		}else if (960 == W &&
			540 == H) {
			CalSafeArea_960_540(_img);
		}else {

		}

		this->policy(_img,_time);
				
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CalSafeArea(const QImage _img, const QDateTime _time)
{

	CalSafeAreaLatest(_img, _time);

	

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CalSafeArea_1920_1080(const QImage & _img)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CalSafeArea_960_540(const QImage & _img)
{
	TimeMeasure tm("CalSafeArea_960_540");

	const int WIDTH = _img.width();
	const int HEIGHT = _img.height();
	const int SZ = WIDTH*HEIGHT;
	const int* _data = (const int*)_img.bits();
	
	this->ClearArea();
	
	for (int xi = 0; xi < WIDTH; xi++){

		for (size_t yi = 0; yi < HEIGHT; yi++)
		{
			const int IDX = xi + yi*WIDTH;
			const QPointF qpf(xi,yi);
			if (0xE0ff0000 == _data[IDX]) {

				if (polygon1.containsPoint(qpf, Qt::OddEvenFill))
				{
					a1++;
				}
				else if (polygon2.containsPoint(qpf, Qt::OddEvenFill))
				{
					a2++;
				}
				else if (polygon3.containsPoint(qpf, Qt::OddEvenFill))
				{
					a3++;
				}
				else if (polygon4.containsPoint(qpf, Qt::OddEvenFill))
				{
					a4++;
				}
				else if (polygon5.containsPoint(qpf, Qt::OddEvenFill))
				{
					a5++;
				}
				else if (polygon6.containsPoint(qpf, Qt::OddEvenFill))
				{
					a6++;
				}
				else
				{
					none++;
				}

			}

		}
				
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int DrivePolicy::Qimage2cvMat(QImage& _img)
{
	cv::Mat mat;

	mat.create(_img.height(), _img.width(), CV_8UC4);
	
	Q_ASSERT(_img.byteCount()== mat.total() * mat.elemSize());

	memcpy(mat.ptr<uchar>(0), _img.bits(),_img.byteCount());
		
	return 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::policy(const QImage & _img,const QDateTime& _time)
{
	RunCmd rc_t= GO_NONE;

	if (a5>0 || a6>0) {
		if (a5>a6) {
			rc_t = GO_DOWN_LEFT;
		}else {
			rc_t = GO_DOWN_RIGHT;
		}
	}else if (a3>0 || a4>0) {
		if (a3>a4) {
			rc_t = GO_RIGHT;
		}else{
			rc_t = GO_LEFT;
		}
	}else if (a1>0 || a2>0){
		if (a1>a2){
			rc_t = GO_UP_RIGHT;
		}else{
			rc_t = GO_UP_LEFT;
		}
	}else{
			rc_t = GO_UP;
	}
	
	emit sig_run_cmd(rc_t, _time);
	emit sig_1_frame_bgra(_img, _time);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/