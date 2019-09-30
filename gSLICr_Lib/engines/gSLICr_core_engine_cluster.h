// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU_cluster.h"
/*----------------------------------------------------------------*/
#include <vector>
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

			void MEM_GPU_to_CPU();
			void MEM_CPU_to_GPU_Cluster_Idx();

			void MEM_GPU_to_CPU_Spixel_Map();
			
			void MEM_GPU_to_CPU_Spixel_Map_Cvt();

			void Perform_Cluster_CPU();

			// Function to get the pointer to the segmented mask image
			const IntImage*		Get_Seg_Res();

			const IntImage*		Get_Adjacency();
			const FloatImage*	Get_Similar();
			const IntImage*		Get_Cluster_Idx_Seg();
			
			const FloatImage*	Do_Similar_Res_Dev_to_Host();

			const SpixelMap*    Get_Spixel_Map_Cvt();
			const SpixelMap*    Get_Spixel_Map();
	
			static const std::vector<gSLICr::objects::spixel_info> Cvt_SpixelMap_to_Vector(const SpixelMap * _spixelMap);
		
			const std::vector<gSLICr::objects::spixel_info> Get_Spixel_Map_Cvt_Vector();
			const std::vector<gSLICr::objects::spixel_info> Get_Spixel_Map_Vector();
		
					
			// Function to draw segmentation result on out_img
			void Draw_Segmentation_Result(UChar4Image* out_img);

			void Draw_Segmentation_Cluster_Result(UChar4Image* out_img);

			const gSLICr::engines::seg_engine_GPU_cluster * GetSegEngineGPUCluster() const;



		};
	}
}

