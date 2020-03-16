#pragma once
/*-----------------------------------------*/
#include "Fuzzy.h"
#include "opencv_basic.h"
/*-----------------------------------------*/
class FuzzyMethod
{
public:
	FuzzyMethod(void);
	~FuzzyMethod(void);
	
public:
	
	static void FuzzySuperPixel(
		const float _hl_vp,
		const int * _label,
		const int _spixelNum,
		const int _width,
		const int _height,
		int * _label_svg);

	static void FuzzySuperPixel_VG(
		const float _hl_vp,
		const int * _label,
		const int _spixelNum,
		const int _width,
		const int _height,
		int * _label_svg);

	static void FuzzySuperPixel_VG_FAST(
		const float _hl_vp,
		const float	_sigma_force_scale,
		const float	_sigma_scale,
		const int * _label,
		const int _spixelNum,
		const int _width,
		const int _height,
		int * _label_svg);

	static void FuzzySuperPixel_Method(
		const std::string _method,
		const float _hl_vp,
		const int * _label,
		const int _spixelNum,
		const int _width,
		const int _height,
		int * _label_svg);

public:


};