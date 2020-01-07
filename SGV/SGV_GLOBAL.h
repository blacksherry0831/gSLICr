#pragma once
/*----------------------------------------------------------------*/
#include "SGV_CFG.h"
/*----------------------------------------------------------------*/
#include "gSLICr_Lib/engines/gSLICr_core_engine_cluster.h"
/*----------------------------------------------------------------*/
#include <SGV/SGV_CFG_DBG.h>
#include <SGV/SGV_CFG_ARITHMETIC.h>
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class SGV_GLOBAL
{
public:
	SGV_GLOBAL(void);
	~SGV_GLOBAL(void);
private:
	static gSLICr::objects::settings m_settings;
	static std::shared_ptr<gSLICr::engines::core_engine_cluster>	m_gSLICr_engine;
public:
	static  std::string FUZZY_METHOD_SVG;
	static float AH_VP;
	static float M_GRAY_COLOR_TH;
public:
	static void InitCoreEngineCluster(const int _w, const int _h);
	static std::shared_ptr<gSLICr::engines::core_engine_cluster>	GetCoreEngineCluster();
private:
	static void initSetting();
	static void initSetting_no(const int _N, const float _Weight_XY);
private:
	static int IsInit(const int _w, const int _h);
	static void initSetting_wh(const int _w, const int _h);
	
};

