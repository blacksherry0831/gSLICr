#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
#include "ROSBasic.hpp"
/*-----------------------------------*/
#include "geometry_msgs_TransformStamped.hpp"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class tf_tfMessage
{

private:
	QVector<geometry_msgs_TransformStamped>	transforms;
public:
	tf_tfMessage();
	~tf_tfMessage();
public:
	void setTransformStamped(const geometry_msgs_TransformStamped _tf);
public:	
	QJsonObject		getJsonObject();
	QJsonArray		getJsonTfArray();
	QJsonObject		getJsonTfObj();
public:

	QString toJsonStr();

};