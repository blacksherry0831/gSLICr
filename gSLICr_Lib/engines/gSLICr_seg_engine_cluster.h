// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
/*----------------------------------------------------------------*/
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_settings.h"
#include "../objects/gSLICr_spixel_info.h"
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
namespace gSLICr
{
	namespace engines
	{
		class seg_engine_cluster :public seg_engine
		{
		protected:
			IntImage *link_img;
		public:

			seg_engine_cluster(const objects::settings& in_settings );
			~seg_engine_cluster();


		};
	}
}

