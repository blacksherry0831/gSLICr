#pragma once
#ifndef _DriveHardware_H
#define _DriveHardware_H

#include <QThread>
#include <QtWebSockets/QtWebSockets>

#include "quanju.h"

#include "RunCmd.h"

class DriveHardware : public QObject
{
    Q_OBJECT

public:
	DriveHardware(QObject *parent=0);
	~DriveHardware();
private:
	void init_param();
private:
	QSharedPointer<QTimer>	mTimer;
private:
	QQueue<RunCmd> mRunCmdQInPut;
private:
	bool mRunning;
public:
	bool IsRunning();
public:
	QString path;      //数据文件路径
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

public:
	void SaveJsonCmd(QString _msgss);
	
	static QString GetJsonCmd(
		const float _x,
		const float _y,
		const float _v1,
		const float _v2);

	
	void sendRunCmd(
		const float _x,
		const float _y,
		const float _v1,
		const float _v2,
		const int _ms);
public:
	void emit_running_status(bool _r);
	void run_cmd_policy(const RunCmd & _cmd, const double _speed_v1, const double _speed_v2);
	static bool	IsRunCmdStable(RunCmd _cmd);
	static int	IsRunCmdExecTime(RunCmd _cmd);
	void EnqueueRunCmdInput(const RunCmd _rc);
	void policy_speed(QQueue<RunCmd> _RunCmdQ, double & _v1, double & _v2);
private slots:
	
	void car_stop();



signals:
    void running_status(bool);
};

#endif // SERVICE_H
