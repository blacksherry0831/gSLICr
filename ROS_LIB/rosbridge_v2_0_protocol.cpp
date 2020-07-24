#include "rosbridge_v2_0_protocol.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
rosbridge_v2_0_protocol::rosbridge_v2_0_protocol(QObject *parent) :QObject(parent)
{
	
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
rosbridge_v2_0_protocol::~rosbridge_v2_0_protocol()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject rosbridge_v2_0_protocol::getJsonObject()
{
	QJsonObject PointCloud;
			
	PointCloud.insert("op", m_op);
	PointCloud.insert("topic", m_topic);

	return PointCloud;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QString rosbridge_v2_0_protocol::toJsonStr()
{
	return  ROSBasic::Json2Str(getJsonObject());
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/