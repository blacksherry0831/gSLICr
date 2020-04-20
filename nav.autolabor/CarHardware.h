#pragma once
#ifndef _CAR_HARDWARE_H_
#define _CAR_HARDWARE_H_
/*----------------------------------------------------------------*/
#include <QWebSocket>
#include <QQueue>
#include <QImage>
#include <QMutex>
#include <QtCore>
/*----------------------------------------------------------------*/
#include "RunCmd.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
class CarHardware : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit CarHardware(QObject *parent = nullptr);
	~CarHardware();
signals:
	void running_status(bool);
private:
	bool mReconnect;
	bool mIsConnected;
	QUrl mUrl; 
	QWebSocket mWebSocket;
private:
	bool mRunning;
private:
	QQueue<RunCmd> mRunCmdQInPut;
public:
	const QWebSocket* GetWebSocket() const ;
public:
	void open();
	void initConnect();
public:
	bool IsRunning();
public:
	void	WebSocketSendMessage(QString _msg);
	int		WebSocketSendMessageEx(QString _msg);
	QString GetJsonCmd(const float _x, const float _y, const float _v1, const float _v2);
	void sendRunCmdMsg(const float _x, const float _y, const float _v1, const float _v2, const int _ms);
public:
	void up_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void down_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void left_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void right_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void up_left_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void up_right_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void down_left_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void down_right_once(
		const float _v1,
		const float _v2,
		const int _ms);

	void stop_once(
		const float _v1,
		const float _v2,
		const int _ms);
public slots:
	void OnWebSocketConnected();
	void OnWebSocketDisconnected();

	void OnWebSocketError(QAbstractSocket::SocketError _error);

	void run_cmd_policy(const RunCmd & _cmd, const double _speed_v1, const double _speed_v2);

	void sendRunCmd(const float _x, const float _y, const float _v1, const float _v2, const int _ms);

	void EnqueueRunCmdInput(const RunCmd _rc);

	void policy_speed(QQueue<RunCmd> _RunCmdQ, double & _v1, double & _v2);

	bool IsRunCmdStable(RunCmd _cmd);

	int IsRunCmdExecTime(RunCmd _cmd);

	void emit_running_status(const bool _r);

};

#endif 
