#pragma once
/*-------------------------------------*/
#include "cpp_stl.h"
/*-------------------------------------*/
#include <QObject>
#include <QtCore>
#include <QThread>
/*-------------------------------------*/
#include "QT_SDK_LIB/QBase.h"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class QtThreadBase :public QThread,public IPrintQ
{
	Q_OBJECT
public:
	explicit QtThreadBase(QObject *parent = Q_NULLPTR);
	~QtThreadBase(void);
protected:
	//定义自己需要的方法或变量  
	bool M_THREAD_RUN;
	int  MAX_MSECS;
	int IDENTIFY;
	unsigned long mSleepTime;
protected:
	QString mStatusMessage;
	QString mThreadName;
	std::string mEvent;
	void emit_status_message(const QString& _msg);
	
public:
	void SleepMy(int _ms=100);
	void startServer();
	void closeServer();
	void closeServerAsync();
	void closeServerSync();
	void wait4ServerClose();
protected:
	virtual void emit_thread_starting();
	virtual void emit_thread_stopping();
protected:
	virtual void before_enter_thread();
	virtual void after_exit_thread();
	virtual void enter_thread();
	virtual void exit_thread();
protected:

public: 
	virtual void run();
	virtual void run_thread_work();	

signals:
		void status_message(const QString& _msg);
		void thread_running_state(int);

};