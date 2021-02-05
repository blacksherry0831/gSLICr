#pragma once
/*----------------------------------------------------------------*/
#include "mw_cfg.hpp"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
class MW_CFG_KV:public   MW_CFG
{
public:
	MW_CFG_KV(void);
	~MW_CFG_KV(void);
public:
	virtual void CreateChildCfgNode(
		QSharedPointer<QDomDocument> _Xml,
		QDomElement& _parent);
private:
	static const QString   NODE_CFG_FRONT_CAM_DST_2_BOARD;
	static const QString   NODE_CFG_FRONT_CAM_SZ_W_BOARD;
	static const QString   NODE_CFG_FRONT_CAM_SZ_H_BOARD;
	static const QString   NODE_CFG_FRONT_CAM_SZ_CELL_BOARD;
	static const QString   NODE_CFG_FRONT_CAM_SZ_MAP;
	static const QString   NODE_CFG_FRONT_CAM_Affine_X_POINTS;
	static const QString   NODE_CFG_FRONT_CAM_Affine_Y_POINTS;
public:
	float				getFrontCamDst2Board();
	int					getFrontCamBoardW();
	int					getFrontCamBoardH();
	float				getFrontCamSzBoardCell();
	int					getFrontCamSzMap();
	std::vector<float>	getFrontCamAffineX();
	std::vector<float>	getFrontCamAffineY();

	std::vector<QString>	getFrontCamAffineX_QStr();
	std::vector<QString>	getFrontCamAffineY_QStr();


};

