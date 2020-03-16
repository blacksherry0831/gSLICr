#include "DrivePolicy.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DrivePolicy::DrivePolicy(QObject *parent) :QObject(parent)
{
	qRegisterMetaType<RunCmd>("RunCmd");
	this->InitArea_960_540();
	this->mEnable = true;
	mRunCmd = RunCmd::GO_NONE;
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
void DrivePolicy::CLearRunCmd()
{
	mRunCmdQ.clear();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::EnqueueRunCmd(const RunCmd _rc)
{

	mRunCmdQ.enqueue(_rc);

	if (mRunCmdQ.size()>100) {
		mRunCmdQ.dequeue();
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::EnqueueExecCmd(const RunCmd _rc)
{

	mExecCmdQ.enqueue(_rc);

	if (mExecCmdQ.size()>100) {
		mExecCmdQ.dequeue();
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CollectRunCmd(const RunCmd _rc)
{

	if (IsEnable()){
		EnqueueRunCmd(_rc);
	}else{
		CLearRunCmd();
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
RunCmd DrivePolicy::policy_dir_weight_avg()
{
	const float W[] = { 0.1F,0.2F, 0.3F, 0.4F, 0.5F, 0.6F, 0.7F, 0.8F,0.9F };
	const int RunDirCount = RunCmd::GO_UP_LEFT;
	const int RunCmdSize = 9;
	const int QSZ = mRunCmdQ.size();
	const int StartCmd = QSZ - RunCmdSize;

	std::vector<float> statistics(RunDirCount, 0);

	RunCmd rc_wa_t = RunCmd::GO_NONE;
	if (StartCmd>0) {

		for (size_t i = 0; i <RunCmdSize; i++) {
			const RunCmd cmd_t = mRunCmdQ.at(StartCmd + i);
			Q_ASSERT(cmd_t >= 0 && cmd_t <= 8);
			statistics[cmd_t] += W[i];
		}

		const int pos = FindMaxPos(statistics);
		rc_wa_t = (RunCmd) pos;
	}

	return rc_wa_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int DrivePolicy::FindMaxPos(std::vector<float> _vec)
{
	std::vector<float>::iterator biggest = std::max_element(_vec.begin(), _vec.end()); 	
	return std::distance(_vec.begin(), biggest);
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
	polygon2 << QPointF(960, 620) << QPointF(1073, 620) << QPointF(1514, 850) << QPointF(960, 850) << QPointF(960, 620);  //安全区a2
	polygon3 << QPointF(540, 850) << QPointF(960, 850) << QPointF(960, 1045) << QPointF(280, 1045) << QPointF(540, 850);   //安全区a3
	polygon4 << QPointF(960, 850) << QPointF(1514, 850) << QPointF(1640, 1045) << QPointF(960, 1045) << QPointF(960, 850);   //安全区a4
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
	this->InitPolygonArea_960_540();
	this->InitImageArea_960_540();
	this->InitPointSet_960_540();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::emitMask_960_540()
{
	emit sig_1_frame_bgra(mImgArea_960_540, QDateTime::currentDateTime());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::InitColor()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::InitImageArea_960_540()
{
	mImgArea_960_540 = QImage(960, 540, QImage::Format::Format_ARGB32);

	mImgArea_960_540.fill(Qt::darkBlue);

	QPainter painter(&mImgArea_960_540);
	painter.setPen(QPen(Qt::white, 3));
	
	painter.setBrush(QBrush(color1));
	painter.drawPolygon(polygon1,Qt::FillRule::WindingFill);

	painter.setBrush(QBrush(color2));
	painter.drawPolygon(polygon2);

	painter.setBrush(QBrush(color3));
	painter.drawPolygon(polygon3);

	painter.setBrush(QBrush(color4));
	painter.drawPolygon(polygon4);

	painter.setBrush(QBrush(color5));
	painter.drawPolygon(polygon5);

	painter.setBrush(QBrush(color6));
	painter.drawPolygon(polygon6);

		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::InitPolygonArea_960_540()
{
	polygon1 << QPointF(750 / 2, 620 / 2) << QPointF(960 / 2, 620 / 2) << QPointF(960 / 2, 945 / 2) << QPointF(220 / 2, 945 / 2) << QPointF(750 / 2, 620 / 2);   //安全区a1
	polygon2 << QPointF(960 / 2, 620 / 2) << QPointF(1170 / 2, 620 / 2) << QPointF(1700 / 2, 945 / 2) << QPointF(960 / 2, 945 / 2) << QPointF(960 / 2, 620 / 2);  //安全区a2
	polygon3 << QPointF(220 / 2, 945 / 2) << QPointF(960 / 2, 945 / 2) << QPointF(960 / 2, 1045 / 2) << QPointF(57 / 2, 1045 / 2) << QPointF(220 / 2, 945 / 2);   //安全区a3
	polygon4 << QPointF(960 / 2, 945 / 2) << QPointF(1700 / 2, 945 / 2) << QPointF(1863 / 2, 1045 / 2) << QPointF(960 / 2, 1045 / 2) << QPointF(960 / 2, 945 / 2);   //安全区a6
	polygon5 << QPointF(57 / 2, 1045 / 2) << QPointF(960 / 2, 1045 / 2) << QPointF(960 / 2, 1080 / 2) << QPointF(0 / 2, 1080 / 2) << QPointF(57 / 2, 1045 / 2);   //安全区a5
	polygon6 << QPointF(960 / 2, 1045 / 2) << QPointF(1863 / 2, 1045 / 2) << QPointF(1920 / 2, 1080 / 2) << QPointF(960 / 2, 1080 / 2) << QPointF(960 / 2, 1045 / 2);   //安全区a6
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::InitPointSet_960_540()
{
	const int WIDTH = mImgArea_960_540.width();
	const int HEIGHT = mImgArea_960_540.height();
	const int SZ = WIDTH*HEIGHT;
	const int* _data = (const int*)mImgArea_960_540.bits();

	for (int xi = 0; xi < WIDTH; xi++) {
			for (int yi = 0; yi < HEIGHT; yi++){
			
						const int IDX = xi + yi*WIDTH;
						const int PIXEL = _data[IDX];
						const cv::Point point_t(xi,yi);
						if (color1 == PIXEL){
							pointSet1.push_back(point_t);
						}else if (color2 == PIXEL){
							pointSet2.push_back(point_t);
						}else if (color3 == PIXEL){
							pointSet3.push_back(point_t);
						}else if (color4 == PIXEL){
							pointSet4.push_back(point_t);
						}else if (color5 == PIXEL){
							pointSet5.push_back(point_t);
						}else if(color6 == PIXEL){
							pointSet6.push_back(point_t);
						}else{
			
						}

			}

	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CountVerticalOnArea(
	const int* _pixel_data,
	const int&  _w,
	const int&  _h,
	const std::vector<cv::Point>& _point_set,
	const int& _v,
	int & _a_count)
{
	for each(const cv::Point& p in _point_set) {
		const int idx = p.x + p.y*_w;
		if (_v == _pixel_data[idx]) {
			_a_count++;
		}
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::CalSafeAreaLatest(const QImage & _img, const QDateTime& _time)
{

	if (IsLatestImage(_time)) {
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
	emit sig_1_frame_bgra(mImgArea_960_540, QDateTime::currentDateTime());
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
	const int V = 0xE0ff0000;
	
	CountVerticalOnArea(_data, WIDTH, HEIGHT, pointSet1, V, a1);
	CountVerticalOnArea(_data, WIDTH, HEIGHT, pointSet2, V, a2);
	CountVerticalOnArea(_data, WIDTH, HEIGHT, pointSet3, V, a3);
	CountVerticalOnArea(_data, WIDTH, HEIGHT, pointSet4, V, a4);
	CountVerticalOnArea(_data, WIDTH, HEIGHT, pointSet5, V, a5);
	CountVerticalOnArea(_data, WIDTH, HEIGHT, pointSet6, V, a6);
		
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
		
	this->policy_img_normal();

	if (IsEnable()){
		policy_dir(_img,_time);
	}
	
	emit sig_1_frame_bgra(_img, _time);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::policy_dir_speed(
	const QImage & _img,
	const QDateTime & _time)
{
	double speed_v1 = 1.0F;
	double speed_v2 = 1.0F;
		
	const RunCmd cmd_t = policy_dir_weight_avg();

	EnqueueExecCmd(cmd_t);

	policy_speed(mExecCmdQ,speed_v1, speed_v2);

	emit_sig_run_cmd(cmd_t, speed_v1, speed_v2, _time);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::policy_dir(const QImage & _img, const QDateTime & _time)
{
	double speed_v1 = 1.0F;
	double speed_v2 = 1.0F;

	const RunCmd cmd_t = policy_dir_weight_avg();

	EnqueueExecCmd(cmd_t);

	emit_sig_run_cmd(cmd_t, speed_v1, speed_v2, _time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::policy_img_normal()
{
	const RunCmd rc_t = policy_normal();

	CollectRunCmd(rc_t);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::emit_sig_run_cmd(RunCmd _cmd,double _v1,double _v2,QDateTime _time)
{
	mRunCmd = _cmd;
	emit sig_run_cmd(mRunCmd,_v1,_v2,_time);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
RunCmd DrivePolicy::policy_normal()
{
	RunCmd rc_t = GO_NONE;

	if (a5>0 || a6>0) {
		if (a5>a6) {
			rc_t = GO_DOWN_LEFT;
		}
		else {
			rc_t = GO_DOWN_RIGHT;
		}
	}
	else if (a3>0 || a4>0) {
		if (a3>a4) {
			rc_t = GO_RIGHT;
		}
		else {
			rc_t = GO_LEFT;
		}
	}
	else if (a1>0 || a2>0) {
		if (a1>a2) {
			rc_t = GO_UP;
		}
		else {
			rc_t = GO_UP;
		}
	}
	else {
		rc_t = GO_UP;
	}
	return rc_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::policy_speed(
	QQueue<RunCmd> _RunCmdQ,
	double& _v1,
	double& _v2)
{
	if (_RunCmdQ.size()<2) {
		return;
	}
	Q_ASSERT(_RunCmdQ.size()>=2);
	const int QSZ = _RunCmdQ.size();
	const RunCmd past_cmd = _RunCmdQ.at(QSZ-2);
	const RunCmd now_cmd = _RunCmdQ.at(QSZ-1);

	_v1 = 1;
	_v2 = 1;
	
	if (((now_cmd==RunCmd::GO_LEFT) ||(now_cmd==RunCmd::GO_RIGHT) )&&
		((past_cmd==RunCmd::GO_LEFT) ||	(past_cmd==RunCmd::GO_RIGHT))){
			_v1 = 2;
			_v2 = 2;
	}else	if (now_cmd==RunCmd::GO_DOWN){
			_v1 = 2;
			_v2 = 2;
	}else if (now_cmd == RunCmd::GO_DOWN_LEFT){
			_v1 = 3;
			_v2 = 3;
	}else if (now_cmd == RunCmd::GO_DOWN_RIGHT){
			_v1 = 3;
			_v2 = 3;
	}else{
		_v1 = 1;
		_v2 = 1;
	}

	Q_ASSERT(_v1>0 && _v2>0);
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::SetEnable(bool _en)
{
	this->mEnable = _en;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool DrivePolicy::IsEnable()
{
	return mEnable;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DrivePolicy::EnablePolicy(bool _en)
{
	SetEnable(_en);
	CLearRunCmd();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
RunCmd DrivePolicy::PolicyRunCmd()
{
	return mRunCmd;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/