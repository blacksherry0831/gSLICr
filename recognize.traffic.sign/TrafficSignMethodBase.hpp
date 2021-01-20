#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "TrafficSignPropertyBase.hpp"
#include "TrafficSignProperty.hpp"

#include "TrafficSignMethodBase.hpp"

/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/
class TrafficSignMethodBase
{
public:
	TrafficSignMethodBase(void);
	~TrafficSignMethodBase(void);
public:
	const CvScalar ColorWhite = CV_RGB(255, 255, 255);
public:
	const CvScalar B_low = cvScalar(100, 43, 46);
	const CvScalar B_up = cvScalar(124, 255, 255);

	const CvScalar Orange_low = cvScalar(11, 43, 46);
	const CvScalar Orange_up = cvScalar(25, 255, 255);

	const CvScalar Y_low = cvScalar(26, 43, 46);
	const CvScalar Y_up = cvScalar(34, 255, 255);

	const CvScalar R00_low = cvScalar(0, 43, 46);
	const CvScalar R00_up  = cvScalar(10, 255, 255);

	const CvScalar R01_low = cvScalar(156, 43, 46);
	const CvScalar R01_up  = cvScalar(180, 255, 255);

	const CvScalar Green_low = cvScalar(35, 43, 46);
	const CvScalar Green_up  = cvScalar(77, 255, 255);

	const CvScalar Cyan_low = cvScalar(78, 43, 46);
	const CvScalar Cyan_up  = cvScalar(99, 255, 255);

protected:
	std::string		mPathFull;
	std::string		mFileName;
	std::string		mFilePath;
	std::string     mPathName;
protected:
	IplImage*  mImgOrg;
	IplImage*  mImgHsv;

	IplImage*  mImgBinGreen;
	IplImage*  mImgBinYellow;
	IplImage*  mImgBinRed;
	IplImage*  mImgBinRed00;
	IplImage*  mImgBinRed01;

	IplImage*  mImgBlockGreen;
	IplImage*  mImgBlockYellow;
	IplImage*  mImgBlockRed;
protected:
	CvMemStorage* mMemStorage;
private:
	void  init();
	void  destory();
	void  allocImg();
	void  allocImg(const int _w,const int _h, const int _d);
	void  releaseImg();

public:
	void LoadImage(const std::string _p);
public:
	static bool IsContourSizeInRange(const CvSeq* _c,const float _min,const float _max);
	static bool IsContourSizeInRange(const float _area, const float _min, const float _max);
public:
	CvRect  rectExpandBorder(
		CvRect _r,
		const int _b,
		const int _w,
		const int _h);
public:
	void cutTempleteArea(const int _blockSz);
	

};