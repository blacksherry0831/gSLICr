#pragma once
/*----------------------------------------------------------------*/
#include "SGV_CFG.h"
/*----------------------------------------------------------------*/
#include "gSLICr_Lib/engines/gSLICr_seg_engine_GPU.h"
/*----------------------------------------------------------------*/
#include "MemcpyCv_gSLICr/MemcpyCv_gSLICr.hpp"
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
	static const QString  NODE_CFG_SOURCE_PATH;
public:
	int getImgSave();
	int getDebugSave();
	QString getOutputPath();
	QString getSourcePath();
public:
	void SaveImage(
		const cv::Mat _m,
		const std::string _file_name,
		const std::string _suffix);

	void SaveImage_Width_Idx(
		const gSLICr::IntImage*	_idx_img,
		const std::string		_file_name,
		const std::string		_suffix,
		std::vector<gSLICr::objects::spixel_info> _spixels,
		const float _M_Gray_Color_th);

	void SaveImage_Width_Idx(
		cv::Mat _m,
		const std::string		_file_name,
		const std::string		_suffix,
		std::vector<gSLICr::objects::spixel_info> _spixels,
		const float _M_Gray_Color_th);

	const void Save_Spixel_Map_Cvt_Vector(
		std::vector<gSLICr::objects::spixel_info> spixel_list_t,
		std::string _file_name);

	const void SGV_CFG_DBG::Save_Spixel_Map_And_Cvt_Vector(
		const ORUtils::Vector2<int>						 _Spixel_Map_noDims_t,
		const std::vector<gSLICr::objects::spixel_info>  _spixel_list_cvt_t,
		const std::vector<gSLICr::objects::spixel_info>  _spixel_list_org_t,
		const std::string _file_name,
		const std::string _suffix);

public:

};

