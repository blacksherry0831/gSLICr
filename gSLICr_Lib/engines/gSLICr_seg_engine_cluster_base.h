// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*----------------------------------------------------------------*/
#pragma once
/*----------------------------------------------------------------*/
#include "../gSLICr_defines.h"
/*----------------------------------------------------------------*/
#include "../objects/gSLICr_spixel_info.h"
/*----------------------------------------------------------------*/
#include "gSLICr_dbg.h"
/*----------------------------------------------------------------*/
#define _USE_MATH_DEFINES
#include <cmath>
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
using namespace gSLICr;
using namespace gSLICr::objects;
using namespace gSLICr::engines;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
__constant__ const int dx4[4] = { -1,	0,	0,	1 };
__constant__ const int dy4[4] = { 0,	1,	-1,	0 };
__constant__ const int dxy4_Pixels = 4;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void find_adjacency_matrix_base(
	const int * inimg,
	int * outimg,
	const gSLICr::Vector2i img_size,
	const gSLICr::Vector2i adj_size,
	const int x,
	const int y)
{
	
	const int idx_center = x + y*img_size.x;
	const int label_center = inimg[idx_center];

	for (size_t pi = 0; pi < dxy4_Pixels; pi++){
			const int x_n =x+ dx4[pi];
			const int y_n =y+ dy4[pi];

			assert(x_n>=0 && x_n<img_size.x);
			assert(y_n>=0 && y_n<img_size.y);

			const int idx_neighbor=x_n+y_n*img_size.x;
			const int label_neighbor= inimg[idx_neighbor];
			
			if (label_center !=label_neighbor ){
				outimg[label_center + label_neighbor*adj_size.x] = 1;
			}

	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void lab2LThetaM(
	const gSLICr::Vector4f& pix_in,
	gSLICr::Vector4f& pix_out)
{
	const float Sqrt2 = 1.4142135623731;
	const float AB_MAX = 128;
	const float LAB_M_MAX = AB_MAX * Sqrt2;
	const float X2_PI = 2 * M_PI;
	///////////////////////////////////////
	if (pix_in.A == pix_in.B && pix_in.B == 0) {
		pix_out.theta = 0;
	}
	else
	{
		const float theta_arc = atan2(pix_in.B, pix_in.A);//(-pi,pi]
		pix_out.theta = theta_arc / X2_PI + 0.5F;
	}
	///////////////////////////////////////
	const float m_ab = sqrt(pix_in.A*pix_in.A + pix_in.B*pix_in.B);
	pix_out.m = m_ab / (LAB_M_MAX);
	///////////////////////////////////////
	pix_out.l = pix_in.L / 100;
	///////////////////////////////////////
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void cvt_spixel_to_l_theta_m(
	const spixel_info* _spixel_list_src,
	spixel_info* _spixel_list_dst,
	const gSLICr::Vector2i _map_size,
	const int x,
	const int y)
{
	const int IDX = x + y*_map_size.x;

	DgbCheckLAB_100_128(_spixel_list_src[IDX].color_info);
	lab2LThetaM(_spixel_list_src[IDX].color_info, _spixel_list_dst[IDX].color_info);
	DgbCheckLThetaM(_spixel_list_dst[IDX].color_info);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int cal_spixel_similar(
	const  spixel_info&		_sp_0,
	const  spixel_info&		_sp_1,
	const float  _L_THRESHOLD=0.031F,
	const float  _M_THRESHOLD=0.020F,
	const float  _THETA_THRESHOLD=0.0156F)
{

	DgbCheck_LThetaM_0_1(_sp_0.color_info);
	DgbCheck_LThetaM_0_1(_sp_1.color_info);

	if (_sp_0.color_info.m <_M_THRESHOLD &&
		_sp_1.color_info.m<_M_THRESHOLD){

		return abs(_sp_0.color_info.l - _sp_1.color_info.l)<_L_THRESHOLD;

	}else if (_sp_0.color_info.m >=_M_THRESHOLD &&
			  _sp_1.color_info.m>=_M_THRESHOLD){

		return abs(_sp_0.color_info.theta - _sp_1.color_info.theta)<_THETA_THRESHOLD;

	}else{
		return 0;
	}

	return 0;

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void cvt_spixel_similar(
	const int *				_adj_img,
	float *					_similar_img,
	const  spixel_info*		_spixel_list,
	const  gSLICr::Vector2i _adj_size,
	const int _x,
	const int _y,
	const float  _L_THRESHOLD,
	const float  _M_THRESHOLD,
	const float  _THETA_THRESHOLD)
{
		
		const int IDX = _x + _y*_adj_size.x;
		const int ADJ= _adj_img[IDX];

		if (ADJ==0) {
				if (_x==_y){
					_similar_img[IDX] = 1;
				}				
		}else{
					_similar_img[IDX]=cal_spixel_similar(
						_spixel_list[_x] ,
						_spixel_list[_y] ,
						_L_THRESHOLD,
						_M_THRESHOLD,
						_THETA_THRESHOLD);//	Adjacent
		}
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/