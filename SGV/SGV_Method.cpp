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
#include "gSLICr_Lib/engines/gSLICr_core_engine_cluster.h"
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
	
	my_settings.spixel_size = 16;
	
	my_settings.no_iters = 5;
	my_settings.color_space = gSLICr::CIELAB; // gSLICr::CIELAB for Lab, or gSLICr::RGB for RGB
	my_settings.seg_method = gSLICr::GIVEN_NUM; // or gSLICr::GIVEN_NUM for given number
	my_settings.do_enforce_connectivity = true; // whether or not run the enforce connectivity step
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::initSetting_no(
	gSLICr::objects::settings& my_settings,
	const int _N,
	const float _Weight_XY)
{
	my_settings.no_segs = (2 * _N + 1)*(2 * _N + 1);
	my_settings.coh_weight = _Weight_XY;
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
void SGV_Method::SVG_NAVIGATION_CAR_CLUSTER(
	const std::string _file_full_name,
	const IplImage* _img,
	const std::string _saveLocation,
	const int _K,
	const float _HL_VP)
{

	SGV_CFG_ARITHMETIC cfg_arithmetic;
	SGV_CFG_DBG cfg_dbg;

	cfg_arithmetic.InitLoad();
	cfg_dbg.InitLoad();

	const float L_th = cfg_arithmetic.GetCluster_LThetaM_L_THRESHOLD();
	const float M_th = cfg_arithmetic.GetCluster_LThetaM_M_THRESHOLD();
	const float Theta_th = cfg_arithmetic.GetCluster_LThetaM_Theta_THRESHOLD();

	const float weight_xy=cfg_arithmetic.getSuperPixel_Weight_XY();

	const std::string file_name_t=Base::file_name_without_ext(_file_full_name);


	TimeMeasure tm("##################### NAVIGATION CAR CLUSTER #####################");
	{

		gSLICr::objects::settings my_settings;
		
		initSetting(my_settings);
		initSetting_no(my_settings, _K,weight_xy);
		initSetting(my_settings, _img);

		gSLICr::engines::core_engine_cluster* gSLICr_engine = new gSLICr::engines::core_engine_cluster(my_settings);
		
		const gSLICr::engines::seg_engine_GPU_cluster* gSLICr_seg_engine = gSLICr_engine->GetSegEngineGPUCluster();
		
		((gSLICr::engines::seg_engine_GPU_cluster* )gSLICr_seg_engine)->SetClusterLThetaM_Threshold(L_th,M_th,Theta_th);

		const int SpixelDim = gSLICr_seg_engine->SpixelNum();

		gSLICr::UChar4Image* in_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
		gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);

		cv::Size img_size_cv(my_settings.img_size.x, my_settings.img_size.y);
		cv::Size cluster_map_size_cv(SpixelDim, 1);
		cv::Size adjacency_size_cv(SpixelDim, SpixelDim);
		

		cv::Mat boundry_draw_frame(img_size_cv, CV_8UC4);
		cv::Mat boundry_cluster_draw_frame(img_size_cv, CV_8UC4);
		cv::Mat cluster_map_frame(cluster_map_size_cv, CV_32SC1);
		cv::Mat idx_frame(img_size_cv, CV_32SC1);
		cv::Mat idx_cluster_frame(img_size_cv, CV_32SC1);
		cv::Mat adjacency_frame(adjacency_size_cv, CV_32SC1);
		cv::Mat similar_frame(adjacency_size_cv, CV_32FC1);
		
		std::vector<gSLICr::objects::spixel_info> spixel_info_t;

		int key; int save_count = 0;
		int do_count = 0;
		while (do_count++<10)
		{

			{
				TimeMeasure tm("cpy.superpixel.cpy");
				TimeMeasure::Config(0, 0);

				MemcpyCv_gSLICr::load_Iplimage4u_to_4image_4u(_img, in_img);

				gSLICr_engine->Process_Frame(in_img);
				gSLICr_engine->Draw_Segmentation_Result(out_img);

				gSLICr_engine->Perform_Cluster();
				gSLICr_engine->MEM_GPU_to_CPU();				
				gSLICr_engine->Perform_Cluster_CPU();

				/*-------------------------------------------------------------------------*/
				const gSLICr::IntImage * idx_img = gSLICr_engine->Get_Seg_Res();
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(idx_img, idx_frame);
				cfg_dbg.SaveImage(idx_frame,
					file_name_t,
					"idx.frame");
				/*-------------------------------------------------------------------------*/
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(out_img, boundry_draw_frame);
				cfg_dbg.SaveImage(boundry_draw_frame,
					file_name_t,
					"boundry.draw.frame");
				/*-------------------------------------------------------------------------*/
				gSLICr_engine->MEM_GPU_to_CPU_Spixel_Map();
				const std::vector<gSLICr::objects::spixel_info> spixel_info_center_t= gSLICr_engine->Get_Spixel_Map_Vector();
				cfg_dbg.SaveImage_Width_Idx(boundry_draw_frame, file_name_t, "txt.idx.frame", spixel_info_center_t);
				/*-------------------------------------------------------------------------*/
				const gSLICr::IntImage * adj_img = gSLICr_engine->Get_Adjacency();
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(adj_img, adjacency_frame);
				cfg_dbg.SaveImage(adjacency_frame,
					file_name_t,
					"adjacency.frame");
				/*-------------------------------------------------------------------------*/
				const gSLICr::IntImage * seg_cluster = gSLICr_engine->Get_Cluster_Idx_Seg();
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(seg_cluster, idx_cluster_frame);
				cfg_dbg.SaveImage(idx_cluster_frame,
					file_name_t,
					"idx.cluster.frame");
				/*-------------------------------------------------------------------------*/
				const gSLICr::FloatImage *similar_img = gSLICr_engine->Get_Similar();
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(similar_img, similar_frame);
				cfg_dbg.SaveImage(similar_frame,
					file_name_t,
					"similar.frame");
				/*-------------------------------------------------------------------------*/
				gSLICr_engine->MEM_CPU_to_GPU_Cluster_Idx();
				gSLICr_engine->MEM_GPU_to_CPU_Spixel_Map_Cvt();
				/*-------------------------------------------------------------------------*/
				spixel_info_t =gSLICr_engine->Get_Spixel_Map_Cvt_Vector();
				cfg_dbg.Save_Spixel_Map_Cvt_Vector(spixel_info_t,"Save_Spixel_Map_Cvt_Vector.txt");
				/*-------------------------------------------------------------------------*/
				gSLICr_engine->Draw_Segmentation_Cluster_Result(out_img);
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(out_img, boundry_cluster_draw_frame);
				cfg_dbg.SaveImage(boundry_cluster_draw_frame,
					file_name_t,
					"boundry.cluster.frame");
				/*-------------------------------------------------------------------------*/
				ImgProcCluster::GetClusterRelation(similar_frame);

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
		
		

	}
	else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR) == 0) {

		SVG_NAVIGATION_CAR(_img,
			saveLocation,
			K,
			M,
			AH_VP);

	}else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR_CLUSTER) == 0) {

		SVG_NAVIGATION_CAR_CLUSTER(
			_f,
			_img,
			saveLocation,
			K,
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