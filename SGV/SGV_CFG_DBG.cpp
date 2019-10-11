#include "SGV_CFG_DBG.h"
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const QString   SGV_CFG_DBG::NODE_CFG_SAVE_IMG		=	"save.image";
const QString   SGV_CFG_DBG::NODE_CFG_SAVE_DBG		=	"save.debug";
const QString   SGV_CFG_DBG::NODE_CFG_OUTPUT_PATH	=	"output.path";
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_CFG_DBG::SGV_CFG_DBG(void)
{
	FILE_XML_CFG="cfg.svg.dbg.xml";
	DATA_CFG_PROPERTY = "debug";
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
SGV_CFG_DBG::~SGV_CFG_DBG(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_DBG::CreateChildCfgNode(QSharedPointer<QDomDocument> _Xml, QDomElement & _parent)
{
	createElement_txt_append(_Xml,_parent, NODE_CFG_PROPERTY, DATA_CFG_PROPERTY);
	createElement_txt_append(_Xml,_parent, NODE_CFG_SAVE_IMG, QString::number(0));
	createElement_txt_append(_Xml,_parent, NODE_CFG_SAVE_DBG, QString::number(0));

	createElement_txt_append(_Xml, _parent, NODE_CFG_OUTPUT_PATH, "E:\\OutPutImg\\");

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_DBG::getImgSave()
{
	return getIntFromDomDoc_Pro(NODE_CFG_SAVE_IMG);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int SGV_CFG_DBG::getDebugSave()
{
	return getIntFromDomDoc_Pro(NODE_CFG_SAVE_DBG);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
QString SGV_CFG_DBG::getOutputPath()
{
	return getStringFromDomDoc_Pro(NODE_CFG_OUTPUT_PATH);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_DBG::SaveImage(const cv::Mat _m,const std::string _file_name,const std::string _suffix)
{
	const std::string file_output = getOutputPath().toStdString();
	const std::string file_output_full_name = file_output+_file_name+"."+_suffix + ".png";
	cv::imwrite(file_output_full_name.c_str(), _m);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_DBG::SaveImage_Width_Idx(
	const gSLICr::IntImage * _idx_img,
	const std::string _file_name,
	const std::string _suffix,
	std::vector<gSLICr::objects::spixel_info> _spixels)
{
	cv::Size img_size_cv(_idx_img->noDims.x, _idx_img->noDims.y);
	cv::Mat  img_frame(img_size_cv, CV_32SC1);
	MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(_idx_img, img_frame);
	
	SaveImage_Width_Idx(
		img_frame,
		_file_name,
		_suffix,
		_spixels);
	
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void SGV_CFG_DBG::SaveImage_Width_Idx(
	cv::Mat _m,
	const std::string _file_name,
	const std::string _suffix,
	std::vector<gSLICr::objects::spixel_info> _spixels)
{
	const int SP_SZ = _spixels.size();
	const int ALPHA = 255;
	for (int i = 0; i < SP_SZ; i++) {

		const gSLICr::objects::spixel_info& spi = _spixels.at(i);

		const int x = spi.center.x;
		const int y = spi.center.y;

		const std::string idx_str = Base::int2str(spi.id);

		cv::circle(_m, cv::Point(x, y),1, cv::Scalar(255,255, 0, ALPHA),CV_FILLED);
		cv::putText(_m, idx_str, cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, 0.5, cv::Scalar(255, 0, 0, ALPHA), 1);

	}

	SaveImage(_m, _file_name, _suffix);

}
/*-------------------------------------------------------------------------*/
/**
*gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
*/
/*-------------------------------------------------------------------------*/
const void SGV_CFG_DBG::Save_Spixel_Map_Cvt_Vector(
	std::vector<gSLICr::objects::spixel_info>  _spixel_list_t,
	std::string _file_name)
{
	const int SZ = _spixel_list_t.size();
	
	
	std::string path=getOutputPath().toStdString();
	std::string file_full_name=path+_file_name;

	std::ofstream outfile;      
	outfile.open(file_full_name);
	if (!outfile) std::cout << "error" << endl;



	for (int i = 0; i < SZ; i++){
		
		const gSLICr::objects::spixel_info spi_t = _spixel_list_t.at(i);

		outfile << i << " ";
		outfile << spi_t.id<< " ";
		outfile << spi_t.no_pixels << " ";
		outfile << spi_t.center.x << " ";
		outfile << spi_t.center.y << " ";
		outfile << spi_t.color_info.l << " ";
		outfile << spi_t.color_info.theta << " ";
		outfile << spi_t.color_info.m << " ";
		outfile<< std::endl;
	}
	
}
/*-------------------------------------------------------------------------*/
/**
*gSLICr::UChar4Image* out_img = new gSLICr::UChar4Image(my_settings.img_size, true, true);
*/
/*-------------------------------------------------------------------------*/
const void SGV_CFG_DBG::Save_Spixel_Map_And_Cvt_Vector(
	const ORUtils::Vector2<int>						 _Spixel_Map_noDims_t,
	const std::vector<gSLICr::objects::spixel_info>  _spixel_list_cvt_t,
	const std::vector<gSLICr::objects::spixel_info>  _spixel_list_org_t,
	const std::string _file_name)
{
	const int SZ_CVT = _spixel_list_cvt_t.size();
	const int SZ	 = _spixel_list_org_t.size();

	assert(SZ==SZ_CVT);

	std::string path = getOutputPath().toStdString();
	std::string file_full_name = path + _file_name;

	std::ofstream outfile;
	outfile.open(file_full_name);
	if (!outfile) std::cout << "error" << endl;

		const int X_DIM = _Spixel_Map_noDims_t.y;
		const int Y_DIM = _Spixel_Map_noDims_t.x;
		int idx = 0;
		for (int xi = 0; xi <X_DIM; xi++){
		for (int yi = 0; yi <Y_DIM; yi++){
	 
				const int SPI=xi+yi*X_DIM;

				const gSLICr::objects::spixel_info spi_cvt_t = _spixel_list_cvt_t.at(SPI);
				const gSLICr::objects::spixel_info spi_org_t = _spixel_list_org_t.at(SPI);

				assert(spi_cvt_t.id == spi_org_t.id);
				assert(spi_org_t.id == idx++);
				assert(spi_cvt_t.color_info.L== spi_org_t.color_info.l);
#if 1
				/////////////////////////////////////////////////////////////////////////////
				outfile << spi_cvt_t.id << " ";
				outfile << spi_cvt_t.no_pixels << " ";
				outfile << spi_cvt_t.center.x << " ";
				outfile << spi_cvt_t.center.y << " ";
				/////////////////////////////////////////////////////////////////////////////
				outfile << spi_org_t.color_info.L << " ";
				outfile << spi_org_t.color_info.A << " ";
				outfile << spi_org_t.color_info.B << " ";
				///////////////////////////////////////////////////////////////////////////
				outfile << spi_cvt_t.color_info.l << " ";
				outfile << spi_cvt_t.color_info.theta << " ";
				outfile << spi_cvt_t.color_info.m << " ";
				////////////////////////////////////////////////////////////////////////////
				outfile << std::endl;
#endif // 1
	
		}
	}
	
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/