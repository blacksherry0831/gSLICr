#include "geometry_msgs_TransformStamped.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_TransformStamped::geometry_msgs_TransformStamped(
	const QString	_frame_parent,
	const QString	_frame_id)
{
	this->setChildFrameId(_frame_id);
	this->m_header.setFrameId(_frame_parent);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_TransformStamped::geometry_msgs_TransformStamped()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_TransformStamped::~geometry_msgs_TransformStamped()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject geometry_msgs_TransformStamped::getJsonObj()
{
	QJsonObject TransformStamped_t;
		
	const QJsonObject		header_t=m_header.getJsonObjInc();
	const QJsonObject		transform_t = m_transform.getJsonObj();;
	
	TransformStamped_t.insert("header", header_t);
	TransformStamped_t.insert("child_frame_id",m_child_frame_id);
	TransformStamped_t.insert("transform", transform_t);

	return TransformStamped_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QString geometry_msgs_TransformStamped::toJsonStr()
{
	return QString();
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void geometry_msgs_TransformStamped::setChildFrameId(const QString	_frame_id)
{
	this->m_child_frame_id = _frame_id;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void geometry_msgs_TransformStamped::setTrans(const QVector3D _p3t)
{
	this->m_transform.setTranslation(_p3t);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
