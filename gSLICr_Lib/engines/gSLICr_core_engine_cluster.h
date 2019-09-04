// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_cluster.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
namespace gSLICr
{
	namespace engines
	{
		class core_engine_cluster 
		{

		public:

			core_engine_cluster(const objects::settings& in_settings);
			~core_engine_cluster();

		protected:

			seg_engine_cluster* slic_seg_engine;

		public:

			// Function to segment in_img
			void Process_Frame(UChar4Image* in_img);

			// Function to get the pointer to the segmented mask image
			const IntImage * Get_Seg_Res();

			// Function to draw segmentation result on out_img
			void Draw_Segmentation_Result(UChar4Image* out_img);

		};
	}
}

