// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include "gSLICr_seg_engine.h"

using namespace std;
using namespace gSLICr;
using namespace gSLICr::objects;
using namespace gSLICr::engines;
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
seg_engine::seg_engine(const objects::settings& in_settings)
{
	gSLICr_settings = in_settings;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
seg_engine::~seg_engine()
{
	if (source_img != NULL) delete source_img;
	if (cvt_img != NULL) delete cvt_img;
	if (idx_img != NULL) delete idx_img;
	if (spixel_map != NULL) delete spixel_map;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void seg_engine::Perform_Segmentation(UChar4Image* in_img)
{
	source_img->SetFrom(in_img, ORUtils::MemoryBlock<Vector4u>::CPU_TO_CUDA);
	Perform_Segmentation_Base();
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void seg_engine::Perform_Segmentation(const char* _data,const size_t _size)
{
	source_img->SetFrom(_data,_size, ORUtils::MemoryBlock<Vector4u>::CPU_TO_CUDA);
	Perform_Segmentation_Base();
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void gSLICr::engines::seg_engine::cudaThreadSync()
{
	cudaThreadSynchronize();
}
/*-------------------------------------------------------------------------*/
/**
*With GTX Titan X, 3.4ms@640x480, 12ms@1280x960, 20ms@1920x1080 image
*/
/*-------------------------------------------------------------------------*/
void seg_engine::Perform_Segmentation_Base()
{
	Cvt_Img_Space(source_img, cvt_img, gSLICr_settings.color_space);

	Init_Cluster_Centers();
	Find_Center_Association();

	for (int i = 0; i < gSLICr_settings.no_iters; i++)
	{

		Update_Cluster_Center();
		Find_Center_Association();
	}

	for (size_t i = 0; i < 1; i++)
	{
		if (gSLICr_settings.do_enforce_connectivity) Enforce_Connectivity();
	}
	
	cudaThreadSync();

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/


