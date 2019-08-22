#pragma once
/*-------------------------------------*/
#include "cpp_stl.h"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
#include "CMD_CTRL_Q.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class QtMsgCmdQ
{
public:
	QtMsgCmdQ();	
	~QtMsgCmdQ();
private:
	CMD_CTRL_Q mCmdMsgQ;
public:
	void SetMsg(QSharedPointer<CMD_CTRL> _msg);
	QSharedPointer<CMD_CTRL> GetMsg();
	void ClearMsg();
	int Qsize();
public:
	virtual void SetMsgWhileRunning(QSharedPointer<CMD_CTRL> _msg);
	virtual void ProcMsg();
	virtual void ProcMsgEx(QSharedPointer<CMD_CTRL> _msg);
};