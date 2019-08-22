//#include "stdafx.h"
#include "QtMsgCmdQ.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtMsgCmdQ::QtMsgCmdQ()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtMsgCmdQ::~QtMsgCmdQ(void)
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtMsgCmdQ::SetMsg(QSharedPointer<CMD_CTRL> _msg)
{
	mCmdMsgQ.setCmd(_msg);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QSharedPointer<CMD_CTRL> QtMsgCmdQ::GetMsg()
{
	return mCmdMsgQ.getCmd();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtMsgCmdQ::ClearMsg()
{
	mCmdMsgQ.clear();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
int QtMsgCmdQ::Qsize()
{
	return mCmdMsgQ.QueueSize();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtMsgCmdQ::SetMsgWhileRunning(QSharedPointer<CMD_CTRL> _msg)
{
	this->SetMsg(_msg);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtMsgCmdQ::ProcMsg()
{
	QSharedPointer<CMD_CTRL> cmd_t = this->GetMsg();

	if (!cmd_t.isNull())
	{
		this->ProcMsgEx(cmd_t);
	}
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtMsgCmdQ::ProcMsgEx(QSharedPointer<CMD_CTRL> _msg)
{

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/