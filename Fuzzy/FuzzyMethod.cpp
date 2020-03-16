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

	Fuzzy::MallocResultMemory(fuzzy_size);
		
	Fuzzy::Fuzzy_S(_spixelNum, _label, _width, _height);
	Fuzzy::Fuzzy_V(_spixelNum, _label, _width, _height);
	Fuzzy::Fuzzy_G(_spixelNum, _label, _width, _height);

	Fuzzy::Fuzzy_Classify_SVG();
	
	Fuzzy::Fuzzy_Label_Ex(
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

	Fuzzy::MallocResultMemory(fuzzy_size);
		
	Fuzzy::Fuzzy_V(_spixelNum, _label, _width, _height);
	Fuzzy::Fuzzy_G(_spixelNum, _label, _width, _height);

	Fuzzy::Fuzzy_Classify_VG();

	
		
	Fuzzy::Fuzzy_Label_Ex(
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
void FuzzyMethod::FuzzySuperPixel_VG_FAST(
	const float _hl_vp,
	const float	_sigma_force_scale,
	const float	_sigma_scale,
	const int * _label,
	const int _spixelNum,
	const int _width,
	const int _height,
	int * _label_svg)
{
	assert(_hl_vp>0 && _hl_vp<1.0F);

	Fuzzy::SetSigmaScale(_sigma_scale);

	Fuzzy::InitYweightTable_VG(_height, _hl_vp);

	cv::Size fuzzy_size(_spixelNum, 1);

	Fuzzy::MallocResultMemory(fuzzy_size);

	Fuzzy::Fuzzy_VG_FAST(_spixelNum, _label, _width, _height);

	Fuzzy::Fuzzy_Classify_VG();
			
	const double LineForce=Fuzzy::CalVerticalForceLine(
		_height,
		_hl_vp,
		_sigma_force_scale);

	Fuzzy::Fuzzy_Classify_V_Force(
		LineForce,
		_label,
		_width,
		_height);

	Fuzzy::Fuzzy_Label_Ex(
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

		FuzzySuperPixel_VG_FAST(
			_hl_vp,
			1,
			6,
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