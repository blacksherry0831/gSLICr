#pragma once
/*-------------------------------------*/
#include "cpp_basic.h"
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
#include "IPrintQ.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class QBase: public IPrintQ
{
public:
	QBase(void);
	~QBase(void);
public:
   	static  std::string   SYS_getCurrentTime(const std::string _format);
	static  QString      SYS_getCurrentTime_Q(const QString _format);
public:
	static  QString  uint2Qstring(uint _num);
	static  QString  GetVectorFloat(const std::vector<float> _float);
	static  std::vector<float>  CvtStr2VectorF(QString _float,QString _split=" ");
public:
	static void	fs_write_xml(const QString _save_full_path,const QSharedPointer<QDomDocument> _Xml);
	static  QSharedPointer<QDomDocument>	fs_read_xml(const QString _save_full_path);
public:
	static void UI_Show_QImage_on_QLabel(QLabel * _qlab, QImage * const  _p_qimg);
};

