#pragma once
/*-------------------------------------*/
#include "opencv_stl.h"
/*-------------------------------------*/
#include <QString>
#include <QSharedPointer>
/*-------------------------------------*/
#include <QDateTime> 
#include <QtNetwork>
#include <QThread>
#include <QtXml>
#include <QtWidgets>
/*-------------------------------------*/

/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class OpencvQtBase
{
public:
	OpencvQtBase(void);
	~OpencvQtBase(void);
public:
	static QSharedPointer<QImage> getPtrQImage(IplImage* const img);
public:
	static  IplImage* CloneIplImage(const QImage* qImage);

	static  IplImage* getIplImagePtr(const QImage* qImage);

	static QImage::Format getQFormat(const IplImage* const _img);

	static  void CopyIplImage2QImage(const IplImage* const img,QImage* qImage);
	static  void CopyQImage2IplImage(IplImage * img, const QImage*  qImage);

	static  QImage* CloneQImage(const IplImage* const img);
	static  QImage CloneQImageEx(const IplImage* const img);

	static void InitImageHeader(IplImage* _img,const QImage* qImage);

};

