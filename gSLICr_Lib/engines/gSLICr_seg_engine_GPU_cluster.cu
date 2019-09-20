// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_cluster_base.h"
/*-------------------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU_cluster.h"
/*-------------------------------------------------------------------------*/
using namespace gSLICr;
using namespace gSLICr::objects;
using namespace gSLICr::engines;
/*-------------------------------------------------------------------------*/
/**
*kernel function defines
*/
/*-------------------------------------------------------------------------*/
__global__ void Kernel_Find_Adjacency_Matrix(
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
__global__ void Kernel_Cvt_Spixel_to_LThetaM(
	const spixel_info* _spixel_list_src,
	spixel_info* _spixel_list_dst,
	const Vector2i _map_size)
{
	const int x = threadIdx.x + blockIdx.x * blockDim.x, y = threadIdx.y + blockIdx.y * blockDim.y;
	if (x > _map_size.x - 1 || y > _map_size.y - 1) return;
	
	cvt_spixel_to_l_theta_m(
		_spixel_list_src,
		_spixel_list_dst,
		_map_size,
		x,
		y);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
__global__ void Kernel_Cvt_Spixel_Similar(
	const int *				_adj_img,
	float *					_similar_img,
	const  spixel_info*		_spixel_list,
	const  gSLICr::Vector2i _adj_size)
{
	const int x = threadIdx.x + blockIdx.x * blockDim.x, y = threadIdx.y + blockIdx.y * blockDim.y;
	if (x > _adj_size.x - 1 || y > _adj_size.y - 1) return;

	cvt_spixel_similar(
				_adj_img,
				_similar_img,
				_spixel_list,
				_adj_size,
				x,
				y);

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

	similar_img = new FloatImage(link_size_t, true, true);

	m_spixel_map_cvt = new SpixelMap(spixel_map_size, true, true);
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
const dim3 gSLICr::engines::seg_engine_GPU_cluster::GetSuperPixelGridDim() const
{
	const Vector2i img_size = spixel_map->noDims;
	return GetGrid2Dim(img_size);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const dim3 gSLICr::engines::seg_engine_GPU_cluster::GetPixelGridDim() const
{
	const Vector2i img_size = source_img->noDims;
	return GetGrid2Dim(img_size);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const dim3 gSLICr::engines::seg_engine_GPU_cluster::GetGrid2Dim(Vector2i _size)  const
{
	const dim3 blockSize= GetBlockDim();
	const dim3 gridSize((int)ceil((float)_size.x / (float)blockSize.x), (int)ceil((float)_size.y / (float)blockSize.y));
	return  gridSize;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const dim3 gSLICr::engines::seg_engine_GPU_cluster::GetBlockDim() const
{
	const dim3 blockSize(BLOCK_DIM, BLOCK_DIM);
	return blockSize;
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

	const dim3 blockSize	=	GetBlockDim();
	const dim3 gridSize		=	GetPixelGridDim();

	Kernel_Find_Adjacency_Matrix << <gridSize, blockSize >> >(inimg_ptr, outimg_ptr, img_size,adj_size);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Cvt_Spixel_Similar()
{
	const int*	adj_mat_ptr = adj_img->GetData(MEMORYDEVICE_CUDA);
	float*	similar_mat_ptr =similar_img->GetData(MEMORYDEVICE_CUDA);
	spixel_info* spixel_list_cvt = spixel_map->GetData(MEMORYDEVICE_CUDA);

	const Vector2i map_adj_size = adj_img->noDims;

	const dim3 blockSize	=	GetBlockDim();
	const dim3 gridSize		=	GetGrid2Dim(map_adj_size);

	Kernel_Cvt_Spixel_Similar << <gridSize, blockSize >> > (
		adj_mat_ptr,
		similar_mat_ptr,
		spixel_list_cvt,
		map_adj_size);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Cvt_Spixel_to_LThetaM()
{
	const spixel_info* spixel_list		=	spixel_map->GetData(MEMORYDEVICE_CUDA);
		  spixel_info* spixel_list_cvt	=	m_spixel_map_cvt->GetData(MEMORYDEVICE_CUDA);
	const Vector2i map_size = spixel_map->noDims;
	
	const dim3 blockSize = GetBlockDim();
	const dim3 gridSize =  GetSuperPixelGridDim();

	Kernel_Cvt_Spixel_to_LThetaM << <gridSize, blockSize >> > (spixel_list, spixel_list_cvt, map_size);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void gSLICr::engines::getMatTriangular_Float(float* _mat, const int _wh)
{

	for (size_t ri = 0; ri <_wh; ri++) {
		for (size_t ci = 0; ci < ri; ci++) {
			const int IDX = ri*_wh + ci;
			_mat[IDX] = 0;
		}
	}

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Cvt_Similar_to_Cluster_CPU()
{
	const FloatImage * similar_img= this->Get_Similar_Matrix_Host();
	float* similar_ptr = (float*) similar_img->GetData(MEMORYDEVICE_CPU);
	const int WH = similar_img->noDims.height;
	assert(similar_img->noDims.height == similar_img->noDims.width);

	getMatTriangular_Float(similar_ptr,WH);

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
	this->Cvt_Spixel_to_LThetaM();
	this->Cvt_Spixel_Similar();

	this->Cvt_Similar_to_Cluster_CPU();
	

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
const FloatImage * gSLICr::engines::seg_engine_GPU_cluster::Get_Similar_Matrix_Host()
{
	similar_img->UpdateHostFromDevice();
	return similar_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/