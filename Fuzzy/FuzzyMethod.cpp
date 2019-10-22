#include "FuzzyMethod.h"
/*-----------------------------------------*/

/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
FuzzyMethod::FuzzyMethod(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
FuzzyMethod::~FuzzyMethod(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void FuzzyMethod::FuzzySuperPixel(
	const float _hl_vp,
	const int * _label,
	const int _spixelNum,
	const int _width,
	const int _height,
	int * _label_svg)
{
	Fuzzy::InitYweightTable_SVG(_height, _hl_vp);

	cv::Size fuzzy_size(_spixelNum, 1);

	cv::Mat  fuzzy_Classify(fuzzy_size, CV_32SC1);
	cv::Mat  fuzzy_S(fuzzy_size, CV_32FC1);
	cv::Mat  fuzzy_V(fuzzy_size, CV_32FC1);
	cv::Mat  fuzzy_G(fuzzy_size, CV_32FC1);

	int *fuzzy_Classify_Ptr = fuzzy_Classify.ptr<int>(0);

	Fuzzy::Fuzzy_S(fuzzy_S.ptr<float>(0), _spixelNum, _label, _width, _height);
	Fuzzy::Fuzzy_V(fuzzy_V.ptr<float>(0), _spixelNum, _label, _width, _height);
	Fuzzy::Fuzzy_G(fuzzy_G.ptr<float>(0), _spixelNum, _label, _width, _height);

	Fuzzy::Fuzzy_Classify(
		fuzzy_Classify_Ptr,
		fuzzy_S.ptr<float>(0),
		fuzzy_V.ptr<float>(0),
		fuzzy_G.ptr<float>(0),
		_spixelNum);


	Fuzzy::Fuzzy_Label(
		fuzzy_Classify_Ptr,
		_spixelNum,
		_label_svg,
		_label,
		_width,
		_height);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void FuzzyMethod::FuzzySuperPixel_VG(
	const float _hl_vp,
	const int * _label,
	const int _spixelNum,
	const int _width,
	const int _height,
	int * _label_svg)
{

	Fuzzy::InitYweightTable_VG(_height, _hl_vp);

	cv::Size fuzzy_size(_spixelNum, 1);

	cv::Mat  fuzzy_Classify(fuzzy_size, CV_32SC1);
	cv::Mat  fuzzy_V(fuzzy_size, CV_32FC1);
	cv::Mat  fuzzy_G(fuzzy_size, CV_32FC1);

	int *fuzzy_Classify_Ptr = fuzzy_Classify.ptr<int>(0);

	
	Fuzzy::Fuzzy_V(fuzzy_V.ptr<float>(0), _spixelNum, _label, _width, _height);
	Fuzzy::Fuzzy_G(fuzzy_G.ptr<float>(0), _spixelNum, _label, _width, _height);

	Fuzzy::Fuzzy_Classify_VG(
		fuzzy_Classify_Ptr,
		fuzzy_V.ptr<float>(0),
		fuzzy_G.ptr<float>(0),
		_spixelNum);


	Fuzzy::Fuzzy_Label(
		fuzzy_Classify_Ptr,
		_spixelNum,
		_label_svg,
		_label,
		_width,
		_height);

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void FuzzyMethod::FuzzySuperPixel_Method(
	const std::string _method,
	const float _hl_vp,
	const int * _label,
	const int _spixelNum,
	const int _width,
	const int _height,
	int * _label_svg)
{

	if (0 == _method.compare("svg")){
		
		FuzzySuperPixel(
			_hl_vp,
			_label,
			_spixelNum,
			_width,
			_height,
			_label_svg);

	}else if (0 == _method.compare("vg")){

		FuzzySuperPixel_VG(
			_hl_vp,
			_label,
			_spixelNum,
			_width,
			_height,
			_label_svg);

	}else{


	}



}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/