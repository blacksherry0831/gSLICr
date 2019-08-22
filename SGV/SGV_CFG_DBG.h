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
class SGV_CFG_DBG : public SGV_CFG
{
public:
	SGV_CFG_DBG(void);
	~SGV_CFG_DBG(void);
public:
	
	virtual void CreateChildCfgNode(
		QSharedPointer<QDomDocument> _Xml,
		QDomElement& _parent);

public:
	static const QString  NODE_CFG_SAVE_IMG;
	static const QString  NODE_CFG_SAVE_DBG;
	static const QString  NODE_CFG_OUTPUT_PATH;

	int getImgSave();
	int getDebugSave();
	QString getOutputPath();

};

