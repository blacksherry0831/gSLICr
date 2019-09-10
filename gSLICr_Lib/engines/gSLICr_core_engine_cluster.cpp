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
void  gSLICr::engines::core_engine_cluster::Perform_Cluster()
{
	slic_seg_engine->Perform_Cluster();
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
const gSLICr::engines::seg_engine_GPU_cluster* gSLICr::engines::core_engine_cluster::GetSegEngineGPUCluster() const
{
	return slic_seg_engine;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const IntImage * gSLICr::engines::core_engine_cluster::Get_Adjacency_Res()
{
	return slic_seg_engine->Get_Adjacency_Matrix();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

