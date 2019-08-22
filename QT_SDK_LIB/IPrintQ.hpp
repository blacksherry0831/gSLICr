#pragma once
#ifndef IPRINTQ_HPP
#define IPRINTQ_HPP
/*-------------------------------------*/
#include "cpp_basic.h"
/*-------------------------------------*/
#include <QMutex>
#include <QString>
#include <QtCore>
#include <QtGlobal>
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class IPrintQ
{
public:
	IPrintQ();
	~IPrintQ();
private:
	static  QMutex   gMutexPrint;
	static  bool  gPrint;
public:
	static void SetPrint(const bool _p);
	static void printf_event(const std::string _event, const std::string _msg="");
	static void printf_event_q(const QString _event, const QString _msg);
	
};
/*-------------------------------------*/
#endif