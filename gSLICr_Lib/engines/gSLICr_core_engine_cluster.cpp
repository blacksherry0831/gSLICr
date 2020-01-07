#include "gSLICr_core_engine_cluster.h"
/*----------------------------------------------------------------*/
#include <fstream>
/*----------------------------------------------------------------*/
#include "gSLICr_core_engine.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*----------------------------------------------------------------*/
using namespace gSLICr;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
gSLICr::engines::core_engine_cluster::core_engine_cluster(const objects::settings& in_settings)
{
	slic_seg_engine = new seg_engine_GPU_cluster(in_settings);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
gSLICr::engines::core_engine_cluster::~core_engine_cluster()
{
	delete slic_seg_engine;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::Process_Frame(UChar4Image * in_img)
{
	slic_seg_engine->Perform_Segmentation(in_img);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::Process_Frame(
	const char* _data,
	const size_t _size)
{
	slic_seg_engine->Perform_Segmentation(_data,_size);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void  gSLICr::engines::core_engine_cluster::Perform_Cluster()
{
	slic_seg_engine->Perform_Cluster();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::cudaThreadSync()
{
	slic_seg_engine->cudaThreadSync();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::MEM_GPU_to_CPU()
{
	slic_seg_engine->Do_Idx_Cpy_Dev_to_Host();

	slic_seg_engine->Do_Adjacency_Matrix_Cpy_Dev_to_Host();
	slic_seg_engine->Do_Similar_Matrix_Cpy_Dev_to_Host();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::MEM_CPU_to_GPU_Cluster_Idx()
{
	slic_seg_engine->Do_Cluster_Idx_Seg_Matrix_Cpy_Host_to_Dev();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::MEM_GPU_to_CPU_Spixel_Map()
{
	slic_seg_engine->Do_Spixel_Map_Cpy_Dev_to_Host();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::MEM_GPU_to_CPU_Spixel_Map_Cvt()
{
	slic_seg_engine->Do_Spixel_Map_Cvt_Spy_Dev_to_Host();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void  gSLICr::engines::core_engine_cluster::Perform_Cluster_CPU()
{
	slic_seg_engine->Perform_Cluster_CPU();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const IntImage * gSLICr::engines::core_engine_cluster::Get_Seg_Res()
{
	return slic_seg_engine->Get_Seg_Mask();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::Draw_Segmentation_Result(UChar4Image * out_img)
{
	slic_seg_engine->Draw_Segmentation_Result(out_img);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::Draw_Segmentation_Cluster_Result(UChar4Image * out_img)
{
	slic_seg_engine->Draw_Segmentation_Cluster_Result(out_img);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const gSLICr::engines::seg_engine_GPU_cluster* gSLICr::engines::core_engine_cluster::GetSegEngineGPUCluster() const
{
	return slic_seg_engine;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const IntImage * gSLICr::engines::core_engine_cluster::Get_Adjacency()
{
	return slic_seg_engine->Get_Adjacency_Matrix();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const FloatImage * gSLICr::engines::core_engine_cluster::Get_Similar()
{
	return slic_seg_engine->Get_Similar_Matrix();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const FloatImage * gSLICr::engines::core_engine_cluster::Do_Similar_Res_Dev_to_Host()
{
	return slic_seg_engine->Do_Similar_Matrix_Cpy_Dev_to_Host();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const SpixelMap * gSLICr::engines::core_engine_cluster::Get_Spixel_Map_Cvt()
{
	return slic_seg_engine->Get_Spixel_Map_Cvt();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const SpixelMap * gSLICr::engines::core_engine_cluster::Get_Spixel_Map()
{
	return nullptr;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const std::vector<gSLICr::objects::spixel_info> gSLICr::engines::core_engine_cluster::Cvt_SpixelMap_to_Vector(const SpixelMap * _spixelMap)
{
	std::vector<gSLICr::objects::spixel_info> spixel_info_t;
	
	const gSLICr::objects::spixel_info* spixel_list_t = _spixelMap->GetData(MEMORYDEVICE_CPU);

	const int dimX = _spixelMap->noDims.x;
	const int dimY = _spixelMap->noDims.y;

	for (int xi = 0; xi < dimX; xi++) {
		for (int yi = 0; yi < dimY; yi++) {
			const int IDX = xi + yi*dimX;
			spixel_info_t.push_back(spixel_list_t[IDX]);
		}
	}

	return spixel_info_t;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const std::vector<gSLICr::objects::spixel_info>  gSLICr::engines::core_engine_cluster::Get_Spixel_Map_Cvt_Vector()
{	
	SpixelMap * spixelMap_t=(SpixelMap *)slic_seg_engine->Get_Spixel_Map_Cvt();
	std::vector<gSLICr::objects::spixel_info> spixel_info_t = Cvt_SpixelMap_to_Vector(spixelMap_t);
	return spixel_info_t;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const std::vector<gSLICr::objects::spixel_info>  gSLICr::engines::core_engine_cluster::Get_Spixel_Map_Vector()
{
	SpixelMap * spixelMap_t = (SpixelMap *)(slic_seg_engine->Get_Spixel_Map());
	std::vector<gSLICr::objects::spixel_info> spixel_info_t = Cvt_SpixelMap_to_Vector(spixelMap_t);
	return spixel_info_t;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const IntImage* gSLICr::engines::core_engine_cluster::Get_Cluster_Idx_Seg()
{
	return slic_seg_engine->Get_Cluster_Idx_Seg_Matrix();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const int gSLICr::engines::core_engine_cluster::SpixelNum() const
{
	return slic_seg_engine->SpixelNum();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/