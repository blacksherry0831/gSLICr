// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include "gSLICr_seg_engine.h"

namespace gSLICr
{
	namespace engines
	{
		class seg_engine_GPU : public seg_engine
		{
		private:

			int no_grid_per_center;
			ORUtils::Image<objects::spixel_info>* accum_map;
			IntImage* tmp_idx_img;
		protected:
			Vector2i spixel_map_size;
			Vector2i spixel_accum_map_size;
		protected:
			void Cvt_Img_Space(
				UChar4Image* inimg,
				Float4Image* outimg,
				COLOR_SPACE color_space);

			void Init_Cluster_Centers();
			void Find_Center_Association();
			void Update_Cluster_Center();
			void Enforce_Connectivity();
			void Enforce_Connectivity_Grid3();
			void Enforce_Connectivity_Table();
		public:
			const IntImage*		Get_Idx();
			const IntImage*		Do_Idx_Cpy_Dev_to_Host();

			const SpixelMap*			   Do_Spixel_Map_Cpy_Dev_to_Host();
			const SpixelMap*			   Get_Spixel_Map();
			const ORUtils::Vector2<int>    Get_Spixel_Map_noDims() const;

		public:

			seg_engine_GPU(const objects::settings& in_settings);
			~seg_engine_GPU();

		public:

			void Draw_Segmentation_Result(UChar4Image* out_img);
			void Draw_Segmentation_Result_Ex(
				const UChar4Image *_source_img,
				const IntImage * _labels_img,
				UChar4Image * _out_img);
			
		};
	}
}

