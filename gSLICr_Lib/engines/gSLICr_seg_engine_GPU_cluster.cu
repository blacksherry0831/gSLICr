// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_cluster_base.h"
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU_cluster.h"
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
__global__ void Find_Adjacency_Matrix(
	const int * inimg,
	int * outimg,
	const  gSLICr::Vector2i img_size,
	const  gSLICr::Vector2i adj_size);
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
__global__ void Find_Adjacency_Matrix(
	const int * inimg,
	int * outimg,
	const  gSLICr::Vector2i img_size,
	const  gSLICr::Vector2i adj_size)
{
	const int x = threadIdx.x + blockIdx.x * blockDim.x, y = threadIdx.y + blockIdx.y * blockDim.y;
	const int BORDER = 1;
	if (x < img_size.x - BORDER &&
		y < img_size.y - BORDER &&
		x >= BORDER &&
		y >= BORDER) {

		find_adjacency_matrix_base(inimg, outimg, img_size, adj_size, x, y);

	}
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
seg_engine_GPU_cluster::seg_engine_GPU_cluster(const objects::settings& in_settings) : seg_engine_GPU(in_settings)
{
	
	const int AdjDim = this->SpixelNum();

	const Vector2i link_size_t(AdjDim, AdjDim);

	adj_img = new IntImage(link_size_t, true, true);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
seg_engine_GPU_cluster::~seg_engine_GPU_cluster()
{
	if (adj_img != NULL) delete adj_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Find_Adjacency_Matrix_E()
{
	const int* inimg_ptr = idx_img->GetData(MEMORYDEVICE_CUDA);
	int* outimg_ptr = adj_img->GetData(MEMORYDEVICE_CUDA);
	const Vector2i img_size = source_img->noDims;
	const Vector2i adj_size = adj_img->noDims;
	const dim3 blockSize(BLOCK_DIM, BLOCK_DIM);
	const dim3 gridSize((int)ceil((float)img_size.x / (float)blockSize.x), (int)ceil((float)img_size.y / (float)blockSize.y));

	Find_Adjacency_Matrix << <gridSize, blockSize >> >(inimg_ptr, outimg_ptr, img_size,adj_size);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Perform_Cluster()
{
	this->Update_Cluster_Center();
	this->Find_Adjacency_Matrix_E();

	cudaThreadSynchronize();

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
int gSLICr::engines::seg_engine_GPU_cluster::SpixelNum() const
{
	return this->spixel_map->noDims.x * this->spixel_map->noDims.y;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const IntImage * gSLICr::engines::seg_engine_GPU_cluster::Get_Adjacency_Matrix()
{
	adj_img->UpdateHostFromDevice();
	return adj_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/