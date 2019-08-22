//#include "stdafx.h"
#include "QtThreadBase.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtThreadBase::QtThreadBase(QObject *parent):QThread(parent)
{
	this->M_THREAD_RUN = true;
	this->MAX_MSECS = 30000;
	
	QTime t;
	t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);

	this->IDENTIFY=qrand();

	mThreadName = __func__;
	mSleepTime = 0;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QtThreadBase::~QtThreadBase(void)
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::emit_status_message(const QString & _msg)
{
	
		QString msg_t;

		msg_t.append(mThreadName).append(", ")
			.append(_msg).append(" ");

		printf_event_q(objectName(), _msg);

		emit status_message(msg_t);
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::SleepMy(int _ms)
{
	const int SLEEP_100MS = 100;
	do {

		QThread::msleep(SLEEP_100MS);
		_ms -= SLEEP_100MS;
		mSleepTime += SLEEP_100MS;

	} while (M_THREAD_RUN  &&_ms > 0);

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::startServer()
{
	this->M_THREAD_RUN = true;
	this->start();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::closeServer()
{
	this->closeServerAsync();
}
/*-------------------------------------*/
/**
*Òì²½
*/
/*-------------------------------------*/
void QtThreadBase::closeServerAsync()
{
	this->M_THREAD_RUN = false;
	quit();
}
/*-------------------------------------*/
/**
*Í¬²½
*/
/*-------------------------------------*/
void QtThreadBase::closeServerSync()
{
	this->closeServerAsync();
	this->wait4ServerClose();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::run()
{
	this->before_enter_thread();
	this->enter_thread();

	while (M_THREAD_RUN)
	{
		this->run_thread_work();
	}

	this->exit_thread();
	this->after_exit_thread();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::wait4ServerClose()
{
	int count = 0;
	while (this->isRunning()) {

		QThread::sleep(1);
		this->emit_status_message(QString("wait for thread done").append(QString::number(count++)));

	}
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::run_thread_work()
{

}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::emit_thread_stopping()
{
	emit thread_running_state(FALSE);
	this->emit_status_message(mStatusMessage = "Thread>>  shutdown");
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::exit_thread()
{
	this->emit_thread_stopping();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::emit_thread_starting()
{
	emit thread_running_state(TRUE);
	this->emit_status_message(mStatusMessage = "Thread>> Ctrl Thread Start");
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::enter_thread()
{
	this->emit_thread_starting();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::after_exit_thread()
{
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void QtThreadBase::before_enter_thread()
{
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/