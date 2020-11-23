#include "General.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
General::General()
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
General::~General()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void  General::printThreadId()
{
	QString LogInfo;
	LogInfo.sprintf("%p", QThread::currentThread());
	qDebug()  << "ThreadID : " << LogInfo;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool General::IsEmptyQImage(const QImage* _img)
{
	if (_img->width() + _img->height()>0) {
		return true;
	}
	else
	{
		return false;
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool General::IsEmptyQImage(const QSharedPointer<QImage> _img_ptr)
{
	return IsEmptyQImage(_img_ptr.get());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool General::IsLatestImage(const QDateTime & _time, const qint64 _ms)
{
	const qint64 ms_diff = _time.msecsTo(QDateTime::currentDateTime());

	if (ms_diff<_ms) {
		return true;
	}
	else {
		//qDebug() << ms_diff<<"ms";
	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/