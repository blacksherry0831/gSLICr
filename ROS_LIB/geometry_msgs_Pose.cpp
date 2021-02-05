#include "geometry_msgs_Pose.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
const QString geometry_msgs_Pose::geometry_msgs__Pose="geometry_msgs/Pose";
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_Pose::geometry_msgs_Pose()
{
	this->m_orientation.setX(0);
	this->m_orientation.setY(0);
	this->m_orientation.setZ(0);
	this->m_orientation.setW(1);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_Pose::~geometry_msgs_Pose()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void geometry_msgs_Pose::setPose(QVector3D _p3t, QVector4D _p4t)
{
	this->m_position	= _p3t;
	this->m_orientation = _p4t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject geometry_msgs_Pose::getJsonObj()
{

	QJsonObject Transform;	
	
	QJsonObject position;
	QJsonObject orientation;
	
	position.insert("x", m_position.x());
	position.insert("y", m_position.y());
	position.insert("z", m_position.z());

	orientation.insert("x", m_orientation.x());
	orientation.insert("y", m_orientation.y());
	orientation.insert("z", m_orientation.z());
	orientation.insert("w", m_orientation.w());

	Transform.insert("position", position);
	Transform.insert("orientation", orientation);

	return Transform;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/