#include "geometry_msgs_PoseStamped.hpp"
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
const QString geometry_msgs_PoseStamped::geometry_msgs__PoseStamped = "geometry_msgs/PoseStamped";
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_PoseStamped::geometry_msgs_PoseStamped(
	const QString	_frame_id)
{
	this->m_header.setFrameId(_frame_id);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_PoseStamped::geometry_msgs_PoseStamped()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
geometry_msgs_PoseStamped::~geometry_msgs_PoseStamped()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject geometry_msgs_PoseStamped::getJsonObj()
{
	QJsonObject poseStamped_t;
		
	const QJsonObject		header_t=m_header.getJsonObjInc();
	const QJsonObject		pose_t = m_pose.getJsonObj();;
	
	poseStamped_t.insert("header", header_t);
	poseStamped_t.insert("pose", pose_t);

	return poseStamped_t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject geometry_msgs_PoseStamped::getPubMsgsPoseJsonObj()
{
	QJsonObject PointCloud;

	QJsonObject msg = getJsonObj();

	PointCloud.insert("op", "publish");
	PointCloud.insert("topic", mTopic);
	PointCloud.insert("msg", msg);

	return PointCloud;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void geometry_msgs_PoseStamped::setTopic(const QString _t)
{
	this->mTopic = _t;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void geometry_msgs_PoseStamped::setPose(QVector3D _p3t, QVector4D _p4t)
{
	this->m_pose.setPose(_p3t,_p4t);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QString		geometry_msgs_PoseStamped::toPubMsgsPoseJsonStr()
{
	return  ROSBasic::Json2Str(getPubMsgsPoseJsonObj());
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/