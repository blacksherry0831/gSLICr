#include "TrafficSignPropertyBase.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignPropertyBase::TrafficSignPropertyBase()
{
	this->initDefault();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignPropertyBase::~TrafficSignPropertyBase(void)
{
	this->release();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::initDefault()
{
	this->mImgBgra = nullptr;
	this->mImgGray = nullptr;
	this->mImgMask = nullptr;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::alloc(const int _w, const int _h)
{

	if (mImgBgra ==nullptr){
				this->allocImage(_w, _h);
	}else{
				if ((mImgBgra->width==_w) &&
					(mImgBgra->height==_h)){
						//do nothing
				}else{
					this->releaseImage();
					this->allocImage(_w, _h);
				}
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::allocImage(const int _w, const int _h)
{
	mImgBgra = cvCreateImage(cvSize(_w,_h),IPL_DEPTH_8U,4);
	mImgGray = cvCreateImage(cvSize(_w, _h), IPL_DEPTH_8U, 1);
	mImgMask = cvCreateImage(cvSize(_w, _h), IPL_DEPTH_8U, 1);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::releaseImage()
{
	cvReleaseImage(&this->mImgBgra);
	cvReleaseImage(&this->mImgGray);
	cvReleaseImage(&this->mImgMask);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::release()
{
	this->releaseImage();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::allocMem()
{
	this->alloc(this->mRect.width, this->mRect.height);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::setFileName(std::string _fn)
{
	this->mFileName = _fn;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::setPathName(std::string _p)
{
	this->mPathName = _p;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignPropertyBase::getFileName()
{
	return this->mFileName;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignPropertyBase::getPathName()
{
	return this->mPathName;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::setRectOrg(const CvRect _rect)
{
	this->mRectOrg = _rect;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvRect	TrafficSignPropertyBase::getRectOrg()const
{
	return this->mRectOrg;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvPoint TrafficSignPropertyBase::getRectOrgCenter() const
{
	const CvRect rect = this->mRectOrg;
	const int cols = rect.width;
	const int rows = rect.height;
	const CvPoint center = cvPoint(rect.x + cols / 2, rect.y + rows / 2);
	return center;

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::setRect(const CvRect _rect, const int _b)
{
	this->mRect = _rect;
	this->mBorder = _b;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::setColor(std::string _c)
{
	this->mColor = _c;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignPropertyBase::getColor() const
{
	return  mColor;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::setArea(float _a)
{
	this->mArea = _a;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
float TrafficSignPropertyBase::getArea() const
{
	return this->mArea;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignPropertyBase::getAreaStr() const
{
	return std::to_string((int) getArea());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::cpyImageMask(IplImage * _img)
{
	cvSetImageROI(_img, mRect);
	cvCopy(_img, mImgBgra, mImgMask);
	cvResetImageROI(_img);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::cpyImage(IplImage * _img)
{
	cvSetImageROI(_img, mRect);
	
	if (_img->nChannels==3){
		cvCvtColor(_img, mImgBgra,CV_BGR2BGRA);
	}
	
	if (_img->nChannels==4){
		cvCopy(_img, mImgBgra);
	}
		
	cvResetImageROI(_img);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::drawMask(IplImage * _img)
{

	cvSetImageROI(_img, mRect);
	cvCopy(_img,mImgMask);
	cvResetImageROI(_img);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int TrafficSignPropertyBase::imageSize()
{

	if (mImgBgra==nullptr){
		return 0;
	}else{
		return mImgBgra->width*mImgBgra->height;
	}
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyBase::cvt2gray()
{

	cvCvtColor(this->mImgBgra, this->mImgGray, CV_RGB2GRAY);
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<cv::Point>  TrafficSignPropertyBase::binaryImgPoints_ImgCoord() const
{
	std::vector<cv::Point> pts;

	const int X_OFF=mRect.x;
	const int Y_OFF=mRect.y;

	IplImage * img=BinaryImg();
	const int W = img->width;
	const int H = img->height;
	const int STEP =img->widthStep;
	const int CH =img->nChannels;

	for (int xi = 0; xi < W; xi+=2) {
		for (int yi=0; yi <H; yi+=2) {
			const char* c_ptr = img->imageData + yi*STEP + xi*CH;
			const unsigned char data_t = c_ptr[0];
			if (data_t == 255) {
					pts.push_back(cv::Point(xi+X_OFF,yi+Y_OFF));
			}
		}
	}
	
	return pts;

}
/*-----------------------------------------*/
/**
*			try
			{
				
			}
			catch (const cv::Exception& e)
			{
				std::cout<< e.msg ;
			}
*/
/*-----------------------------------------*/
IplImage * TrafficSignPropertyBase::GrayImg()
{
	return mImgGray;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage * TrafficSignPropertyBase::ColorBgraImg()
{
	return mImgBgra;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage * TrafficSignPropertyBase::BinaryImg() const
{
	return this->mImgMask;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/