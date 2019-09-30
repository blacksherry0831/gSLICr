#include "SGV_CFG_ARITHMETIC.h"
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_OUT_DOOR_HUMAN = "out.door.human";
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_OUT_DOOR_400_IMAGE_STABLE = "out.door.400.image.stable";
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_LAB_SVG = "Method.lab.svg";
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR = "Method.nav.car";
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR_CLUSTER = "Method.nav.car.cluster";
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_METHOD_CURRENT = "Method.current";
/*-------------------------------------------------------------------------*/
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SuperPixel_Number		= "SuperPixel.Number";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SuperPixel_Compactness = "SuperPixel.Compactness";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SuperPixel_Weight_XY = "SuperPixel.Weight.XY";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_SVG_ApparentHorizon_VanishingPoint = "SVG.ApparentHorizon.VanishingPoint";
/*-------------------------------------------------------------------------*/
const QString  SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_L_THRESHOLD =		"Cluster.LThetaM.L.Threshold";
const QString  SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_M_THRESHOLD =		"Cluster.LThetaM.M.Threshold";
const QString  SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_Theta_THRESHOLD =	"Cluster.LThetaM.Theta.Threshold";
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
		NODE_CFG_SuperPixel_Weight_XY,
		QString::number(1.9F));

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

#if 1

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_L_THRESHOLD,
		QString::number(0.031F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_M_THRESHOLD,
		QString::number(0.02F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_Theta_THRESHOLD,
		QString::number(0.015F));

#endif // 1



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
float SGV_CFG_ARITHMETIC::getSuperPixel_Weight_XY()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_SuperPixel_Weight_XY);
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
float		SGV_CFG_ARITHMETIC::GetCluster_LThetaM_L_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_L_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float		SGV_CFG_ARITHMETIC::GetCluster_LThetaM_M_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_M_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float		SGV_CFG_ARITHMETIC::GetCluster_LThetaM_Theta_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_Theta_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/