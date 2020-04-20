#include <CarHardware.h>
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
CarHardware::CarHardware(QObject *parent) :QObject(parent)
{
	this->mReconnect = true;
	this->mIsConnected = false;
	this->mUrl = "ws://192.168.0.10:9090";
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
CarHardware::~CarHardware()
{
	mWebSocket.close();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const QWebSocket * CarHardware::GetWebSocket() const
{
	return &mWebSocket;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::open()
{
	this->mWebSocket.open(mUrl);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::initConnect()
{

	connect(&mWebSocket, SIGNAL(connected()), this, SLOT(OnWebSocketConnected()));
	connect(&mWebSocket, SIGNAL(disconnected()), this, SLOT(OnWebSocketDisconnected()));
	connect(&mWebSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(OnWebSocketError(QAbstractSocket::SocketError)));

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::WebSocketSendMessage(QString _msg)
{
		mWebSocket.sendTextMessage(_msg);
		mWebSocket.flush();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int CarHardware::WebSocketSendMessageEx(QString _msg)
{
	if (mIsConnected) {
		WebSocketSendMessage(_msg);
		return 1;
	}else{
		return 0;
	}
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
QString CarHardware::GetJsonCmd(
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
*
*/
/*----------------------------------------------------------------*/
void CarHardware::sendRunCmdMsg(
	const float _x,
	const float _y,
	const float _v1,
	const float _v2,
	const int	_ms)
{
	const QString msgss = GetJsonCmd(_x, _y, _v1, _v2);
	this->WebSocketSendMessageEx(msgss);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::up_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::down_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::left_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::right_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::up_left_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::up_right_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::down_left_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::down_right_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::stop_once(const float _v1, const float _v2, const int _ms)
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
void CarHardware::OnWebSocketConnected()
{
	this->mIsConnected = true;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::OnWebSocketDisconnected()
{
	this->mIsConnected = false;

	this->open();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
bool CarHardware::IsRunning()
{
	return mRunning;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::OnWebSocketError(QAbstractSocket::SocketError _error)
{
	qDebug()  << _error << endl;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::run_cmd_policy(
	const RunCmd & _cmd,
	const double _speed_v1,
	const double _speed_v2)
{

	if (IsRunning() == true) {
		return;
	}
	else {

		double speed_v1 = 1;
		double speed_v2 = 1;

		this->EnqueueRunCmdInput(_cmd);

		this->policy_speed(mRunCmdQInPut, speed_v1, speed_v2);

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
void CarHardware::sendRunCmd(
	const float _x,
	const float _y,
	const float _v1,
	const float _v2,
	const int	_ms)
{

	Q_ASSERT(IsRunning() == false);
	const QString msgss = GetJsonCmd(_x, _y, _v1, _v2);

	emit_running_status(true);
	//Quanju::WebSocketSendMessage(msgss);
	qDebug() << msgss << endl;

	

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void CarHardware::EnqueueRunCmdInput(const RunCmd _rc)
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
void CarHardware::policy_speed(
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

bool  CarHardware::IsRunCmdStable(RunCmd _cmd)
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
int CarHardware::IsRunCmdExecTime(RunCmd _cmd)
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
void CarHardware::emit_running_status(const bool _r)
{
	mRunning = _r;
	emit running_status(mRunning);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/