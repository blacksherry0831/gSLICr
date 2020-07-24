#include "std_msgs_Header.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
std_msgs_Header::std_msgs_Header()
{
	m_seq=0;
	m_stamp_sec= QDateTime::currentDateTime().toSecsSinceEpoch();
	m_stamp_nsec=0;
	m_frame_id="unknow frame";
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
std_msgs_Header::~std_msgs_Header()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void std_msgs_Header::Inc()
{
	m_seq++;
	const QDateTime	time_t= QDateTime::currentDateTime();
	m_stamp_sec = time_t.toSecsSinceEpoch();
	m_stamp_nsec = time_t.time().msec()*1000;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject std_msgs_Header::getJsonObj()
{

	QJsonObject header;
	QJsonObject stamp;

	stamp.insert("secs", (qint64)m_stamp_sec);
	stamp.insert("nsecs", (qint64)m_stamp_nsec);

	header.insert("seq", (qint64)m_seq);
	header.insert("stamp", stamp);
	header.insert("frame_id", QString::fromStdString(m_frame_id));

	return header;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject std_msgs_Header::getJsonObjInc()
{
	Inc();
	return getJsonObj();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void std_msgs_Header::setFrameId(const QString	_frame_id)
{
	this->m_frame_id = _frame_id.toStdString();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/