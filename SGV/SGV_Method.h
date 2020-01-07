#pragma once
/*----------------------------------------------------------------*/
#include <cpp_stl.h>
#include <cpp_def.h>
#include <cpp_def_debug.h>
/*----------------------------------------------------------------*/
#include <opencv_basic.h>
/*----------------------------------------------------------------*/
#include <QDir>
/*----------------------------------------------------------------*/
#include <MY_SDK_LIB/TimeMeasure.hpp>
#include <MY_SDK_LIB/ImgProcCluster.hpp>
/*----------------------------------------------------------------*/
#include "gSLICr_Lib/gSLICr.h"
/*----------------------------------------------------------------*/
#include <SGV/SGV_GLOBAL.h>
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class SGV_Method
{
public:
	SGV_Method(void);
	~SGV_Method(void);
private:
	static int G_DEBUG;
	static int G_SAVE;
public:

static void initGlobalCfg();

static void initSetting(gSLICr::objects::settings& my_settings);

static void initSetting_no(
	gSLICr::objects::settings & my_settings, 
	const int _N,
	const float _Weight_XY= 0.6F);

static void initSetting(
	gSLICr::objects::settings& my_settings,
	const IplImage* _img);

static	void SVG_NAVIGATION_CAR(						
						IplImage* _img,
						std::string _saveLocation,
						const int _K = 1089,
						const float _M = 10,
						const float _HL_VP = 0.5);

static void SVG_NAVIGATION_CAR_CLUSTER(
						const std::string _file_full_name,
						const IplImage * _img,
						const std::string _saveLocation,
						const int _K,
						const float _HL_VP);

static void SVG_NAVIGATION_CAR_CLUSTER_FAST(
						const std::string _file_full_name,
						const IplImage * _img,
						const std::string _saveLocation);

static void SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(
	const IplImage * _img,
	cv::Mat& _svg_idx_frame);

public:
static	void METHOD_PATH_CFG();
static	void METHOD_PATH(const std::string _path);
static	void METHOD_FILE(const std::string _f);
static	void METHOD_MEM(const std::string _f,IplImage* _img);

};

