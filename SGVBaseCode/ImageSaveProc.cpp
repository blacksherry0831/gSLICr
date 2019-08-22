#include "ImageSaveProc.h"
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
int ImageSaveProc::SAVE_DEBUG_2DISK = FALSE;
/*----------------------------------------------------------------*/
int ImageSaveProc::SAVE_IMAGE_2DISK = FALSE;
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
ImageSaveProc::ImageSaveProc(void)
{

}
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
ImageSaveProc::~ImageSaveProc(void)
{

}
/*-------------------------------------------------------------------------------------------*/
/**
*保存图像到硬盘时画上图像的轮廓
*图像ubuff本身不会变化
*
*@param  ubuff  图像原始数据
*@param  labels 图像的超像素标定Labels
*@param	 width  图像宽度
*@param	 height 图像高度
*@param	 filereadfullpath  图像的读取路径
*@param  filewritepath    图像的写入路径
*@param  fileadd       添加到图像文件名中的额外字符串
*
*/
/*-------------------------------------------------------------------------------------------*/
void ImageSaveProc::SaveImgWithContours(
	UINT32* ubuff,
	int* labels,
	const int&			width,
	const int&			height,
	std::string			filereadfullpath,
	std::string			filewritepath,
	std::string			fileadd)
{

	TimeMeasure tm("SaveImgWithContours");
	
	if (SAVE_IMAGE_2DISK == FALSE) {
		printf("SaveImgWithContours: --not-- \n");
	}
	else {
		unsigned int * imgbuf_t = new unsigned int[width*height];
		memcpy(imgbuf_t, ubuff, sizeof(unsigned int)*width*height);

		DrawContoursAroundSegments(imgbuf_t, labels, width, height, BlackColorPNG);

		if (fileadd == "") {
			fileadd = GetCurrentTimeStr();
		}
		SaveImageData(imgbuf_t, width, height, filereadfullpath, filewritepath, 1, fileadd);
		delete[]imgbuf_t;
	}

}
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
void ImageSaveProc::DrawContoursAroundSegments(
	unsigned int*			ubuff,
	int*					labels,
	const int&				width,
	const int&				height,
	const unsigned int&		color)
{
	
}
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
std::string ImageSaveProc::GetCurrentTimeStr(void)
{

	std::string cui_t;

#ifdef _WIN32 || _WIN64
#if _WIN32 || _WIN64
#if _MSC_VER

	time_t curtime = time(0);
	struct tm tim;
	localtime_s(&tim, &curtime);

	char title[128];
	static int s_num = 0;
	sprintf(title, "%d_%02d_%02d_%02d_%02d_%02d", tim.tm_year + 1900, tim.tm_mon + 1,
		tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);

	/*SYSTEMTIME systime;
	cui_t="win32__win64";*/
	cui_t.append(title);
#endif


#ifdef Use_CString&&_MSC_VER
#if Use_CString	&&_MSC_VER
	SYSTEMTIME systime;
	CString strName, Time;
	GetSystemTime(&systime);
#if 1
	Time.Format(_T("%u_%u_%u_%u_%u_%u_%u"),
		systime.wYear,
		systime.wMonth,
		systime.wDay,
		systime.wHour,
		systime.wMinute,
		systime.wSecond,
		systime.wMilliseconds);
#else
	Time.Format(_T("%u:%u:%u__%uMs"),
		systime.wHour,
		systime.wMinute,
		systime.wSecond,
		systime.wMilliseconds);
#endif
	cui_t = cui_GeneralImgProcess::ConvertCS2string(Time);
#endif
#endif


#endif


#endif
	/**********************************/
#ifdef linux
#if linux 
	cui_t = "linux_time";
#endif
#endif
	/**********************************/
	return cui_t;
}
/*----------------------------------------------------------------*/
/**
*将图像矩阵保存到硬盘
*
*@param 	imgBuffer  图像矩阵
*@param     width      图像宽度
*@param 	height     图像高度
*@param 	outFilename  图像要保存的文件名
*@param 	saveLocation  图像要保存的路径
*@param 	format     图片格式
*@param 	str       保存图片时的附加字符串
*
*/
/*----------------------------------------------------------------*/
void ImageSaveProc::SaveImageData(
	UINT32*				imgBuffer,
	int					width,
	int					height,
	std::string&				outFilename,
	std::string&				saveLocation,
	int					format,
	const std::string&		str)
{

	if (SAVE_IMAGE_2DISK == FALSE) {
		printf("SaveImageData: --not-- \n");
	}
	else {
		int sz = width*height;
		IplImage *Save_Image_t;
		Save_Image_t = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 4);
		memcpy(Save_Image_t->imageData, imgBuffer, 4 * width*height);
		//-----------------------------------------
		// Prepare path and save the result images
		//-----------------------------------------
		std::string path = saveLocation;
		char fname[_MAX_FNAME];
		_splitpath(outFilename.c_str(), NULL, NULL, fname, NULL);
		path += fname;

		if (0 != str.compare("")) path.append(str);
		if (1 == format) path.append(".png");
		if (0 == format) path.append(".bmp");

		printf("cvSaveImage: %s \n", path.c_str());
		cvSaveImage(path.c_str(), Save_Image_t);
		cvReleaseImage(&Save_Image_t);
	}
	
}
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/