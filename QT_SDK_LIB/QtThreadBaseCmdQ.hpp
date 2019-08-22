#pragma once
/*-------------------------------------*/
#include "cpp_stl.h"
/*-------------------------------------*/
#include "QT_SDK_LIB/QBase.h"
#include "QT_SDK_LIB/QtThreadBase.hpp"
/*-------------------------------------*/
#include "QtMsgCmdQ.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class QtThreadBaseCmdQ :public QtThreadBase,public QtMsgCmdQ
{
	Q_OBJECT
public:
	explicit QtThreadBaseCmdQ(QObject *parent = Q_NULLPTR);
	~QtThreadBaseCmdQ(void);
protected:
public:
	virtual void SetMsgWhileRunning(QSharedPointer<CMD_CTRL> _msg);

};