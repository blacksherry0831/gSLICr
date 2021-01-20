#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/
class TrafficSignPropertyBase
{
public:
	TrafficSignPropertyBase();
	~TrafficSignPropertyBase(void);
protected:
	IplImage*		mImgBgra;
	IplImage*		mImgGray;
	IplImage*		mImgMask;
	CvRect			mRect;
	CvRect			mRectOrg;
	int				mBorder;
	std::string		mColor;
	float			mArea;
protected:
	cv::Mat			mMatGrayTest;
protected:
	std::string     mFullPath;
	std::string     mFilePath;
protected:
	std::string     mFileName;
	std::string     mPathName;
private:
	void initDefault();
private:
	void  alloc(const int _w,const int _h);
	void  allocImage(const int _w, const int _h);
	void  releaseImage();
	void  release();
public:
	void	allocMem();
public:
	void setFileName(std::string _fn);
	void setPathName(std::string _p);
	std::string getFileName();
	std::string getPathName();

public:
	void			setRectOrg(const CvRect _rect);
	void			setRect(const CvRect _rect, const int _b);
	void			setColor(std::string _c);
	std::string		getColor();
	void			setArea(float _a);
	float			getArea() const;
	std::string		getAreaStr() const;
public:
	void cpyImageMask(IplImage* _img);
	void cpyImage(IplImage* _img);
	void drawMask(IplImage* _img);
public:
	int imageSize();
public:
	void cvt2gray();
public:
	IplImage * GrayImg();
	IplImage * ColorBgraImg();
	IplImage * BinaryImg();
	
};

