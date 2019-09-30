// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*----------------------------------------------------------------*/
#pragma once
/*----------------------------------------------------------------*/
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_spixel_info.h"
/*----------------------------------------------------------------*/
#include <assert.h>
/*----------------------------------------------------------------*/
using namespace gSLICr;
using namespace gSLICr::objects;
using namespace gSLICr::engines;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void  DgbCheckRange(
	const double& _f,
	const double& _min,
	const double& _max,
	const double& _eps)
{
#if _DEBUG
	assert(_f >= _min - _eps && _f <= _max + _eps);
#endif // _DEBUG
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void  DgbCheck01(const double _f)
{
	const double EPS = 1E-3;
	DgbCheckRange(_f, 0, 1, EPS);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void  DgbCheckLThetaM(const Vector4f _f)
{
	DgbCheck01(_f.l);
	DgbCheck01(_f.a);
	DgbCheck01(_f.b);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void  DgbCheckLAB_100_128(const Vector4f _f)
{
	const double EPS = 1E-3;
	const double AB_MIN=-127;
	const double AB_MAX=128;
	DgbCheckRange(_f.L, 0, 100, EPS);
	DgbCheckRange(_f.A, AB_MIN, AB_MAX, EPS);
	DgbCheckRange(_f.B, AB_MIN, AB_MAX, EPS);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void  DgbCheck_LThetaM_0_1(const Vector4f _f)
{
	const double EPS = 1E-3;
	const double MIN = 0;
	const double MAX = 1;
	DgbCheckRange(_f.l, MIN, MAX, EPS);
	DgbCheckRange(_f.theta, MIN, MAX, EPS);
	DgbCheckRange(_f.m, MIN, MAX, EPS);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
