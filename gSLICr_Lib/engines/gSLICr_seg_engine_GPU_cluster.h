// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
/*----------------------------------------------------------------*/
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_settings.h"
#include "../objects/gSLICr_spixel_info.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_GPU.h"
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
		class seg_engine_GPU_cluster :public seg_engine_GPU
		{
		public:
			seg_engine_GPU_cluster(const objects::settings& in_settings);
			~seg_engine_GPU_cluster();

		private:
			void  malloc_Spixel_Mem();
			void  free_Spixel_Mem();
		private:
			float mClusterL_Color_Threshold;
			float mClusterM_Color_Threshold;
			float mClusterTheta_Color_Threshold;

			float mClusterL_Gray_Threshold;
			float mClusterM_Gray_Threshold;
			float mClusterTheta_Gray_Threshold;

			float mClusterM_Gray_Color_Threshold;
		public:
			void SetClusterLThetaM_Threshold(
				const float _L_Color_th,
				const float _M_Color_th,
				const float _Theta_Color_th,
				const float _L_Gray_th,
				const float _M_Gray_th,
				const float _Theta_Gray_th,
				const float _M_Gray_Color_th);
		protected:
			IntImage* cluster_map_img;
			IntImage* adj_img;
			IntImage* cluster_idx_img;
		protected:
			FloatImage* similar_img;
			SpixelMap*  m_spixel_map_cvt;
		public:
			const dim3 GetSuperPixelGridDim() const;
			const dim3 GetPixelGridDim() const;
			const dim3 GetGrid2Dim(Vector2i _size) const;
			const dim3 GetBlockDim() const;
		public:
			virtual void Find_Adjacency_Matrix_E_UpTri();
			virtual void Find_Adjacency_Matrix_E();
			virtual void Cvt_Spixel_Similar();
			virtual void Cvt_Spixel_to_LThetaM();

			virtual void Cvt_Similar_to_Cluster_CPU();
			virtual void Cvt_Labels_to_ClusterLabels_CPU();
		public:
			void Perform_Cluster();
			void Perform_Cluster_CPU();
		public:
			int SpixelNum() const;
		public:
			const IntImage*		Do_Adjacency_Matrix_Cpy_Dev_to_Host();
			const IntImage*		Get_Adjacency_Matrix();

			const FloatImage*	Do_Similar_Matrix_Cpy_Dev_to_Host();
			const FloatImage*	Get_Similar_Matrix();

			const IntImage*		Get_Cluster_Idx_Seg_Matrix();
			
			const IntImage*		Do_Cluster_Idx_Seg_Matrix_Cpy_Host_to_Dev();

			const SpixelMap*	Do_Spixel_Map_Cvt_Spy_Dev_to_Host();

			const SpixelMap*    Get_Spixel_Map_Cvt();

			void Draw_Segmentation_Cluster_Result(UChar4Image* _out_img);


		};

		static void getMatTriangular_Float(float * _mat, const int _wh);

		static void MergeNeighbor_Line(
			const int * _DATA,
			const int _SZ,
			float * _mat,
			const int _wh);

		static void getMatCluster_Float(float * _mat, const int _wh);
		static void getMapCluster_Idx(
			int* _map,
			const float * _mat,
			const int _wh);
		
		bool CompareArray(
			const std::vector<int>& _v,
			const int * _DATA,
			const int _SZ);

		bool MergeNeighbor_RemoveAnother(float * _mat, const int _wh, const int _i, const int _j);

		void getSameClass(std::vector<int>& sameClass,const int _ci,const float * _mat, const int _wh);

		void getSameClass(
			int * _sameClass,
			int * _sameNum,
			const int _ci,
			const float * _mat,
			const int _wh);
		
	}
}