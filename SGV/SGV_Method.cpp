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
#include "Fuzzy/FuzzyMethod.h"
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
	TimeMeasure::Config(1, 1);
	TimeMeasure tm("##################### NAVIGATION CAR #####################");
	{
		
		const int WIDTH = _img->width;
		const int HEIGHT = _img->height;
		gSLICr::Vector2i img_size(WIDTH, HEIGHT);
		SGV_GLOBAL::InitCoreEngineCluster(WIDTH, HEIGHT);
		
		std::shared_ptr<gSLICr::engines::core_engine_cluster> gSLICr_engine = SGV_GLOBAL::GetCoreEngineCluster();
		gSLICr::UChar4Image* in_img = new gSLICr::UChar4Image(img_size, true, true);
		gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(img_size, true, true);
		
		cv::Size s(img_size.x, img_size.y);
		cv::Mat boundry_draw_frame; 
				boundry_draw_frame.create(s, CV_8UC4);

		cv::Mat idx_frame;
				idx_frame.create(s, CV_32SC1);

		int save_count = 0;
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
		
#if _DEBUG && 0
			imshow("segmentation", boundry_draw_frame);

			const int key = cv::waitKey(1);
			if (key == 27) break;
			else if (key == 's')
			{
				printf("\nsaved segmentation %04i\n", save_count);
				save_count++;
			}
#endif // _DEBUG


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
	
	SGV_CFG_DBG cfg_dbg;	
	cfg_dbg.InitLoad();

	const std::string file_name_t=Base::file_name_without_ext(_file_full_name);
	
	TimeMeasure::Config(1, 1);
	TimeMeasure tm("##################### NAVIGATION CAR CLUSTER #####################");
	{
		const int WIDTH = _img->width;
		const int HEIGHT = _img->height;
		
		gSLICr::Vector2i img_size(WIDTH,HEIGHT);
		cv::Size img_size_cv(WIDTH, HEIGHT);
		
		SGV_GLOBAL::InitCoreEngineCluster(WIDTH, HEIGHT);
		/*-------------------------------------------------------------------------*/
		std::shared_ptr<gSLICr::engines::core_engine_cluster>  gSLICr_engine = SGV_GLOBAL::GetCoreEngineCluster();
		
		const int	SpixelDim = gSLICr_engine->SpixelNum();
				
		std::shared_ptr<gSLICr::UChar4Image>  in_img(new gSLICr::UChar4Image(img_size, true, true));
		std::shared_ptr<gSLICr::UChar4Image>  out_img(new gSLICr::UChar4Image(img_size, true, true));

		cv::Size cluster_map_size_cv(SpixelDim, 1);
		cv::Size adjacency_size_cv(SpixelDim, SpixelDim);
		
		cv::Mat boundry_draw_frame(img_size_cv, CV_8UC4);
		cv::Mat boundry_cluster_draw_frame(img_size_cv, CV_8UC4);
		cv::Mat cluster_map_frame(cluster_map_size_cv, CV_32SC1);
		cv::Mat idx_frame(img_size_cv, CV_32SC1);
		cv::Mat idx_svg_frame(img_size_cv, CV_8UC4);
		cv::Mat idx_cluster_frame(img_size_cv, CV_32SC1);
		cv::Mat adjacency_frame(adjacency_size_cv, CV_32SC1);
		cv::Mat similar_frame(adjacency_size_cv, CV_32FC1);
		
		std::vector<gSLICr::objects::spixel_info> spixel_info_cvt_t;
		std::vector<gSLICr::objects::spixel_info> spixel_info_org_t;

		int save_count = 0;
		int do_count = 0;
		const int COUNT_MAX = 1;
		while (do_count++<COUNT_MAX)
		{

			{
				TimeMeasure tm("cpy.superpixel.cpy");
				TimeMeasure::Config(0, 0);
				/*-------------------------------------------------------------------------*/
#if 1
				MemcpyCv_gSLICr::load_Iplimage4u_to_4image_4u(_img, in_img.get());

				gSLICr_engine->Process_Frame(in_img.get());
				gSLICr_engine->Draw_Segmentation_Result(out_img.get());

				gSLICr_engine->Perform_Cluster();
				gSLICr_engine->MEM_GPU_to_CPU();				
				gSLICr_engine->Perform_Cluster_CPU();

				/*-------------------------------------------------------------------------*/
				const gSLICr::IntImage * idx_img = gSLICr_engine->Get_Seg_Res();
				const int* inimg_ptr = idx_img->GetData(MEMORYDEVICE_CPU);
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(idx_img, idx_frame);
				cfg_dbg.SaveImage(idx_frame,
					file_name_t,
					"idx.frame");
		
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(out_img.get(), boundry_draw_frame);
				cfg_dbg.SaveImage(boundry_draw_frame,
					file_name_t,
					"boundry.draw.frame");
				
				/*-------------------------------------------------------------------------*/
				gSLICr_engine->MEM_GPU_to_CPU_Spixel_Map();
				const std::vector<gSLICr::objects::spixel_info> spixel_info_center_t= gSLICr_engine->Get_Spixel_Map_Vector();
#if 0

				cfg_dbg.SaveImage_Width_Idx(
					boundry_draw_frame,
					file_name_t,
					"txt.idx.frame",
					spixel_info_center_t,
					M_Gray_Color_th);
#endif // 0


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
				spixel_info_cvt_t = gSLICr_engine->Get_Spixel_Map_Cvt_Vector();
				spixel_info_org_t = gSLICr_engine->Get_Spixel_Map_Vector();

				const ORUtils::Vector2<int> Spixel_Map_noDims_t =gSLICr_engine->GetSegEngineGPUCluster()->Get_Spixel_Map_noDims();

#if 1

				cfg_dbg.SaveImage_Width_Idx(
					boundry_draw_frame,
					file_name_t,
					"txt.idx.frame",
					spixel_info_cvt_t,
					SGV_GLOBAL::M_GRAY_COLOR_TH);

				cfg_dbg.Save_Spixel_Map_And_Cvt_Vector(
					Spixel_Map_noDims_t,
					spixel_info_cvt_t,
					spixel_info_org_t,
					file_name_t,
					"Save_Spixel_Map_Cvt_Vector");
#endif  
				
				/*-------------------------------------------------------------------------*/
				gSLICr_engine->Draw_Segmentation_Cluster_Result(out_img.get());
				MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(out_img.get(), boundry_cluster_draw_frame);
				cfg_dbg.SaveImage(boundry_cluster_draw_frame,
					file_name_t,
					"boundry.cluster.frame");

#if TRUE
				/*-------------------------------------------------------------------------*/
				FuzzyMethod::FuzzySuperPixel_Method(
					SGV_GLOBAL::FUZZY_METHOD_SVG,
					SGV_GLOBAL::AH_VP,
					idx_cluster_frame.ptr<int>(0),
					SpixelDim,
					WIDTH,
					HEIGHT,
					idx_svg_frame.ptr<int>(0));

				/*-------------------------------------------------------------------------*/
				cfg_dbg.SaveImage(idx_svg_frame,
					file_name_t,
					"idx_svg_frame");
				/*-------------------------------------------------------------------------*/

				MemcpyCv_gSLICr::cpy_svg_2_img(
					boundry_cluster_draw_frame,
					idx_svg_frame,
					boundry_cluster_draw_frame);
				
				cfg_dbg.SaveImage(boundry_cluster_draw_frame,
					file_name_t,
					"boundry.svg.draw.frame");
#endif // TRUE
#endif // 0
				/*-------------------------------------------------------------------------*/				
				TimeMeasure::Config(1, 1);
			}
#if 0
			imshow("segmentation", boundry_draw_frame);

			int key = cv::waitKey(1);
			if (key == 27) break;
			else if (key == 's')
			{
				printf("\nsaved segmentation %04i\n", save_count);
				save_count++;
			}
#endif // 0


		}

	}

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST(
	const std::string _file_full_name,
	const IplImage* _img,
	const std::string _saveLocation)
{
	TimeMeasure::Config(1, 1);
	{
		
		const int HEIGHT = _img->height;
		const int WIDTH = _img->width;
										
		cv::Size img_size_cv(WIDTH, HEIGHT);
		cv::Mat idx_svg_frame(img_size_cv, CV_8UC4);
	
		int do_count = 0;
		const int COUNT_MAX = 10;
		while (do_count++<COUNT_MAX)
		{
				TimeMeasure tm("1.frame.car.cluster");
				SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(_img,idx_svg_frame);							
		}

	}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(
	const IplImage * _img,
	cv::Mat & _svg_idx_frame)
{	
	
	const char*		IMG_SRC = _img->imageData;
	const int		ImageSize = _img->imageSize;
	const int		WIDTH = _img->width;
	const int		HEIGHT = _img->height;	
	int*		IMG_SVG_DATA = _svg_idx_frame.ptr<int>(0);
	
	SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(
											IMG_SRC,
											ImageSize,
											WIDTH,
											HEIGHT,
											IMG_SVG_DATA);
	
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(
	const QImage & _imgSrc,
	const QImage & _imgSVG)
{

	const char*		IMG_SRC = (const char*) _imgSrc.bits();
	const int		ImageSize = _imgSrc.byteCount();
	const int		WIDTH =		_imgSrc.width();
	const int		HEIGHT =	_imgSrc.height();
	int*		IMG_SVG_DATA = (int*) _imgSVG.bits();

	SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(
		IMG_SRC,
		ImageSize,
		WIDTH,
		HEIGHT,
		IMG_SVG_DATA);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::SVG_NAVIGATION_CAR_CLUSTER_FAST_1_FRAME(
	const char*	_IMG_SRC,
	const int	_ImageSize,
	const int	_WIDTH,
	const int	_HEIGHT,
	int*		_IMG_SVG_DATA)
{
	
	/*-------------------------------------------------------------------------*/
	SGV_GLOBAL::InitCoreEngineCluster(_WIDTH, _HEIGHT);
	/*-------------------------------------------------------------------------*/
	std::shared_ptr<gSLICr::engines::core_engine_cluster>  gSLICr_engine = SGV_GLOBAL::GetCoreEngineCluster();
	/*-------------------------------------------------------------------------*/
	const int	SpixelDim = gSLICr_engine->SpixelNum();
	/*-------------------------------------------------------------------------*/
	{
		TimeMeasure tm("gSLICr");
		gSLICr_engine->Process_Frame(_IMG_SRC, _ImageSize);
	}
	/*-------------------------------------------------------------------------*/
	{
		TimeMeasure tm("cluster gpu");
		gSLICr_engine->Perform_Cluster();
	}
	/*-------------------------------------------------------------------------*/
	{
		TimeMeasure tm("memcpy GPU to CPU");
		gSLICr_engine->MEM_GPU_to_CPU();
	}
	/*-------------------------------------------------------------------------*/
	{
		TimeMeasure tm("cluster cpu");
		gSLICr_engine->Perform_Cluster_CPU();
	}
	/*-------------------------------------------------------------------------*/
	{
		TimeMeasure tm("svg");
		const gSLICr::IntImage * seg_cluster = gSLICr_engine->Get_Cluster_Idx_Seg();
		const int* seg_cluster_ptr = seg_cluster->GetData(MEMORYDEVICE_CPU);

		FuzzyMethod::FuzzySuperPixel_Method(
			SGV_GLOBAL::FUZZY_METHOD_SVG,
			SGV_GLOBAL::AH_VP,
			seg_cluster_ptr,
			SpixelDim,
			_WIDTH,
			_HEIGHT,
			_IMG_SVG_DATA);
	}
	/*-------------------------------------------------------------------------*/

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::METHOD_PATH_CFG()
{

	SGV_CFG_DBG cfg_dbg;
	cfg_dbg.InitLoad();

	const QString path_qstr = cfg_dbg.getSourcePath();

	QString path_native_t = QDir::toNativeSeparators(path_qstr);

	QFileInfo fi(path_native_t);

	if (fi.exists()){

			if(fi.isFile()){
				METHOD_FILE(path_native_t.toStdString());
			}else{

			}

			if (fi.isDir()){
				METHOD_PATH(path_native_t.toStdString());
			}

	}
			
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_Method::METHOD_PATH(const std::string _path)
{

	std::vector<std::string> files_t;

	Base::FS_getFiles(_path,"png",files_t);
	Base::FS_getFiles(_path, "jpg", files_t);
	
	for each (const std::string file_img_t in files_t){
		METHOD_FILE(file_img_t);
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
		
		

	}else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR) == 0) {

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

	}else if (method_t.compare(SGV_CFG_ARITHMETIC::NODE_METHOD_NAV_CAR_CLUSTER_FAST) == 0){

		SVG_NAVIGATION_CAR_CLUSTER_FAST(
			_f,
			_img,
			saveLocation);

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