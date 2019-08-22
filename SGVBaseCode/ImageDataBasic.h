#pragma once
/*----------------------------------------------------------------*/
#include "cpp_basic.h"
#include "opencv_basic.h"
/*----------------------------------------------------------------*/
#include "cpp_def.h"
#include "cpp_def_debug.h"
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class ImageDataBasic
{
public:
	ImageDataBasic(
		std::string filename,
		std::string filesavepath);

	ImageDataBasic(
		IplImage* img,
		std::string filesavepath="");

	~ImageDataBasic(void);
public:
	static void ConvertImg2Eighth4Ch(IplImage ** src);
	static void ConvertImg3ChTo4Ch(IplImage ** src);

private:
	void SetImageDataBasic(
		std::string filename,
		std::string filesavepath);

	void initParam(void);

	void InitMemoryData(
		IplImage* img,
		std::string filename,
		std::string filesavepath);	
	
	void ReleaseMemory(void);

private:
	std::string FileReadFullPath;
	std::string FileWritePath;

private:	
	IplImage* srcCv_ImgBGRA;	

public:
	IplImage* GetIplImagePtr();

};

