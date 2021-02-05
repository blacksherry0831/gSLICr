#include "mw_cfg_kv.hpp"
/*-------------------------------------------------------------------------*/
/**
*front
*/
/*-------------------------------------------------------------------------*/
const QString   MW_CFG_KV::NODE_CFG_FRONT_CAM_DST_2_BOARD		= "cam.front.dst.cam2board";
const QString   MW_CFG_KV::NODE_CFG_FRONT_CAM_SZ_W_BOARD		= "cam.front.sz.w.board";
const QString	MW_CFG_KV::NODE_CFG_FRONT_CAM_SZ_H_BOARD		= "cam.front.sz.h.board";
/*-------------------------------------------------------------------------*/
const QString   MW_CFG_KV::NODE_CFG_FRONT_CAM_SZ_CELL_BOARD		= "cam.front.sz.cell.board";
const QString   MW_CFG_KV::NODE_CFG_FRONT_CAM_SZ_MAP			= "cam.front.sz.map";
const QString   MW_CFG_KV::NODE_CFG_FRONT_CAM_Affine_X_POINTS	= "cam.front.Aff.X.points";
const QString   MW_CFG_KV::NODE_CFG_FRONT_CAM_Affine_Y_POINTS	= "cam.front.Aff.Y.points";
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
MW_CFG_KV::MW_CFG_KV(void)
{
	FILE_XML_CFG = "cfg.mainwindow.xml";
	DATA_CFG_PROPERTY = "mainwindow.nav.autolabor.cfg";
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
MW_CFG_KV::~MW_CFG_KV(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MW_CFG_KV::CreateChildCfgNode(
	QSharedPointer<QDomDocument> _Xml,
	QDomElement& _parent)
{
	createElement_txt_append(_Xml, _parent, NODE_CFG_PROPERTY, DATA_CFG_PROPERTY);

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_FRONT_CAM_DST_2_BOARD,
		QString::number(1.0F));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_FRONT_CAM_SZ_W_BOARD,
		QString::number(11));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_FRONT_CAM_SZ_H_BOARD,
		QString::number(8));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_FRONT_CAM_SZ_CELL_BOARD,
		QString::number(0.03F));

	createElement_txt_append(
		_Xml,
		_parent,
		MW_CFG_KV::NODE_CFG_FRONT_CAM_SZ_MAP,
		QString::number(7));

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_FRONT_CAM_Affine_X_POINTS,
		"933,1148,890,1198");

	createElement_txt_append(
		_Xml,
		_parent,
		NODE_CFG_FRONT_CAM_Affine_Y_POINTS,
		"836,830,964,956");

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float MW_CFG_KV::getFrontCamDst2Board()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_FRONT_CAM_DST_2_BOARD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int MW_CFG_KV::getFrontCamBoardW()
{
	return getIntFromDomDoc_Pro(NODE_CFG_FRONT_CAM_SZ_W_BOARD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int MW_CFG_KV::getFrontCamBoardH()
{
	return getIntFromDomDoc_Pro(NODE_CFG_FRONT_CAM_SZ_H_BOARD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
float MW_CFG_KV::getFrontCamSzBoardCell()
{
	return getFloatFromDomDoc_Pro(NODE_CFG_FRONT_CAM_SZ_CELL_BOARD);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int MW_CFG_KV::getFrontCamSzMap()
{
	return getIntFromDomDoc_Pro(NODE_CFG_FRONT_CAM_SZ_MAP);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<float> MW_CFG_KV::getFrontCamAffineX()
{
	return getVectorFromDomDoc_Pro(NODE_CFG_FRONT_CAM_Affine_X_POINTS);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<float> MW_CFG_KV::getFrontCamAffineY()
{
	return getVectorFromDomDoc_Pro(NODE_CFG_FRONT_CAM_Affine_Y_POINTS);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<QString> MW_CFG_KV::getFrontCamAffineX_QStr()
{
	return getVectorQStrFromDomDoc_Pro(NODE_CFG_FRONT_CAM_Affine_X_POINTS);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::vector<QString> MW_CFG_KV::getFrontCamAffineY_QStr()
{
	return getVectorQStrFromDomDoc_Pro(NODE_CFG_FRONT_CAM_Affine_Y_POINTS);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/