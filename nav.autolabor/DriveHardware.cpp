#include "DriveHardware.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DriveHardware::DriveHardware(QObject *parent):QObject(parent)
{
	init_param();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
DriveHardware::~DriveHardware()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void DriveHardware::init_param()
{
	path = "D://shuju";
	mRunning = false;
	mTimer=QSharedPointer<QTimer>(new QTimer());

	connect(mTimer.data(), SIGNAL(timeout()), this, SLOT(car_stop()));
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
bool DriveHardware::IsRunning()
{
	return mRunning;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::up_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = 1;
	const float y = 0;
	
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::down_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = -1;
	const float y = 0;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::left_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = 0;
	const float y = 1;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::right_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = 0;
	const float y = -1;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::up_left_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = 1;
	const float y = 1;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::up_right_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = 1;
	const float y = -1;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::down_left_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = -1;
	const float y = -1;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

void DriveHardware::down_right_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = -1;
	const float y = 1;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::stop_once(
	const float _v1,
	const float _v2,
	const int _ms)
{
	const float x = 0;
	const float y = 0;
	sendRunCmd(
		x,
		y,
		_v1,
		_v2,
		_ms);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::SaveJsonCmd(QString _msgss)
{
	if (Quanju::change == 1)
	{
		QFile file(path + "/shuju.txt");
		if (!file.open(QIODevice::ReadWrite | QIODevice::Append))
			qDebug() << file.errorString();
		qDebug() << path + "/shuju.txt";
		QTextStream out(&file);
		out << _msgss << " " << QDateTime::currentDateTime().toMSecsSinceEpoch() << "\n\r" << endl;
		file.close();
		Quanju::change = 0;
	}
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
QString DriveHardware::GetJsonCmd(
	const float _x,
	const float _y,
	const float _v1,
	const float _v2)
{

	const float V1 = 0.125*_v1;
	const float V2 = 0.8*_v2;

	QJsonObject json;

	QJsonObject linear;
	linear.insert("x", _x*V1);
	linear.insert("y", 0);
	linear.insert("z", 0);
	QJsonObject angular;
	angular.insert("x", 0);
	angular.insert("y", 0);
	angular.insert("z", _y*V2);
	QJsonObject msg;
	msg.insert("linear", linear);
	msg.insert("angular", angular);

	json.insert("op", "publish");
	json.insert("topic", "/cmd_vel");
	json.insert("msg", msg);
	QJsonDocument json_doc;
	json_doc.setObject(json);
	QString msgss = json_doc.toJson(QJsonDocument::Compact);
	return msgss;
}
/*----------------------------------------------------------------*/
/**
*按键消息实时发送 socket
*/
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/**
*按键消息实时发送 socket
*/
/*----------------------------------------------------------------*/
void DriveHardware::sendRunCmd(
	const float _x,
	const float _y,
	const float _v1,
	const float _v2,
	const int	_ms)
{

		Q_ASSERT(IsRunning() == false);
		const QString msgss = GetJsonCmd(_x,_y,_v1,_v2);

		emit_running_status(true);
		Quanju::WebSocketSendMessage(msgss);
		qDebug() << msgss << endl;
		SaveJsonCmd(msgss);
		mTimer->setSingleShot(true);
		mTimer->start(_ms);

	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::emit_running_status(const bool _r)
{
	mRunning = _r;
	emit running_status(mRunning);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::car_stop()
{
	emit_running_status(false);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::run_cmd_policy(
	const RunCmd & _cmd,
	const double _speed_v1,
	const double _speed_v2)
{

	if (IsRunning() == true) {
		return;
	}else{

			double speed_v1=1;
			double speed_v2 = 1;

			this->EnqueueRunCmdInput(_cmd);

			this->policy_speed(mRunCmdQInPut,speed_v1,speed_v2);

			const int exec_ms = IsRunCmdExecTime(_cmd);

			switch (_cmd)
			{
			case RunCmd::GO_DOWN:
				this->down_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_DOWN_LEFT:
				this->down_left_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_DOWN_RIGHT:
				this->down_right_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_RIGHT:
				this->right_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_LEFT:
				this->left_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_UP_RIGHT:
				this->up_right_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_UP_LEFT:
				this->up_left_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_UP:
				this->up_once(speed_v1, speed_v2, exec_ms);
				break;
			case RunCmd::GO_NONE:
				break;
			case RunCmd::GO_STOP:
				this->stop_once(speed_v1, speed_v2, exec_ms);
				break;
			default:
				break;
			}		
	}
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
bool DriveHardware::IsRunCmdStable(RunCmd _cmd)
{

	if ((_cmd == RunCmd::GO_UP) ||
		(_cmd == RunCmd::GO_DOWN) ||
		(_cmd == RunCmd::GO_UP_RIGHT) ||
		(_cmd == RunCmd::GO_UP_LEFT)) {
		return	true;
	}
	else {
		return	false;
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int DriveHardware::IsRunCmdExecTime(RunCmd _cmd)
{

	if (IsRunCmdStable(_cmd)) {
		return 800;
	}
	else {
		return 2000;
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::EnqueueRunCmdInput(const RunCmd _rc)
{

	mRunCmdQInPut.enqueue(_rc);

	if (mRunCmdQInPut.size()>100) {
		mRunCmdQInPut.dequeue();
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void DriveHardware::policy_speed(
	QQueue<RunCmd> _RunCmdQ,
	double& _v1,
	double& _v2)
{
	if (_RunCmdQ.size()<2) {
		return;
	}
	Q_ASSERT(_RunCmdQ.size() >= 2);
	const int QSZ = _RunCmdQ.size();
	const RunCmd past_cmd = _RunCmdQ.at(QSZ - 2);
	const RunCmd now_cmd = _RunCmdQ.at(QSZ - 1);

	_v1 = 1;
	_v2 = 1;

	if (((now_cmd == RunCmd::GO_LEFT) || (now_cmd == RunCmd::GO_RIGHT)) &&
		((past_cmd == RunCmd::GO_LEFT) || (past_cmd == RunCmd::GO_RIGHT))) {
		_v1 = 2;
		_v2 = 2;
	}
	else	if (now_cmd == RunCmd::GO_DOWN) {
		_v1 = 2;
		_v2 = 2;
	}
	else if (now_cmd == RunCmd::GO_DOWN_LEFT) {
		_v1 = 3;
		_v2 = 3;
	}
	else if (now_cmd == RunCmd::GO_DOWN_RIGHT) {
		_v1 = 3;
		_v2 = 3;
	}
	else {
		_v1 = 1;
		_v2 = 1;
	}

	Q_ASSERT(_v1>0 && _v2>0);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/