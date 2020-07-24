#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
#include <QVector4D>
#include <QVector3D>
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class geometry_msgs_Transform
{
private:
	QVector3D			m_translation;
	QVector4D			m_rotation;
public:
	geometry_msgs_Transform();
	~geometry_msgs_Transform();
public:

	QJsonObject getJsonObj();
public:


};