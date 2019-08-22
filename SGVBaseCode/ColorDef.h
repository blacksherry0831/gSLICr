#pragma once
#ifndef _COLOR_DEF_H_
#define _COLOR_DEF_H_
/*----------------------------------------------------------------------*/
/**
*颜色定义 RGB 三通道
*/
/*----------------------------------------------------------------------*/
#define WhiteColorRGB  (0x00ffffff)
#define BlackColorRGB  (0x00000000)
/*----------------------------------------------------------------------*/
/**
*颜色定义RGBA 四通道
*/
/*----------------------------------------------------------------------*/
#define BlackColorPNG (0xff000000)
#define WhiteColorPNG (0xffffffff)
#define SkyColorPNG      (0xD04B4587)
#define VerticalColorPNG (0xE0ff0000)
#define GroundColorPNG   (0xF04D9D7B)
#define UnknowColorPNG      (0xff000000)
#define VerticalTreeColorPNG (0xff00ff00)
#define VerticalBuildingColorPNG (0xffff0000)
/*----------------------------------------------------------------------*/
/**
*颜色定义--OpenCv cvScalar
*/
/*----------------------------------------------------------------------*/
#define BlackColorPNGCv     cvScalar(0x00,0x00,0x00,0xff)
#define WhiteColorPNGCv	    cvScalar(0xff,0xff,0xff,0xff)
#define SkyColorPNGCv       cvScalar(0x87,0x45,0x4B,0xD0)
#define VerticalColorPNGCv  cvScalar(0x00,0x00,0xff,0xE0)
#define GroundColorPNGCv    cvScalar(0x7B,0x9D,0x4D,0xF0)
/*----------------------------------------------------------------------*/
#endif