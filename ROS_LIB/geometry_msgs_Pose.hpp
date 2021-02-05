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
class geometry_msgs_Pose
{
private:
	QVector3D			m_position;
	QVector4D			m_orientation;
public:
	geometry_msgs_Pose();
	~geometry_msgs_Pose();
public:
	static const QString geometry_msgs__Pose;
public:
	QJsonObject getJsonObj();
public:
	void setPose(QVector3D _p3t, QVector4D _p4t);

};