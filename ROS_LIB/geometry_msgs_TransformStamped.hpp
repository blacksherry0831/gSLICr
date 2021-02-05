#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
#include "std_msgs_Header.hpp"
#include "geometry_msgs_Transform.hpp"
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class geometry_msgs_TransformStamped
{
private:
	std_msgs_Header				m_header;
	QString						m_child_frame_id;
	geometry_msgs_Transform		m_transform;
public:

	geometry_msgs_TransformStamped(
		const QString	_frame_parent,
		const QString	_frame_id);

	geometry_msgs_TransformStamped();
	~geometry_msgs_TransformStamped();
public:
	QJsonObject getJsonObj();
	QString toJsonStr();
public:
	void setChildFrameId(const QString	_frame_id);
};