#include "SGV_Method.h"
/*-------------------------------------------------------------------------*/
#include <SGV/SGV_Method.h>
#include <SGV/SGV_CFG_DBG.h>
#include <SGV/SGV_CFG_ARITHMETIC.h>
/*-------------------------------------------------------------------------*/
#include <SGVBaseCode/ImageDataBasic.h>
#include <SGVBaseCode/ImageSaveProc.h>
/*-------------------------------------------------------------------------*/
#include "MemcpyCv_gSLICr/MemcpyCv_gSLICr.hpp"
/*-------------------------------------------------------------------------*/
int SGV_Method::G_DEBUG = FALSE;
/*----------------------------------------------------------------*/
int SGV_Method::G_SAVE = FALSE;
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_Method::SGV_Method(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_Method::~SGV_Method(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::initGlobalCfg()
{
	SGV_CFG_DBG cfg_dbg;

	cfg_dbg.InitLoad();

	G_DEBUG = cfg_dbg.getDebugSave();
	G_SAVE = cfg_dbg.getImgSave();
		
	TimeMeasure::Config(G_DEBUG, G_SAVE);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::initSetting(gSLICr::objects::settings& my_settings)
{
	const int N = 16;
	my_settings.no_segs = (2 * N + 1)*(2 * N + 1);
	my_settings.spixel_size = 16;
	my_settings.coh_weight = 0.6f;
	my_settings.no_iters = 5;
	my_settings.color_space = gSLICr::XYZ; // gSLICr::CIELAB for Lab, or gSLICr::RGB for RGB
	my_settings.seg_method = gSLICr::GIVEN_NUM; // or gSLICr::GIVEN_NUM for given number
	my_settings.do_enforce_connectivity = true; // whether or not run the enforce connectivity step
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::initSetting(
	gSLICr::objects::settings& my_settings,
	const IplImage* _img)
{
	my_settings.img_size.x = _img->width;
	my_settings.img_size.y = _img->height;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::SVG_NAVIGATION_CAR(								
									IplImage* _img,
									std::string _saveLocation,
									const int _K,
									const float _M,
									const float _HL_VP)
{

	TimeMeasure tm("##################### NAVIGATION CAR #####################");
	{
		
		gSLICr::objects::settings my_settings;
		initSetting(my_settings);
		initSetting(my_settings, _img);
		
		gSLICr::engines::core_engine* gSLICr_engine = new gSLICr::engines::core_engine(my_settings);
		gSLICr::UChar4Image* in_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
		gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
		
		cv::Size s(my_settings.img_size.x, my_settings.img_size.y);
		cv::Mat boundry_draw_frame; 
				boundry_draw_frame.create(s, CV_8UC4);

		cv::Mat idx_frame;
				idx_frame.create(s, CV_32SC1);

		int key; int save_count = 0;
		int do_count=0;
		while (do_count++<10)
		{
									
			{
					TimeMeasure tm("cpy.superpixel.cpy");
					TimeMeasure::Config(0, 0);
					
							MemcpyCv_gSLICr::load_Iplimage4u_to_4image_4u(_img, in_img);

										gSLICr_engine->Process_Frame(in_img);
										gSLICr_engine->Draw_Segmentation_Result(out_img);
										const gSLICr::IntImage * idx_img=gSLICr_engine->Get_Seg_Res();

							MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(idx_img,idx_frame);
							MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(out_img, boundry_draw_frame);

					TimeMeasure::Config(1, 1);
			}
				
			imshow("segmentation", boundry_draw_frame);

			 key = cv::waitKey(1);
			if (key == 27) break;
			else if (key == 's')
			{
				printf("\nsaved segmentation %04i\n", save_count);
				save_count++;
			}
		}

	}

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::METHOD_FILE(const std::string _f)
{
	ImageDataBasic imgorg(_f,"");
	METHOD_MEM(_f,imgorg.GetIplImagePtr());
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::METHOD_MEM(const std::string _f,IplImage* _img)
{
	initGlobalCfg();

	SGV_CFG_DBG cfg_dbg;
	SGV_CFG_ARITHMETIC cfg_arithmetic;

	cfg_dbg.InitLoad();
	cfg_arithmetic.InitLoad();

	const std::string saveLocation = cfg_dbg.getOutputPath().toStdString();
	const QString   method_t= cfg_arithmetic.getMethod_Current();

	const float K = cfg_arithmetic.getSuperPixel_Number();
	const float M = cfg_arithmetic.getSuperPixel_Compactness();
	const float AH_VP = cfg_arithmetic.getSVG_G_ApparentHorizon_VanishingPoint();

	if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_LAB_SVG)==0){
		
		

	}else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR)==0){
						
		SVG_NAVIGATION_CAR(_img,
			saveLocation,
			K,
			M,
			AH_VP);

	}else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_OUT_DOOR_400_IMAGE_STABLE)==0){
		
		

	}else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_OUT_DOOR_HUMAN)==0){
		
		

	}else{
		Q_ASSERT(0);
	}
	

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/