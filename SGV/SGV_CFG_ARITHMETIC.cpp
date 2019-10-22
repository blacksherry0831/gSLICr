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
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_Fuzzy_Method="Fuzzy.Method";
/*-------------------------------------------------------------------------*/
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_L_COLOR_THRESHOLD =		"Cluster.LThetaM.L.Color.Threshold";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_M_COLOR_THRESHOLD =		"Cluster.LThetaM.M.Color.Threshold";
const QString	SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_Theta_COLOR_THRESHOLD =	"Cluster.LThetaM.Theta.Color.Threshold";
/*-------------------------------------------------------------------------*/
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_L_GRAY_THRESHOLD		= "Cluster.LThetaM.L.Gray.Threshold";
const QString   SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_M_GRAY_THRESHOLD		= "Cluster.LThetaM.M.Gray.Threshold";
const QString	SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_Theta_GRAY_THRESHOLD	= "Cluster.LThetaM.Theta.Gray.Threshold";
/*-------------------------------------------------------------------------*/
const QString	SGV_CFG_ARITHMETIC::NODE_CFG_Cluster_LThetaM_Gray_Color_THRESHOLD =	"Cluster.LThetaM.M.Gray.Color.Threshold";
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
		QString::number(27));

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
	createElement_txt_append(_Xml,
		_parent,
		NODE_CFG_Fuzzy_Method,
		"svg");


	this->CreateElement_Threshold(
		_Xml,
		_parent);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_ARITHMETIC::CreateElement_Threshold(
	QSharedPointer<QDomDocument> _Xml,
	QDomElement& _parent)
{
	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_L_COLOR_THRESHOLD,
		QString::number(6.25F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_M_COLOR_THRESHOLD,
		QString::number(11.315F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_Theta_COLOR_THRESHOLD,
		QString::number(8.0F));



	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_L_GRAY_THRESHOLD,
		QString::number(3.0F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_M_GRAY_THRESHOLD,
		QString::number(0.0F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_Theta_GRAY_THRESHOLD,
		QString::number(4.0F));
	

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_Cluster_LThetaM_Gray_Color_THRESHOLD,
		QString::number(2.0F));



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
QString SGV_CFG_ARITHMETIC::getFuzzyMethod()
{
	return getStringFromDomDoc_Pro(NODE_CFG_Fuzzy_Method);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float		SGV_CFG_ARITHMETIC::GetCluster_LThetaM_L_COLOR_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_L_COLOR_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float		SGV_CFG_ARITHMETIC::GetCluster_LThetaM_M_COLOR_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_M_COLOR_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float		SGV_CFG_ARITHMETIC::GetCluster_LThetaM_Theta_COLOR_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_Theta_COLOR_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float SGV_CFG_ARITHMETIC::GetCluster_LThetaM_L_GRAY_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_L_GRAY_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float SGV_CFG_ARITHMETIC::GetCluster_LThetaM_M_GRAY_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_M_GRAY_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float SGV_CFG_ARITHMETIC::GetCluster_LThetaM_Theta_GRAY_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_Theta_GRAY_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float SGV_CFG_ARITHMETIC::GetCluster_LThetaM_Gray_Color_THRESHOLD()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_Cluster_LThetaM_Gray_Color_THRESHOLD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/