#pragma once
/*-----------------------------------------*/
#include <QtCore>
#include <QThread>
#include <QImage>
#include <QQueue>
#include <QMetaType>
#include <QDebug>
/*-----------------------------------------*/
#include <opencv2\opencv.hpp>
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
class General :public QObject
{
    Q_OBJECT
public:
    explicit General();
    ~General();
public:
	void static printThreadId();

	static bool IsEmptyQImage(const QImage * _img);
	static bool IsEmptyQImage(const QSharedPointer<QImage>  _img_ptr);
	
	static bool IsLatestImage(const QDateTime& _time, const qint64 _ms);

	


};