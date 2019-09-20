// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU_cluster.h"
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

			seg_engine_GPU_cluster* slic_seg_engine;

		public:

			// Function to segment in_img
			void Process_Frame(UChar4Image* in_img);

			void Perform_Cluster();

			// Function to get the pointer to the segmented mask image
			const IntImage * Get_Seg_Res();
			const IntImage * Get_Adjacency_Res();

			const FloatImage * Get_Similar_Res();

			// Function to draw segmentation result on out_img
			void Draw_Segmentation_Result(UChar4Image* out_img);

			const gSLICr::engines::seg_engine_GPU_cluster * GetSegEngineGPUCluster() const;



		};
	}
}

