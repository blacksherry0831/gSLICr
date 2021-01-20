#include "TrafficSignMethodBase.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignMethodBase::TrafficSignMethodBase(void)
{
	this->init();
	//this->allocImg();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignMethodBase::~TrafficSignMethodBase(void)
{
	this->releaseImg();
	this->destory();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::init()
{

	this->mMemStorage = cvCreateMemStorage(0);
	
	this->mImgOrg = nullptr;
	this->mImgHsv = nullptr;

	this->mImgBinGreen = nullptr;
	this->mImgBinYellow = nullptr;
	this->mImgBinRed = nullptr;
	this->mImgBinRed00 = nullptr;
	this->mImgBinRed01 = nullptr;

	this->mImgBlockGreen = nullptr;
	this->mImgBlockYellow = nullptr;
	this->mImgBlockRed = nullptr;
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::destory()
{
	cvClearMemStorage(mMemStorage);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::allocImg()
{
	const int W = mImgOrg->width;
	const int H = mImgOrg->height;
	const int D = mImgOrg->depth;

	if (mImgHsv==nullptr){		
			allocImg(W, H,D);
	}else{
		if ((mImgHsv->width == W)
			&& (mImgHsv->height == H)) {
			//do nothing 
		}else{
			releaseImg();
			allocImg(W, H,D);
		}
	}
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::allocImg(const int _w, const int _h,const int _d)
{
	const CvSize SZ =cvSize(_w, _h);
	this->mImgHsv = cvCreateImage(SZ,_d,3);

	this->mImgBinGreen  = cvCreateImage(SZ, _d, 1);
	this->mImgBinYellow = cvCreateImage(SZ, _d, 1);
	this->mImgBinRed    = cvCreateImage(SZ, _d, 1);
	this->mImgBinRed00 = cvCreateImage(SZ, _d, 1);
	this->mImgBinRed01 = cvCreateImage(SZ, _d, 1);

	this->mImgBlockGreen  = cvCreateImage(SZ, _d, 1);
	this->mImgBlockYellow = cvCreateImage(SZ, _d, 1);
	this->mImgBlockRed    = cvCreateImage(SZ, _d, 1);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::releaseImg()
{
	cvReleaseImage(&this->mImgOrg);
	cvReleaseImage(&this->mImgHsv);
	
	cvReleaseImage(&this->mImgBinGreen);
	cvReleaseImage(&this->mImgBinYellow);
	cvReleaseImage(&this->mImgBinRed);
	cvReleaseImage(&this->mImgBinRed00);
	cvReleaseImage(&this->mImgBinRed01);
	
	cvReleaseImage(&this->mImgBlockGreen);
	cvReleaseImage(&this->mImgBlockYellow);
	cvReleaseImage(&this->mImgBlockRed);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::LoadImage(const std::string _p)
{
	if (mImgOrg != nullptr) {
		cvReleaseImage(&mImgOrg);
	}
	this->mPathFull = _p;
	this->mFilePath = Base::FS_getSuperDirPath(_p);
	this->mFileName = Base::FS_getFileName(_p);
	this->mPathName = Base::FS_getEndDirName(this->mFilePath);
		
	this->mImgOrg = cvLoadImage(_p.c_str(), CV_LOAD_IMAGE_UNCHANGED);

	this->allocImg();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool TrafficSignMethodBase::IsContourSizeInRange(const CvSeq * _c, const float _min, const float _max)
{
	CV_Assert(_c!=0);
	CV_Assert(_min < _max);

	const float dConArea = fabs(cvContourArea(_c, CV_WHOLE_SEQ));

	if (dConArea > _min && dConArea < _max){
		return true;
	}else{
		return false;
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool TrafficSignMethodBase::IsContourSizeInRange(const float _area, const float _min, const float _max)
{

	CV_Assert(_area >= 0);
	CV_Assert(_min < _max);

	if (_area >= _min && _area <= _max) {
		return true;
	}else {
		return false;
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvRect TrafficSignMethodBase::rectExpandBorder(
	CvRect _r,
	const int _b,
	const int _w,
	const int _h)
{
	const int BX2=_b*2;

	const int rx = ((_r.x - _b) > 0) ? (_r.x - _b) : 0;
	const int ry = ((_r.y - _b) > 0) ? (_r.y - _b) : 0;
	const int rw = ((_r.width + BX2) < _w) ? (_r.width + BX2) : _w;
	const int rh = ((_r.height + BX2) < _h) ? (_r.height + BX2) : _h;

	return 	 cvRect(rx, ry, rw, rh);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::cutTempleteArea(const int _blockSz)
{
	cvCvtColor(mImgOrg, mImgHsv, CV_BGR2HSV);//CV_BGR2HSV

	cvInRangeS(mImgHsv, Orange_low, Y_up, mImgBinYellow);//yellow-orange

	cvInRangeS(mImgHsv, R00_low, R00_up, mImgBinRed00);//red
	cvInRangeS(mImgHsv, R01_low, R01_up, mImgBinRed01);//red
	cvOr(mImgBinRed00, mImgBinRed01, mImgBinRed);//red

	cvInRangeS(mImgHsv, Cyan_low, Cyan_up, mImgBinGreen);//cyan
		

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/