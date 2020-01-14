#pragma once
/*-----------------------------------*/
#include <QtCore>
#include <QtNetwork>
#include <QSharedPointer>
#include <QThread>
#include <QImage>
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
class QImage_Q
{
public:
	
public:
	QImage_Q();
	~QImage_Q();
private:
	QMutex mutex;
	QQueue<QImage> mQ;
public:
	void clear();
private:
	void init();
	void destory();
public:
	int QueueSize();
public:
	QImage getQImage();
	void setQImage(const QImage _img);

};