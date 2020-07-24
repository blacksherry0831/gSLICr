#include "ROSBasic.hpp"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
ROSBasic::ROSBasic()
{
	
}
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
ROSBasic::~ROSBasic()
{
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
QString ROSBasic::Json2Str(const QJsonObject _q_jo)
{

	QJsonDocument json_doc;
	json_doc.setObject(_q_jo);
	const QString msgss = json_doc.toJson(QJsonDocument::Compact);
	return msgss;

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
QString ROSBasic::Json2Str(const QJsonArray _q_ja)
{
	QJsonDocument json_doc;
	json_doc.setArray(_q_ja);
	const QString msgss = json_doc.toJson(QJsonDocument::Compact);
	return msgss;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/