// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*----------------------------------------------------------------*/
#pragma once
/*----------------------------------------------------------------*/
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_spixel_info.h"
/*----------------------------------------------------------------*/
#include <assert.h>
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