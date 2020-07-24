#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
#include "ROSBasic.hpp"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class rosbridge_v2_0_protocol : public QObject
{
public:
	Q_INVOKABLE explicit rosbridge_v2_0_protocol(QObject *parent = nullptr);
	~rosbridge_v2_0_protocol();
protected:
	QString m_op;
	QString m_topic;
	QString m_type;
public:
	virtual QJsonObject		getJsonObject();
	virtual QString			toJsonStr();

};