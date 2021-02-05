#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
#include "ROSBasic.hpp"
/*-----------------------------------*/
#include "std_msgs_Header.hpp"
#include "geometry_msgs_Pose.hpp"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class geometry_msgs_PoseStamped
{
public:
	geometry_msgs_PoseStamped(const QString	_frame_id);

	geometry_msgs_PoseStamped();
	~geometry_msgs_PoseStamped();
public:
	static const QString geometry_msgs__PoseStamped;
private:
	std_msgs_Header				m_header;
	
	geometry_msgs_Pose			m_pose;
private:
	QString mTopic;
public:
	void setTopic(const QString _t);
	void setPose(QVector3D _p3t,QVector4D _p4t);
public:
	QJsonObject getJsonObj();
	QJsonObject getPubMsgsPoseJsonObj();
	QString		toPubMsgsPoseJsonStr();
	
public:
	

};