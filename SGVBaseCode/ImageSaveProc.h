#pragma once
/*----------------------------------------------------------------*/
#include "cpp_def_type.h"
/*----------------------------------------------------------------*/
#include "ColorDef.h"
/*----------------------------------------------------------------*/
#include "MY_SDK_LIB/TimeMeasure.hpp"
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class ImageSaveProc
{
public:
	ImageSaveProc(void);
	~ImageSaveProc(void);
public:
	static int SAVE_IMAGE_2DISK;
	static int SAVE_DEBUG_2DISK;
public:
	static void SaveImgWithContours(
		UINT32*				ubuff,
		int*				labels,
		const int&			width,
		const int&			height,
		std::string			filereadfullpath,
		std::string			filewritepath,
		std::string			fileadd);

	static void DrawContoursAroundSegments(
		unsigned int * ubuff,
		int * labels,
		const int & width,
		const int & height,
		const unsigned int & color);

	static std::string GetCurrentTimeStr(void);

	static void SaveImageData(
		UINT32 * imgBuffer,
		int width,
		int height,
		std::string & outFilename,
		std::string & saveLocation, 
		int format,
		const std::string & str);

};

