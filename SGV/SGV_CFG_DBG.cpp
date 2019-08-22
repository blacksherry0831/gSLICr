#include "SGV_CFG_DBG.h"
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const QString   SGV_CFG_DBG::NODE_CFG_SAVE_IMG		=	"save.image";
const QString   SGV_CFG_DBG::NODE_CFG_SAVE_DBG		=	"save.debug";
const QString   SGV_CFG_DBG::NODE_CFG_OUTPUT_PATH	=	"output.path";
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_CFG_DBG::SGV_CFG_DBG(void)
{
	FILE_XML_CFG="cfg.svg.dbg.xml";
	DATA_CFG_PROPERTY = "debug";
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_CFG_DBG::~SGV_CFG_DBG(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_DBG::CreateChildCfgNode(QSharedPointer<QDomDocument> _Xml, QDomElement & _parent)
{
	createElement_txt_append(_Xml,_parent, NODE_CFG_PROPERTY, DATA_CFG_PROPERTY);
	createElement_txt_append(_Xml,_parent, NODE_CFG_SAVE_IMG, QString::number(0));
	createElement_txt_append(_Xml,_parent, NODE_CFG_SAVE_DBG, QString::number(0));

	createElement_txt_append(_Xml, _parent, NODE_CFG_OUTPUT_PATH, "E:\\OutPutImg\\");

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_DBG::getImgSave()
{
	return getIntFromDomDoc_Pro(NODE_CFG_SAVE_IMG);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_DBG::getDebugSave()
{
	return getIntFromDomDoc_Pro(NODE_CFG_SAVE_DBG);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
QString SGV_CFG_DBG::getOutputPath()
{
	return getStringFromDomDoc_Pro(NODE_CFG_OUTPUT_PATH);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/