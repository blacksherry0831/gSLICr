#include "tf_tfMessage.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
tf_tfMessage::tf_tfMessage()
{
	
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
tf_tfMessage::~tf_tfMessage()
{
	
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject tf_tfMessage::getJsonObject()
{
	QJsonObject PointCloud;
	
	QJsonObject msg= getJsonTfObj();
		
	PointCloud.insert("op", "publish");
	PointCloud.insert("topic", "/tf");
	PointCloud.insert("msg", msg);

	return PointCloud;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonArray tf_tfMessage::getJsonTfArray()
{
	QJsonArray qja;

	for each (auto transform_t in transforms){

		const QJsonObject  qjo_t = transform_t.getJsonObj();
		
		qja.append(qjo_t);
		
	}

	return qja;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QJsonObject tf_tfMessage::getJsonTfObj()
{
	const QJsonArray  transformsArr = getJsonTfArray();
	QJsonObject transforms;
	
	transforms.insert("transforms", transformsArr);

	return transforms;
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
QString tf_tfMessage::toJsonStr()
{
	return  ROSBasic::Json2Str(getJsonObject());
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/
void tf_tfMessage::setTransformStamped(const geometry_msgs_TransformStamped _tf)
{
	transforms.push_back(_tf);
}
/*-------------------------------------*/
/**
*
*/
/*-------------------------------------*/