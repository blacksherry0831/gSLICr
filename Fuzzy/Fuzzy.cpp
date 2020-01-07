#include "Fuzzy.h"
/*-----------------------------------------*/
 int	Fuzzy::HEIGHT=0;
 float  Fuzzy::Seg_HorizontalLinePosScale=0;
/*-----------------------------------------*/
 float  Fuzzy::pYweight_V[Y_HEIGHT_MAX];
 float  Fuzzy::pYweight_G[Y_HEIGHT_MAX];
 float  Fuzzy::pYweight_S[Y_HEIGHT_MAX];
 /*-----------------------------------------*/
 cv::Mat  Fuzzy::FuzzyResult_Classify;
 cv::Mat  Fuzzy::FuzzyResult_S;
 cv::Mat  Fuzzy::FuzzyResult_V;
 cv::Mat  Fuzzy::FuzzyResult_G;
 cv::Mat  Fuzzy::FuzzyResult_Count;
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
Fuzzy::Fuzzy(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
Fuzzy::~Fuzzy(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
inline double Fuzzy::Gx_InDoor20150603(int y, int n, float H0, float Hg, int H)
{
	double Pn = 1.0*(2 * n + 2) / (2 * n + 1);
	double Gy = 0;
	double C_g = Pn / powl(H - Hg - H0, Pn);
	double yHg = 0;

	if (y >= Hg) {
		yHg = powl(y - Hg, 1.0 / (2 * n + 1));
	}
	else if (y<Hg) {
		yHg = -1 * powl(Hg - y, 1.0 / (2 * n + 1));
	}
	Gy = C_g*yHg;
	return Gy;
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
inline double Fuzzy::Sx_InDoor20150603(int y, int n, float H0, float Hc, int H)
{
	double Pn = 1.0*(2 * n + 2) / (2 * n + 1);
	double Gy = 0;
	double C_g = Pn / powl(H0 - Hc, Pn);
	double yHg = 0;

	if (y <= -1 * Hc) {
		yHg = powl(-1 * y - Hc, 1.0 / (2 * n + 1));
	}
	else if (y>-1 * Hc) {
		yHg = -1 * powl(y + Hc, 1.0 / (2 * n + 1));
	}
	Gy = C_g*yHg;
	return Gy;
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::FillWeightArrayV_Gaussian(double horizontal_line, double n, double SigmaScale, double WeightScale)
{
	TRACE_FUNC();
	{
#if 1
		//室外原始和室内叠加
		double sigma;
		double L, L_1, L_2;
		L_1 = horizontal_line;
		L_2 = HEIGHT - horizontal_line;
		L = (L_1>L_2) ? L_2 : L_1;
		sigma = L / SigmaScale;

		for (register int i = -L; i<L; i++) {
			if ((horizontal_line - i) >= 0 && (horizontal_line - i)< HEIGHT) {

				double constant_t = (1 / (sqrt(2 * M_PI)*sigma))*WeightZoom*WeightScale;
				double variable_t = exp(-powl(i, 2) / powl(sigma, 2));
				double result = constant_t*variable_t;
				pYweight_V[(int)horizontal_line - i] += constant_t*variable_t;
			}
		}
#endif
	}
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::InitYweightTable_SVG(const int _height,const float _HorizontalLinePosScale)
{

	if (HEIGHT != _height){

			HEIGHT = _height;
			Seg_HorizontalLinePosScale = _HorizontalLinePosScale;

			const float horizontal_line = Seg_HorizontalLinePosScale*HEIGHT;

			FillWeightArrayS_InDoor20150603(horizontal_line, 1);
			FillWeightArrayV_Gaussian(horizontal_line, 1,6,2);			
			FillWeightArrayG_InDoor20150603(horizontal_line, 1);
			
	}

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::InitYweightTable_VG(const int _height, const float _HorizontalLinePosScale)
{

	if (HEIGHT != _height) {

		HEIGHT = _height;
		Seg_HorizontalLinePosScale = _HorizontalLinePosScale;

		const float horizontal_line = Seg_HorizontalLinePosScale*HEIGHT;

		FillWeightArrayV_Gaussian(horizontal_line, 1, 6, 2);
		FillWeightArrayG_InDoor20150603(horizontal_line, 1);

	}

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::MallocResultMemory(const cv::Size & _sp_num)
{
	FuzzyResult_Classify.create(_sp_num, CV_32SC1);
	FuzzyResult_S.create(_sp_num, CV_32FC1);
	FuzzyResult_V.create(_sp_num, CV_32FC1);
	FuzzyResult_G.create(_sp_num, CV_32FC1);
	FuzzyResult_Count.create(_sp_num, CV_32SC1);
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_Property(
	const float* _p,
	float * _mat,
	const int _dim,
	const int * _label,
	const int _w,
	const int _h)
{

	int* sp_size_ptr=new int[_dim];
	
	memset(sp_size_ptr,0,sizeof(int)*_dim);
	memset(_mat, 0, sizeof(float)*_dim);

	for (int wi = 0; wi < _w; wi++){
		for (int hi = 0; hi < _h; hi++){
			const int IDX = wi + hi*_w;
			const int SP_IDX = _label[IDX];
			assert(SP_IDX < _dim);
			_mat[SP_IDX]+=_p[hi];
			sp_size_ptr[SP_IDX]++;

		}
	}
	
	for (int spi = 0; spi < _dim; spi++){

		if (sp_size_ptr[spi] ==0){
			
		}
		else {
			_mat[spi]/=sp_size_ptr[spi];
		}
		
	}

	delete[]sp_size_ptr;

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_S(
	const int _dim,
	const int * _label,
	const int _w,
	const int _h)
{
	float * _mat=FuzzyResult_S.ptr<float>(0);

	Fuzzy_Property(
		pYweight_S,
		_mat,
		_dim,
		_label,
		_w,
		_h);
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_V( const int _dim, const int * _label, const int _w, const int _h)
{
	float * _mat= FuzzyResult_V.ptr<float>(0);

	Fuzzy_Property(
		pYweight_V,
		_mat,
		_dim,
		_label,
		_w,
		_h);
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_G(const int _dim, const int * _label, const int _w, const int _h)
{
	float * _mat= FuzzyResult_G.ptr<float>(0);

	Fuzzy_Property(
		pYweight_G,
		_mat,
		_dim,
		_label,
		_w,
		_h);
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_VG_FAST(
	const int _dim,
	const int * _label,
	const int _w,
	const int _h)
{
	
	FuzzyResult_Count.setTo(cv::Scalar::all(0));
	FuzzyResult_V.setTo(cv::Scalar::all(0));
	FuzzyResult_G.setTo(cv::Scalar::all(0));

	int*	fuzzy_count_ptr	= FuzzyResult_Count.ptr<int>(0);
	float*	fuzzy_v_ptr		= FuzzyResult_V.ptr<float>(0);
	float*	fuzzy_g_ptr		= FuzzyResult_G.ptr<float>(0);

	for (int wi = 0; wi < _w; wi++) {
		for (int hi = 0; hi < _h; hi++) {
			const int IDX = wi + hi*_w;
			const int SP_IDX = _label[IDX];
			assert(SP_IDX < _dim);
			fuzzy_v_ptr[SP_IDX] += pYweight_V[hi];
			fuzzy_g_ptr[SP_IDX] += pYweight_G[hi];
			fuzzy_count_ptr[SP_IDX]++;

		}
	}

	for (int spi = 0; spi < _dim; spi++) {
		const int sp_count = fuzzy_count_ptr[spi];
		if (sp_count == 0) {

		}else {
			fuzzy_v_ptr[spi] /= sp_count;
			fuzzy_g_ptr[spi] /= sp_count;
		}
	}
	
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_Classify(
	int * _mat_Classify,
	const float * _mat_S,
	const float * _mat_V,
	const float * _mat_G,
	const int _dim)
{

	for (int spi = 0; spi < _dim; spi++){

		const int Classify_t=GetFuzzyClassify(_mat_S[spi], _mat_V[spi], _mat_G[spi]);
		_mat_Classify[spi] = Classify_t;
	
	}

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_Classify_SVG()
{

	int*	mat_Classify= FuzzyResult_Classify.ptr<int>(0);

	float*	fuzzy_s_ptr = FuzzyResult_S.ptr<float>(0);
	float*	fuzzy_v_ptr = FuzzyResult_V.ptr<float>(0);
	float*	fuzzy_g_ptr = FuzzyResult_G.ptr<float>(0);
	const int		dim = FuzzyResult_G.size().width;

	Fuzzy_Classify(
		mat_Classify,
		fuzzy_s_ptr,
		fuzzy_v_ptr,
		fuzzy_g_ptr,
		dim);

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_Classify_VG()
{
	int* fuzzy_classify=FuzzyResult_Classify.ptr<int>(0);
	const int sp_num = FuzzyResult_Classify.size().width;

	const float*	fuzzy_v_ptr = FuzzyResult_V.ptr<float>(0);
	const float*	fuzzy_g_ptr = FuzzyResult_G.ptr<float>(0);

	for (int spi = 0; spi < sp_num; spi++) {

		const int Classify_t = GetFuzzyClassify_VG(fuzzy_v_ptr[spi], fuzzy_g_ptr[spi]);
		fuzzy_classify[spi] = Classify_t;

	}

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_Label(
	const int * _mat_Classify,
	const int _dim,
	int * _label_svg,
	const int * _label,
	const int _w,
	const int _h)
{

	const int SZ=_w*_h;
	for (int pi = 0; pi < SZ; pi++){
			const int SP_IDX = _label[pi];
			assert(SP_IDX<=_dim);
			const int SVG_IDX = _mat_Classify[SP_IDX];
			assert(SVG_IDX==FUZZY_SKY || SVG_IDX == FUZZY_V || SVG_IDX == FUZZY_GND);
			_label_svg[pi]=SVG_IDX;
		
	}

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
void Fuzzy::Fuzzy_Label_Ex(
	const int _dim,
	int * _label_svg,
	const int * _label,
	const int _w,
	const int _h)
{

	const int * mat_Classify = FuzzyResult_Classify.ptr<int>(0);

	Fuzzy::Fuzzy_Label(
		mat_Classify,
		_dim,
		_label_svg,
		_label,
		_w,
		_h);

}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
int Fuzzy::GetFuzzyClassify(
	const float _mat_S,
	const float _mat_V,
	const float _mat_G)
{

	if (_mat_S>=std::max(_mat_V,_mat_G)){
		return FUZZY_SKY;
	}else if (_mat_V>=std::max(_mat_S, _mat_G)){
		return FUZZY_V;
	}else if (_mat_G>=std::max(_mat_S, _mat_V)) {
		return FUZZY_GND;
	}
	assert(0);
	return FUZZY_NOT;
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/
int Fuzzy::GetFuzzyClassify_VG(
	const float& _mat_V,
	const float& _mat_G)
{

	if (_mat_V >=  _mat_G) {
		return FUZZY_V;
	}
	else if (_mat_G >= _mat_V) {
		return FUZZY_GND;
	}
	else
	{

	}
	assert(0);
	return FUZZY_NOT;
}
/*---------------------------------------------------------------------------------------------------*/
/**
*地面重力场视觉模糊分布密度函数G
*
*@param horizontal_line 水平线位置
*@param n
*@note
*@image html image_fuzzy_sky_ground_vertical.jpg 图像中视平线以及天花板和地面可能出现的区域
*/
/*---------------------------------------------------------------------------------------------------*/
void  Fuzzy::FillWeightArrayG_InDoor20150603(const double _horizontal_line,const double n)
{
	TRACE_FUNC();

	const float PgOffset = 0;
	const float PsOffset = 0;
		
	const float HgPos = _horizontal_line + PgOffset*HEIGHT;
	const float HsPos = _horizontal_line - PsOffset*HEIGHT;
	const float Hg = HgPos - _horizontal_line;
	const float H0 = _horizontal_line;
	const float HC = _horizontal_line - HsPos;
	

	for (int i = 0; i<HEIGHT; i++) {
		const int x = i - H0;
		const int YIdx = i;
		pYweight_G[YIdx] = Gx_InDoor20150603(x, 1, H0, Hg, HEIGHT)*WeightZoom;
	}

}
/*--------------------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*-------------------------------------------------------------------------------------------------------*/
void   Fuzzy::FillWeightArrayS_InDoor20150603(const double _horizontal_line,const  double _n)
{
	TRACE_FUNC();

	const float PgOffset = 0;
	const float PsOffset = 0;
	
	float HgPos = _horizontal_line + PgOffset*HEIGHT;
	float HsPos = _horizontal_line - PsOffset*HEIGHT;
	float Hg = HgPos - _horizontal_line;
	float H0 = _horizontal_line;
	float HC = _horizontal_line - HsPos;
	//////////////////////////////////////////////////////////////////////
	for (int i = 0; i<HEIGHT; i++) {
		int x = i - H0;
		int YIdx = i;
		pYweight_S[YIdx] = Sx_InDoor20150603(x, 1, H0, HC, HEIGHT)*WeightZoom;
	}
	///////////////////////////////////////////////////////////////////////
}
/*--------------------------------------------------------------------*/
/**
*
*
*/
/*--------------------------------------------------------------------*/