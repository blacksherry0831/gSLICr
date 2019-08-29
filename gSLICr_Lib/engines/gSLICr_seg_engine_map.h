// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
#pragma once
/*-------------------------------------------------------------------------*/
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_spixel_info.h"
/*-------------------------------------------------------------------------*/
#if defined(_WIN32) || defined(_WIN64) ||	defined(_MSC_VER)
#include <assert.h>
#endif
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int GetAccumMapIdx(const int _spixel_id, const int _no_blocks_per_spixel, const int _n_b)
{
	const int accum_map_idx = _spixel_id * _no_blocks_per_spixel + _n_b;
	return accum_map_idx;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int SuperPixelIdx_2_ImgCoord_Center(const int _spixel_id_xy, const int _spixel_size)
{
	const int img_sp_coord_center = _spixel_id_xy * _spixel_size + _spixel_size / 2;
	return img_sp_coord_center;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int SuperPixelIdx_2_ImgCoord_9Grid_Start(const int _spixel_id_xy, const int _spixel_size)
{
	const int img_9grid_coord_start = _spixel_id_xy * _spixel_size - _spixel_size;
	return img_9grid_coord_start;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int Grid_9_Length(const int _spixel_size)
{
	return _spixel_size * 3;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int Grid_9_PixelsSize(const int _spixel_size_x, const int _spixel_size_y)
{
	return Grid_9_Length(_spixel_size_x)*Grid_9_Length(_spixel_size_y);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline int Grid_9_Blocks(const int _spixel_size_x, const int _spixel_size_y)
{
	const int no_grid_per_center = (int)ceil(Grid_9_PixelsSize(_spixel_size_x, _spixel_size_y) / (float)(BLOCK_DIM * BLOCK_DIM));
	return no_grid_per_center;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/