#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
#include <cv.h>
/*-----------------------------------------*/
#define  WeightZoom (10000)
#define  Y_HEIGHT_MAX	(3000)
/*-----------------------------------------*/
#define BlackColorPNG (0xff000000)
#define WhiteColorPNG (0xffffffff)
#define SkyColorPNG      (0xD04B4587)
#define VerticalColorPNG (0xE0ff0000)
#define GroundColorPNG   (0xF04D9D7B)
/*-----------------------------------------*/
#define		FUZZY_SKY	(0xD04B4587)
#define		FUZZY_V		(0xE0ff0000)
#define		FUZZY_GND	(0xF04D9D7B)
#define		FUZZY_NOT	(-1)
/*-----------------------------------------*/
class Fuzzy
{
public:
	Fuzzy(void);
	~Fuzzy(void);
public:
	static float PgOffset;
	static float PsOffset;
public:
	static double Gx_Pn_c(const int n);
	static double Gx_Pn_v(const int n);

	static double Gx_InDoor20150603(int y, int n, float H0, float Hg, int H);
	static double Sx_InDoor20150603(int y, int n, float H0, float Hc, int H);

	static void FillWeightArrayV_Gaussian(
		const double _horizontal_line,
		const double _n,
		double _SigmaScale,
		double _WeightScale);

public:
	static void FillWeightArrayG_InDoor20150603(const double _horizontal_line,const double _n);
	static void FillWeightArrayS_InDoor20150603(const double _horizontal_line,const double _n);
public:
	static  int HEIGHT;
	static	float Seg_HorizontalLinePosScale;
public:
	static  float pYweight_S[Y_HEIGHT_MAX];
	static  float pYweight_V[Y_HEIGHT_MAX];
	static  float pYweight_G[Y_HEIGHT_MAX];
private:
	static cv::Mat  FuzzyResult_Classify;
	static cv::Mat  FuzzyResult_S;
	static cv::Mat  FuzzyResult_V;
	static cv::Mat  FuzzyResult_G;
	static cv::Mat  FuzzyResult_Count;
public:
	static void InitYweightTable_SVG(const int _height, const float _HorizontalLinePosScale);
	static void InitYweightTable_VG(const int _height, const float _HorizontalLinePosScale);
public:
	static void MallocResultMemory(const cv::Size& _sp_num);
public:
	static void Fuzzy_Property(
		const float* _p,
		float * _mat,
		const int _dim,
		const int * _label,
		const int _w,
		const int _h);

	static void Fuzzy_S(
		const int _dim,
		const int * _label,
		const int _w,
		const int _h);

	static void Fuzzy_V(
		const int _dim,
		const int * _label,
		const int _w,
		const int _h);

	static void Fuzzy_G(
		const int _dim,
		const int * _label,
		const int _w,
		const int _h);

	static void Fuzzy_VG_FAST(
		const int _dim,
		const int * _label,
		const int _w,
		const int _h);

	static void Fuzzy_Classify(
		int		* _mat_Classify,
		const float * _mat_S,
		const float * _mat_V,
		const float * _mat_G,
		const int _dim);

	static void Fuzzy_Classify_SVG();

	static void Fuzzy_Classify_VG();
	
	static void Fuzzy_Label(
		const int*		_mat_Classify,
		const int		_dim,
		int*			_label_svg,
		const int*		_label,
		const int		_w,
		const int		_h);

	static void Fuzzy_Label_Ex(
		const int _dim,
		int * _label_svg,
		const int * _label,
		const int _w,
		const int _h);
			
	static int GetFuzzyClassify(		
		const float  _mat_S,
		const float  _mat_V,
		const float  _mat_G);

	static int GetFuzzyClassify_VG(
		const float& _mat_V,
		const float& _mat_G);

};