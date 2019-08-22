#include "IPrintQ.hpp"
/*-------------------------------------*/
 QMutex   IPrintQ::gMutexPrint;
 bool  IPrintQ::gPrint;
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
IPrintQ::IPrintQ()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
IPrintQ::~IPrintQ()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void IPrintQ::printf_event_q(const QString _event, const QString _msg)
{
	QMutexLocker mutex_t(&gMutexPrint);

	if (gPrint)
	{
		qDebug() << _event << _msg;
	}
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void IPrintQ::printf_event(const std::string _event,const  std::string _msg)
{
	printf_event_q(QString::fromStdString(_event), QString::fromStdString(_msg));
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void IPrintQ::SetPrint(const bool _p)
{
	gPrint = _p;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
