#include "advertise_a_topic.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
advertise_a_topic::advertise_a_topic(
	QObject *parent,
	QString _topic,
	QString _type) :rosbridge_v2_0_protocol(parent)
{
	this->m_op = "advertise";
	this->m_topic = _topic;
	this->m_type = _type;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
advertise_a_topic::advertise_a_topic(QObject * parent) :rosbridge_v2_0_protocol(parent)
{
	this->m_op = "advertise";
	this->m_topic = "";
	this->m_type = "";
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
advertise_a_topic::~advertise_a_topic()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject advertise_a_topic::getJsonObject()
{
	QJsonObject obj;
			
	obj.insert("op",	m_op);
	obj.insert("topic",	m_topic);
	obj.insert("type",	m_type);
	
	return obj;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/