#include "SGV_GLOBAL.h"
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
gSLICr::objects::settings SGV_GLOBAL::m_settings = {0};
std::shared_ptr<gSLICr::engines::core_engine_cluster>	SGV_GLOBAL::m_gSLICr_engine;
std::string SGV_GLOBAL::FUZZY_METHOD_SVG="svg";
float SGV_GLOBAL::AH_VP=0.5;
float SGV_GLOBAL::M_GRAY_COLOR_TH=0;
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_GLOBAL::SGV_GLOBAL(void)
{
	m_settings.img_size.height = 0;
	m_settings.img_size.width = 0;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_GLOBAL::~SGV_GLOBAL(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
std::shared_ptr<gSLICr::engines::core_engine_cluster>	
SGV_GLOBAL::GetCoreEngineCluster()
{
	assert(m_gSLICr_engine != nullptr);
	return m_gSLICr_engine;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_GLOBAL::InitCoreEngineCluster(const int _w, const int _h)
{

	if (0==IsInit(_w, _h)) {
							
							initSetting_wh(_w,_h);
	
							SGV_CFG_DBG cfg_dbg;
							SGV_CFG_ARITHMETIC cfg_arithmetic;

							cfg_dbg.InitLoad();
							cfg_arithmetic.InitLoad();

							const std::string saveLocation = cfg_dbg.getOutputPath().toStdString();
							const QString   method_t = cfg_arithmetic.getMethod_Current();

							const float K = cfg_arithmetic.getSuperPixel_Number();
							const float M = cfg_arithmetic.getSuperPixel_Compactness();

							AH_VP = cfg_arithmetic.getSVG_G_ApparentHorizon_VanishingPoint();

							const float L_Color_th = cfg_arithmetic.GetCluster_LThetaM_L_COLOR_THRESHOLD();
							const float M_Color_th = cfg_arithmetic.GetCluster_LThetaM_M_COLOR_THRESHOLD();
							const float Theta_Color_th = cfg_arithmetic.GetCluster_LThetaM_Theta_COLOR_THRESHOLD();

							const float L_Gray_th = cfg_arithmetic.GetCluster_LThetaM_L_GRAY_THRESHOLD();
							const float M_Gray_th = cfg_arithmetic.GetCluster_LThetaM_M_GRAY_THRESHOLD();
							const float Theta_Gray_th = cfg_arithmetic.GetCluster_LThetaM_Theta_GRAY_THRESHOLD();

							M_GRAY_COLOR_TH = cfg_arithmetic.GetCluster_LThetaM_Gray_Color_THRESHOLD();

							const float weight_xy = cfg_arithmetic.getSuperPixel_Weight_XY();


							FUZZY_METHOD_SVG = cfg_arithmetic.getFuzzyMethod().toStdString();

							initSetting();
							initSetting_no(K, weight_xy);


							m_gSLICr_engine = std::shared_ptr<gSLICr::engines::core_engine_cluster>(new gSLICr::engines::core_engine_cluster(m_settings));

							const gSLICr::engines::seg_engine_GPU_cluster* gSLICr_seg_engine = m_gSLICr_engine->GetSegEngineGPUCluster();

							((gSLICr::engines::seg_engine_GPU_cluster*)gSLICr_seg_engine)->SetClusterLThetaM_Threshold(
								L_Color_th,
								M_Color_th,
								Theta_Color_th,
								L_Gray_th,
								M_Gray_th,
								Theta_Gray_th,
								M_GRAY_COLOR_TH);
	
	}
	
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/

void SGV_GLOBAL::initSetting_no(
	const int _N,
	const float _Weight_XY)
{
	m_settings.no_segs = (2 * _N + 1)*(2 * _N + 1);
	m_settings.coh_weight = _Weight_XY;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_GLOBAL::IsInit(const int _w, const int _h)
{
	if ((m_settings.img_size.height == _h) &&
		(m_settings.img_size.width == _w))
	{
		return 1;
	}
	return 0;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_GLOBAL::initSetting_wh(const int _w, const int _h)
{
	m_settings.img_size.height = _h;
	m_settings.img_size.width  = _w;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void  SGV_GLOBAL::initSetting()
{
	m_settings.spixel_size = 16;
	m_settings.no_iters = 5;
	m_settings.color_space = gSLICr::CIELAB; // gSLICr::CIELAB for Lab, or gSLICr::RGB for RGB
	m_settings.seg_method = gSLICr::GIVEN_NUM; // or gSLICr::GIVEN_NUM for given number
	m_settings.do_enforce_connectivity = true; // whether or not run the enforce connectivity step
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
