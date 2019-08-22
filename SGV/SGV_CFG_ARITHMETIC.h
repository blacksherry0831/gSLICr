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
public:
	static const QString  NODE_METHOD_OUT_DOOR_HUMAN;
	static const QString  NODE_METHOD_OUT_DOOR_400_IMAGE_STABLE;

	static const QString  NODE_METHOD_LAB_SVG;
	static const QString  NODE_METHOD_NAV_CAR;
	static const QString  NODE_METHOD_CURRENT;
public:
	static const QString  NODE_CFG_SuperPixel_Number;
	static const QString  NODE_CFG_SuperPixel_Compactness;
	static const QString  NODE_CFG_SVG_ApparentHorizon_VanishingPoint;
public:
	QString getMethod_Current();
	int		getMethod_LAB_SVG();
	int		getMethod_NAV_CAR();
public:
	int		getSuperPixel_Number();
	int		getSuperPixel_Compactness();
public:
	float	getSVG_G_ApparentHorizon_VanishingPoint();
public:
	
};

