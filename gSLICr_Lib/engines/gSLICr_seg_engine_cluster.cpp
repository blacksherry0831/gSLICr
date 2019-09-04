// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr
/*----------------------------------------------------------------*/
#include "gSLICr_seg_engine_cluster.h"
/*----------------------------------------------------------------*/
using namespace std;
using namespace gSLICr;
using namespace gSLICr::objects;
using namespace gSLICr::engines;
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
seg_engine_cluster::seg_engine_cluster(const objects::settings& in_settings) : seg_engine(in_settings)
{
	const Vector2i link_size_t(in_settings.no_segs, in_settings.no_segs);
	
	link_img = new IntImage(link_size_t, true, true);

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
seg_engine_cluster::~seg_engine_cluster()
{
	if (link_img != NULL) delete link_img;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/





