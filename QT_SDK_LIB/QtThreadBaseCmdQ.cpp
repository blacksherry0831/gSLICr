//#include "stdafx.h"
#include "QtThreadBaseCmdQ.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtThreadBaseCmdQ::QtThreadBaseCmdQ(QObject *parent):QtThreadBase(parent)
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtThreadBaseCmdQ::~QtThreadBaseCmdQ(void)
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBaseCmdQ::SetMsgWhileRunning(QSharedPointer<CMD_CTRL> _msg)
{
	if (this->isRunning()) {
		this->SetMsg(_msg);
	}
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/

