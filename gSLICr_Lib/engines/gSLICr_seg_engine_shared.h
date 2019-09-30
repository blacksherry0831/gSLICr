// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include "../gSLICr_defines.h"
#include "../objects/gSLICr_spixel_info.h"

#include "gSLICr_seg_engine_map.h"
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void rgb2xyz(
		const gSLICr::Vector4u& pix_in,
		gSLICr::Vector4f& pix_out)
{
	const float _b = (float)pix_in.b * 0.0039216f;
	const float _g = (float)pix_in.g * 0.0039216f;
	const float _r = (float)pix_in.r * 0.0039216f;

	pix_out.x = _r*0.412453f + _g*0.357580f + _b*0.180423f;
	pix_out.y = _r*0.212671f + _g*0.715160f + _b*0.072169f;
	pix_out.z = _r*0.019334f + _g*0.119193f + _b*0.950227f;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void rgb2CIELab(
	const gSLICr::Vector4u& pix_in,
	gSLICr::Vector4f& pix_out)
{
	const float _b = (float)pix_in.b * 0.0039216f;
	const float _g = (float)pix_in.g * 0.0039216f;
	const float _r = (float)pix_in.r * 0.0039216f;

	const float x = _r*0.412453f + _g*0.357580f + _b*0.180423f;
	const float y = _r*0.212671f + _g*0.715160f + _b*0.072169f;
	const float z = _r*0.019334f + _g*0.119193f + _b*0.950227f;

	const float epsilon = 0.008856f;	//actual CIE standard
	const float kappa = 903.3f;		//actual CIE standard

	const float Xr = 0.950456f;	//reference white
	const float Yr = 1.0f;		//reference white
	const float Zr = 1.088754f;	//reference white

	const float xr = x / Xr;
	const float yr = y / Yr;
	const float zr = z / Zr;

	float fx, fy, fz;
	if (xr > epsilon)	fx = pow(xr, 1.0f / 3.0f);
	else				fx = (kappa*xr + 16.0f) / 116.0f;
	if (yr > epsilon)	fy = pow(yr, 1.0f / 3.0f);
	else				fy = (kappa*yr + 16.0f) / 116.0f;
	if (zr > epsilon)	fz = pow(zr, 1.0f / 3.0f);
	else				fz = (kappa*zr + 16.0f) / 116.0f;

	pix_out.L = 116.0f*fy - 16.0f;
	pix_out.A = 500.0f*(fx - fy);
	pix_out.B = 200.0f*(fy - fz);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void cvt_img_space_shared(
	const gSLICr::Vector4u* inimg,
	gSLICr::Vector4f* outimg,
	const gSLICr::Vector2i& img_size,
	const int x,
	const int y, 
	const gSLICr::COLOR_SPACE& color_space)
{
	const int idx = y * img_size.x + x;

	switch (color_space)
	{
	case gSLICr::RGB:
		outimg[idx].b = inimg[idx].b;
		outimg[idx].g = inimg[idx].g;
		outimg[idx].r = inimg[idx].r;
		break;
	case gSLICr::XYZ:
		rgb2xyz(inimg[idx], outimg[idx]);
		break;
	case gSLICr::CIELAB:
		rgb2CIELab(inimg[idx], outimg[idx]);
		break;
	}
}
/*-------------------------------------------------------------------------*/
/**
*@param inimg			Í¼Ïñ¾ØÕó
*@param out_spixel		³¬ÏñËØÊôÐÔ
*@param map_size		³¬ÏñËØ¶þÎ¬×ø±ê
*@param img_size		Í¼Ïñ³ß´ç
*@param spixel_size		³¬ÏñËØ³¤¿í(ÏñËØ)
*@param x				³¬ÏñËØ¶þÎ¬×ø±ê£¬XÖá×ø±ê
*@param y				³¬ÏñËØ¶þÎ¬×ø±ê£¬YÖá×ø±ê
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void init_cluster_centers_shared(
	const gSLICr::Vector4f* inimg,
	gSLICr::objects::spixel_info* out_spixel,
	const gSLICr::Vector2i map_size,
	const gSLICr::Vector2i img_size,
	const int spixel_size,
	const int x,
	const int y)
{
	const int cluster_idx = y * map_size.x + x;

	int img_x = SuperPixelIdx_2_ImgCoord_Center(x, spixel_size);
	int img_y = SuperPixelIdx_2_ImgCoord_Center(y, spixel_size);

	img_x = img_x >= img_size.x ? (x * spixel_size + img_size.x) / 2 : img_x;
	img_y = img_y >= img_size.y ? (y * spixel_size + img_size.y) / 2 : img_y;

	// TODO: go one step towards gradients direction

	out_spixel[cluster_idx].id = cluster_idx;
	out_spixel[cluster_idx].center = gSLICr::Vector2f((float)img_x, (float)img_y);
	out_spixel[cluster_idx].color_info = inimg[img_y*img_size.x + img_x];
	
	out_spixel[cluster_idx].no_pixels = 0;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline float compute_slic_distance(
	const gSLICr::Vector4f& pix,
	const int x,
	const int y,
	const gSLICr::objects::spixel_info& center_info,
	const float weight,
	const float normalizer_xy,
	const float normalizer_color)
{
	const float dcolor =
				(pix.x - center_info.color_info.x)*(pix.x - center_info.color_info.x)
			+	(pix.y - center_info.color_info.y)*(pix.y - center_info.color_info.y)
			+	(pix.z - center_info.color_info.z)*(pix.z - center_info.color_info.z);

	const float dxy =
				(x - center_info.center.x) * (x - center_info.center.x)
			  + (y - center_info.center.y) * (y - center_info.center.y);


	const float retval = dcolor * normalizer_color + weight * dxy * normalizer_xy;
	return sqrtf(retval);
}
/*-------------------------------------------------------------------------*/
/**
*
*@param	[in]	inimg				Í¼ÏñÊý¾Ý
*@param	[in]	in_spixel_map		³¬ÏñËØÊôÐÔ
*@param	[out]	out_idx_img			±êÇ©¾ØÕó
*@param	[in]	map_size			³¬ÏñËØ³ß´ç
*@param	[in]	img_size			Í¼Ïñ³ß´ç
*@param	[in]	spixel_size			³¬ÏñËØ³¤¿í(ÏñËØ)	
*@param	[in]	weight				×ø±ê¾àÀëÈ¨ÖØ
*@param	[in]	x					Í¼Ïñ×ø±êX
*@param	[in]	y					Í¼Ïñ×ø±êY
*@param	[in]	max_xy_dist			×ø±ê×î´ó¾àÀë
*@param	[in]	max_color_dist		É«²Ê×î´ó¾àÀë
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void find_center_association_shared(
	const gSLICr::Vector4f* inimg,
	const gSLICr::objects::spixel_info* in_spixel_map,
	int* out_idx_img,
	const gSLICr::Vector2i map_size,
	const gSLICr::Vector2i img_size,
	const int spixel_size,
	const float weight,
	const int x,
	const int y,
	const float max_xy_dist,
	const float max_color_dist)
{
	const int idx_img = y * img_size.x + x;

	const int ctr_x = x / spixel_size;
	const int ctr_y = y / spixel_size;

	int minidx = -1;
	const float DIST_MAX= 999999.9999f;
	float dist = DIST_MAX;

	// search 3x3 neighborhood
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
	{
		const int ctr_x_check = ctr_x + j;
		const int ctr_y_check = ctr_y + i;

		if (ctr_x_check >= 0 && 
			ctr_y_check >= 0 && 
			ctr_x_check < map_size.x && 
			ctr_y_check < map_size.y)
		{
			const int ctr_idx = ctr_y_check*map_size.x + ctr_x_check;

			const float cdist = compute_slic_distance(
														inimg[idx_img],
														x,
														y,
														in_spixel_map[ctr_idx],
														weight,
														max_xy_dist,
														max_color_dist);

			if (cdist < dist)
			{
				dist = cdist;
				minidx = in_spixel_map[ctr_idx].id;
			}

		}
	}

	if (minidx >= 0)
		out_idx_img[idx_img] = minidx;
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void draw_superpixel_boundry_shared(
	const int* idx_img,
	const gSLICr::Vector4u* sourceimg,
	gSLICr::Vector4u* outimg,
	const gSLICr::Vector2i img_size,
	const int x,
	const int y)
{
	const int idx = y * img_size.x + x;

	if (idx_img[idx] != idx_img[idx + 1]
	 || idx_img[idx] != idx_img[idx - 1]
	 || idx_img[idx] != idx_img[(y - 1)*img_size.x + x]
	 || idx_img[idx] != idx_img[(y + 1)*img_size.x + x])
	{
		outimg[idx] = gSLICr::Vector4u(255,0,0,0);
	}
	else
	{
		outimg[idx] = sourceimg[idx];
	}
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void finalize_reduction_result_shared(
	const gSLICr::objects::spixel_info* accum_map,
	gSLICr::objects::spixel_info* spixel_list,
	const gSLICr::Vector2i map_size,
	const int no_blocks_per_spixel,
	const int x,
	const int y)
{
	const int spixel_idx = y * map_size.x + x;

	spixel_list[spixel_idx].center = gSLICr::Vector2f(0, 0);
	spixel_list[spixel_idx].color_info = gSLICr::Vector4f(0, 0, 0, 0);
	spixel_list[spixel_idx].no_pixels = 0;

	for (int i = 0; i < no_blocks_per_spixel; i++)
	{
		const int accum_list_idx = GetAccumMapIdx(spixel_idx, no_blocks_per_spixel,i);

		spixel_list[spixel_idx].center += accum_map[accum_list_idx].center;
		spixel_list[spixel_idx].color_info += accum_map[accum_list_idx].color_info;
		spixel_list[spixel_idx].no_pixels += accum_map[accum_list_idx].no_pixels;
	}

	if (spixel_list[spixel_idx].no_pixels != 0)
	{
		spixel_list[spixel_idx].center /= (float)spixel_list[spixel_idx].no_pixels;
		spixel_list[spixel_idx].color_info /= (float)spixel_list[spixel_idx].no_pixels;
	}

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
_CPU_AND_GPU_CODE_ inline void supress_local_lable(
	const int* in_idx_img,
	int* out_idx_img,
	const gSLICr::Vector2i img_size,
	const int x,
	const int y)
{
	const int IDX = y*img_size.x + x;
	const int clable = in_idx_img[IDX];

	// don't suppress boundary
	if (x <= 1 || y <= 1 || x >= img_size.x - 2 || y >= img_size.y - 2)
	{ 
		out_idx_img[IDX] = clable;
		return; 
	}

	int diff_count = 0;
	int diff_lable = -1;

	for (int j = -2; j <= 2; j++) for (int i = -2; i <= 2; i++)
	{
		int nlable = in_idx_img[(y + j)*img_size.x + (x + i)];
		if (nlable!=clable)
		{
			diff_lable = nlable;
			diff_count++;
		}
	}

	if (diff_count>=16)
		out_idx_img[IDX] = diff_lable;
	else
		out_idx_img[IDX] = clable;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/