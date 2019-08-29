#pragma once
/*-------------------------------------*/
#include "cpp_basic.h"
/*-------------------------------------*/
#include <MY_SDK_LIB/TimeMeasure.hpp>
/*-------------------------------------*/
#include "gSLICr_Lib/gSLICr.h"
/*-------------------------------------*/
/**
*
*
*/
/*-------------------------------------*/
class MemcpyCv_gSLICr 
{
public:
	MemcpyCv_gSLICr(void);
	~MemcpyCv_gSLICr(void);
public:
	static void load_4Image_to_MatBGR_BGR(const gSLICr::UChar4Image * inimg, cv::Mat & outimg);
	static void load_4Image_to_MatBGRA_BGRA(const gSLICr::UChar4Image * inimg, cv::Mat & outimg);
	static void load_MatBGRA_to_4image_BGR(const cv::Mat & inimg, gSLICr::UChar4Image * outimg);
	static void load_IplimageBGRA_to_4image_BGR(const IplImage* _inimg, gSLICr::UChar4Image * _outimg);
	static void load_Iplimage4u_to_4image_4u(const IplImage* _inimg, gSLICr::UChar4Image * _outimg);
	static void load_4Image_to_MatBGRA_4u(const gSLICr::UChar4Image * inimg, cv::Mat & outimg);
	static void load_4Image_to_MatBGRA_4u(const gSLICr::IntImage * _inimg, cv::Mat & _outimg);
public:

};

