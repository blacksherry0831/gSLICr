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
			FloatImage *similar_img;
			SpixelMap* m_spixel_map_cvt;
		public:
			const dim3 GetSuperPixelGridDim() const;
			const dim3 GetPixelGridDim() const;
			const dim3 GetGrid2Dim(Vector2i _size) const;
			const dim3 GetBlockDim() const;
		public:
			virtual void Find_Adjacency_Matrix_E();
			virtual void Cvt_Spixel_Similar();
			virtual void Cvt_Spixel_to_LThetaM();

			virtual void Cvt_Similar_to_Cluster_CPU();

			void Perform_Cluster();
			
			int SpixelNum() const;
			
			const IntImage* Get_Adjacency_Matrix();

			const FloatImage * Get_Similar_Matrix_Host();

		};
		static void getMatTriangular_Float(float * _mat, const int _wh);
	}
}

