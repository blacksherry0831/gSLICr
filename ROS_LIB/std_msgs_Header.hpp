#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class std_msgs_Header
{
private:
	uint32_t		m_seq;
	uint32_t		m_stamp_sec;
	uint32_t		m_stamp_nsec;
	std::string		m_frame_id;
public:
	void setFrameId(const QString	_frame_id);
public:
	std_msgs_Header();
	~std_msgs_Header();
public:
	void Inc();
	QJsonObject getJsonObj();
public:
	QJsonObject getJsonObjInc();

};