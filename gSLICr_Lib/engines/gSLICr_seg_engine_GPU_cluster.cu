// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_cluster_base.h"
/*-------------------------------------------------------------------------*/
using namespace std;
using namespace gSLICr;
using namespace gSLICr::objects;
using namespace gSLICr::engines;
/*-------------------------------------------------------------------------*/
/**
*kernel function defines
*/
/*-------------------------------------------------------------------------*/
__global__ void Find_Link_Matrix(const Vector4u* inimg, Vector4f* outimg, Vector2i img_size);
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
__global__ void Find_Link_Matrix(const Vector4u * inimg, Vector4f * outimg, Vector2i img_size)
{
	const int x = threadIdx.x + blockIdx.x * blockDim.x, y = threadIdx.y + blockIdx.y * blockDim.y;
	if (x > img_size.x - 1 || y > img_size.y - 1) return;

	find_link_matrix_base(inimg, outimg, img_size, x, y);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
