#pragma once

#include "cpp_stl.h"

#include  "qt_basic.h"

#include "QT_SDK_LIB/QtTcpClientBase.hpp"
/*-------------------------------------*/
#define HEART_BEAT_FREQUENCY (5)
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class QtTcpClientCmdCtrl :public QtTcpClientBase
{
	Q_OBJECT
public:
	explicit QtTcpClientCmdCtrl(QObject *parent = Q_NULLPTR);
	~QtTcpClientCmdCtrl(void);

public:
	int Send_1_cmd(CMD_CTRL *_cmd);
	int Read_1_cmd(CMD_CTRL *_cmd);
	int Read_1_cmd_fast(CMD_CTRL *_cmd);
	int getByteTcpRead();
public:
	int SendHearbeatCmd(int _need_resp);

};