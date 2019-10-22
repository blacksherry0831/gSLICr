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
#include <vector>
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
	
	cvt_spixel_to_l_theta_m_raw(
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
	const  gSLICr::Vector2i _adj_size,
	const float _L_Color_th,
	const float _M_Color_th,
	const float _Theta_Color_th,
	const float _L_Gray_th,
	const float _M_Gray_th,
	const float _Theta_Gray_th,
	const float _M_Gray_Color_th)
{
	const int x = threadIdx.x + blockIdx.x * blockDim.x, y = threadIdx.y + blockIdx.y * blockDim.y;
	if (x > _adj_size.x - 1 || y > _adj_size.y - 1) return;

	cvt_spixel_similar(
				_adj_img,
				_similar_img,
				_spixel_list,
				_adj_size,
				x,
				y,
				_L_Color_th,
				_M_Color_th,
				_Theta_Color_th,
				_L_Gray_th,
				_M_Gray_th,
				_Theta_Gray_th,
				_M_Gray_Color_th);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
seg_engine_GPU_cluster::seg_engine_GPU_cluster(const objects::settings& in_settings) : seg_engine_GPU(in_settings)
{

	this->malloc_Spixel_Mem();

	cluster_idx_img = new IntImage(gSLICr_settings.img_size, true, true);
	m_spixel_map_cvt = new SpixelMap(spixel_map_size, true, true);
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
seg_engine_GPU_cluster::~seg_engine_GPU_cluster()
{
	this->free_Spixel_Mem();

	if (cluster_idx_img  != NULL)				delete cluster_idx_img;
	if (m_spixel_map_cvt != NULL)				delete m_spixel_map_cvt;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::malloc_Spixel_Mem()
{
	const int AdjDim = this->SpixelNum();
	const Vector2i link_size_t(AdjDim, AdjDim);
	const Vector2i map_size_t(AdjDim, 1);

	adj_img = new IntImage(link_size_t, true, true);
	similar_img = new FloatImage(link_size_t, true, true);
	cluster_map_img = new IntImage(map_size_t, true, true);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::free_Spixel_Mem()
{
	if (adj_img != NULL)				delete adj_img;
	if (similar_img != NULL)			delete similar_img;
	if (cluster_map_img != NULL)		delete cluster_map_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::SetClusterLThetaM_Threshold(
	const float _L_Color_th,
	const float _M_Color_th,
	const float _Theta_Color_th,
	const float _L_Gray_th,
	const float _M_Gray_th,
	const float _Theta_Gray_th,
	const float _M_Gray_Color_th)
{
	mClusterL_Color_Threshold= _L_Color_th;
	mClusterM_Color_Threshold= _M_Color_th;
	mClusterTheta_Color_Threshold= _Theta_Color_th;

	mClusterL_Gray_Threshold= _L_Gray_th;
	mClusterM_Gray_Threshold= _M_Gray_th;
	mClusterTheta_Gray_Threshold= _Theta_Gray_th;

	mClusterM_Gray_Color_Threshold= _M_Gray_Color_th;
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
	spixel_info* spixel_list_cvt = m_spixel_map_cvt->GetData(MEMORYDEVICE_CUDA);

	const Vector2i map_adj_size = adj_img->noDims;

	const dim3 blockSize	=	GetBlockDim();
	const dim3 gridSize		=	GetGrid2Dim(map_adj_size);

	Kernel_Cvt_Spixel_Similar << <gridSize, blockSize >> > (
		adj_mat_ptr,
		similar_mat_ptr,
		spixel_list_cvt,
		map_adj_size,
		mClusterL_Color_Threshold,
		mClusterM_Color_Threshold,
		mClusterTheta_Color_Threshold,
		mClusterL_Gray_Threshold,
		mClusterM_Gray_Threshold,
		mClusterTheta_Gray_Threshold,
		mClusterM_Gray_Color_Threshold);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Cvt_Spixel_to_LThetaM()
{

	assert(gSLICr_settings.color_space == COLOR_SPACE::CIELAB);

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
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool gSLICr::engines::RemoveLine_Float(
	float* _mat,
	const int _wh,
	const int _li)
{

	for (size_t ci = 0; ci < _wh; ci++) {
		const int IDX_I = _li*_wh + ci;
		const int I_v = _mat[IDX_I];
		_mat[IDX_I] = 0;
	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool gSLICr::engines::MergeNeighbor_Float(
	float * _mat,
	const int _wh,
	const int _i,
	const int _j)
{

	for (size_t ci = 0; ci < _wh; ci++) {
		const int IDX_I = _i* _wh + ci;
		const int IDX_J = _j* _wh + ci;
		const int I_v = _mat[IDX_I];
		const int J_v = _mat[IDX_J];
		const int IJ_v = I_v | J_v;
		_mat[IDX_J] = IJ_v;
	}

	return true;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void gSLICr::engines::getMatCluster_Float(float * _mat, const int _wh)
{
	for (int ci = _wh - 1; ci >= 0; ci--) {

		std::vector<int> sameClass;

		for (int ri = 0; ri <_wh; ri++) {
			const int IDX = ci + ri*_wh;
			const int W = _mat[IDX];
			if (W) {
				sameClass.push_back(ri);
			}
		}

		if (sameClass.size() > 0) {
			const int ri_min = sameClass.at(0);
			for (int ri = 1; ri < sameClass.size(); ri++) {
				const int ri_current = sameClass.at(ri);
				MergeNeighbor_Float(_mat, _wh, ri_current, ri_min);
				RemoveLine_Float(_mat, _wh, ri_current);
			}
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
	const FloatImage * similar_img_t= this->Get_Similar_Matrix();
	float* similar_ptr = (float*) similar_img_t->GetData(MEMORYDEVICE_CPU);
	const int WH = similar_img_t->noDims.height;
	assert(similar_img_t->noDims.height == similar_img_t->noDims.width);

	getMatTriangular_Float(similar_ptr,WH);

	getMatCluster_Float(similar_ptr, WH);

	int * map=cluster_map_img->GetData(MEMORYDEVICE_CPU);
	
	getMapCluster_Idx(map,similar_ptr,WH);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Cvt_Labels_to_ClusterLabels_CPU()
{
	const FloatImage * similar_img_t = this->Get_Similar_Matrix();
	const IntImage *labels_idx= Get_Idx();
	const int WIDTH  = labels_idx->noDims.width;
	const int HEIGHT = labels_idx->noDims.height;
	const int WH = similar_img_t->noDims.width;

	const int*  map_ptr = cluster_map_img->GetData(MEMORYDEVICE_CPU);
	const int*  labels_idx_ptr =(int*) labels_idx->GetData(MEMORYDEVICE_CPU);
	int*  cluster_idx_ptr = (int*)cluster_idx_img->GetData(MEMORYDEVICE_CPU);


	for (int ci = 0; ci <WIDTH; ci++){
		for (int ri = 0; ri < HEIGHT; ri++){
			const int IDX = ci + ri*WIDTH;
			const int LABEL_OLD = labels_idx_ptr[IDX];
			const int LABEL_NEW = map_ptr[LABEL_OLD];
			cluster_idx_ptr[IDX] = LABEL_NEW;
		}
	}
	
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::getMapCluster_Idx(int* _map, const float * _mat, const int _wh)
{

	for (int ri = 0; ri < _wh; ri++){

		for (int ci = 0; ci < _wh; ci++){

			const int IDX = ci + ri*_wh;

			const int N = _mat[IDX];

			if (N){
				_map[ci] = ri;
			}


		}

	}
	
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

	cudaThreadSynchronize();

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Perform_Cluster_CPU()
{
	this->Cvt_Similar_to_Cluster_CPU();

	this->Cvt_Labels_to_ClusterLabels_CPU();
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
const IntImage * gSLICr::engines::seg_engine_GPU_cluster::Do_Adjacency_Matrix_Cpy_Dev_to_Host()
{
	adj_img->UpdateHostFromDevice();
	return adj_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const IntImage * gSLICr::engines::seg_engine_GPU_cluster::Get_Adjacency_Matrix()
{
	return adj_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const FloatImage * gSLICr::engines::seg_engine_GPU_cluster::Do_Similar_Matrix_Cpy_Dev_to_Host()
{
	similar_img->UpdateHostFromDevice();
	return similar_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const FloatImage * gSLICr::engines::seg_engine_GPU_cluster::Get_Similar_Matrix()
{
	return similar_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const IntImage * gSLICr::engines::seg_engine_GPU_cluster::Get_Cluster_Idx_Seg_Matrix()
{
	return  cluster_idx_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const IntImage * gSLICr::engines::seg_engine_GPU_cluster::Do_Cluster_Idx_Seg_Matrix_Cpy_Host_to_Dev()
{
	cluster_idx_img->UpdateDeviceFromHost();
	return cluster_idx_img;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const SpixelMap * gSLICr::engines::seg_engine_GPU_cluster::Do_Spixel_Map_Cvt_Spy_Dev_to_Host()
{
	m_spixel_map_cvt->UpdateHostFromDevice();
	return m_spixel_map_cvt;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
const SpixelMap * gSLICr::engines::seg_engine_GPU_cluster::Get_Spixel_Map_Cvt()
{
	return m_spixel_map_cvt;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine_GPU_cluster::Draw_Segmentation_Cluster_Result(UChar4Image * _out_img)
{
	this->Draw_Segmentation_Result_Ex(source_img, cluster_idx_img,_out_img);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/