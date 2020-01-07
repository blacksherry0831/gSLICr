#pragma once
/*----------------------------------------------------------------*/
#include "SGV_CFG.h"
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class SGV_CFG_ARITHMETIC : public SGV_CFG
{
public:
	SGV_CFG_ARITHMETIC(void);
	~SGV_CFG_ARITHMETIC(void);
public:
	virtual void CreateChildCfgNode(
		QSharedPointer<QDomDocument> _Xml,
		QDomElement& _parent);

	void CreateElement_Threshold(
		QSharedPointer<QDomDocument> _Xml,
		QDomElement& _parent);
public:
	static const QString  NODE_METHOD_OUT_DOOR_HUMAN;
	static const QString  NODE_METHOD_OUT_DOOR_400_IMAGE_STABLE;

	static const QString  NODE_METHOD_LAB_SVG;
	static const QString  NODE_METHOD_NAV_CAR;
	static const QString  NODE_METHOD_NAV_CAR_CLUSTER;
	static const QString  NODE_METHOD_NAV_CAR_CLUSTER_FAST;
	static const QString  NODE_METHOD_CURRENT;
public:
	static const QString  NODE_CFG_SuperPixel_Number;
	static const QString  NODE_CFG_SuperPixel_Compactness;
	static const QString  NODE_CFG_SuperPixel_Weight_XY;
	static const QString  NODE_CFG_SVG_ApparentHorizon_VanishingPoint;
public:
	static const QString  NODE_CFG_Fuzzy_Method;
public:
	static const QString  NODE_CFG_Cluster_LThetaM_L_COLOR_THRESHOLD;
	static const QString  NODE_CFG_Cluster_LThetaM_M_COLOR_THRESHOLD;
	static const QString  NODE_CFG_Cluster_LThetaM_Theta_COLOR_THRESHOLD;

	static const QString  NODE_CFG_Cluster_LThetaM_L_GRAY_THRESHOLD;
	static const QString  NODE_CFG_Cluster_LThetaM_M_GRAY_THRESHOLD;
	static const QString  NODE_CFG_Cluster_LThetaM_Theta_GRAY_THRESHOLD;

	static const QString  NODE_CFG_Cluster_LThetaM_Gray_Color_THRESHOLD;
public:
	QString getMethod_Current();
	int		getMethod_LAB_SVG();
	int		getMethod_NAV_CAR();
public:
	float		GetCluster_LThetaM_L_COLOR_THRESHOLD();
	float		GetCluster_LThetaM_M_COLOR_THRESHOLD();
	float		GetCluster_LThetaM_Theta_COLOR_THRESHOLD();

	float		GetCluster_LThetaM_L_GRAY_THRESHOLD();
	float		GetCluster_LThetaM_M_GRAY_THRESHOLD();
	float		GetCluster_LThetaM_Theta_GRAY_THRESHOLD();

	float		GetCluster_LThetaM_Gray_Color_THRESHOLD();
public:
	int		getSuperPixel_Number();
	int		getSuperPixel_Compactness();
	float   getSuperPixel_Weight_XY();
public:
	float	getSVG_G_ApparentHorizon_VanishingPoint();
public:
	QString getFuzzyMethod();
};

