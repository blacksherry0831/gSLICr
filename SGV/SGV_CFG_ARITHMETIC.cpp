#include "SGV_CFG_ARITHMETIC.h"
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_OUT_DOOR_HUMAN = "out.door.human";
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_OUT_DOOR_400_IMAGE_STABLE = "out.door.400.image.stable";
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_LAB_SVG = "Method.lab.svg";
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR = "Method.nav.car";
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_CURRENT = "Method.current";
/*-------------------------------------------------------------------------*/
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SuperPixel_Number		= "SuperPixel.Number";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SuperPixel_Compactness = "SuperPixel.Compactness";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SVG_ApparentHorizon_VanishingPoint = "SVG.ApparentHorizon.VanishingPoint";
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_CFG_ARITHMETIC::SGV_CFG_ARITHMETIC(void)
{
	FILE_XML_CFG = "cfg.svg.arithmetic.xml";
	DATA_CFG_PROPERTY = "arithmetic";
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_CFG_ARITHMETIC::~SGV_CFG_ARITHMETIC(void)
{


}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_ARITHMETIC::CreateChildCfgNode(QSharedPointer<QDomDocument> _Xml, QDomElement& _parent)
{

	const QString QS_TRUE = QString::number(1);
#if 1
	createElement_txt_append(
		_Xml,
		_parent,
		NODE_METHOD_OUT_DOOR_HUMAN,
		QS_TRUE);

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_METHOD_OUT_DOOR_400_IMAGE_STABLE,
		QS_TRUE);

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_METHOD_LAB_SVG,
		QS_TRUE);

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_METHOD_NAV_CAR,
		QS_TRUE);

#endif // 1

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_METHOD_CURRENT,
		QString(""));
	
#if 1

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_PROPERTY,
		DATA_CFG_PROPERTY);

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_SuperPixel_Number,
		QString::number(1089));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_SuperPixel_Compactness,
		QString::number(10));

	createElement_txt_append(_Xml,
		_parent,
		NODE_CFG_SVG_ApparentHorizon_VanishingPoint,
		QString::number(0.5));

#endif

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_ARITHMETIC::getMethod_LAB_SVG()
{
	return getIntFromDomDoc_Pro(NODE_METHOD_LAB_SVG);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_ARITHMETIC::getMethod_NAV_CAR()
{
	return getIntFromDomDoc_Pro(NODE_METHOD_NAV_CAR);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
QString SGV_CFG_ARITHMETIC::getMethod_Current()
{
	return	getStringFromDomDoc_Pro(NODE_METHOD_CURRENT);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_ARITHMETIC::getSuperPixel_Number()
{
	return getIntFromDomDoc_Pro(NODE_CFG_SuperPixel_Number);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_ARITHMETIC::getSuperPixel_Compactness()
{
	return getIntFromDomDoc_Pro(NODE_CFG_SuperPixel_Compactness);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float SGV_CFG_ARITHMETIC::getSVG_G_ApparentHorizon_VanishingPoint()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_SVG_ApparentHorizon_VanishingPoint);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/