// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*----------------------------------------------------------------*/
#pragma once
/*----------------------------------------------------------------*/
#include "gSLICr_core_engine.h"
#include "gSLICr_core_engine_cluster.h"
#include <fstream>
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_cluster.h"
/*----------------------------------------------------------------*/
using namespace gSLICr;
using namespace std;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
gSLICr::engines::core_engine_cluster::core_engine_cluster(const objects::settings& in_settings)
{

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
gSLICr::engines::core_engine_cluster::~core_engine_cluster()
{
		
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::Process_Frame(UChar4Image * in_img)
{
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
const IntImage * gSLICr::engines::core_engine_cluster::Get_Seg_Res()
{
	return nullptr;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void gSLICr::engines::core_engine_cluster::Draw_Segmentation_Result(UChar4Image * out_img)
{
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/



