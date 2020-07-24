#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
#include "ROSBasic.hpp"
/*-----------------------------------*/
#include "rosbridge_v2_0_protocol.hpp"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class advertise_a_topic : public rosbridge_v2_0_protocol
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit advertise_a_topic(QObject *parent = nullptr);
	Q_INVOKABLE  advertise_a_topic(QObject *parent ,QString _topic,QString _type);
	~advertise_a_topic();

public:
	QJsonObject		getJsonObject();
	
};