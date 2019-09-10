// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
/*----------------------------------------------------------------*/
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_settings.h"
#include "../objects/gSLICr_spixel_info.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
namespace gSLICr
{
	namespace engines
	{
		class seg_engine_GPU_cluster :public seg_engine_GPU
		{
		public:
			seg_engine_GPU_cluster(const objects::settings& in_settings);
			~seg_engine_GPU_cluster();
		protected:
			IntImage *adj_img;
		public:
			virtual void Find_Adjacency_Matrix_E();

			void Perform_Cluster();
			
			int SpixelNum() const;
			
			const IntImage* Get_Adjacency_Matrix();

		};
	}
}

