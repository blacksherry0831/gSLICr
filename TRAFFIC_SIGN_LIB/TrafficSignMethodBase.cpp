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
void TrafficSignMethodBase::CloneImage(IplImage * _src)
{
	if (mImgOrg != nullptr) {
		cvReleaseImage(&mImgOrg);
	}
	
	this->mImgOrg = cvCloneImage(_src);

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
float TrafficSignMethodBase::LogPolarMatchAngle(cv::Mat _s, cv::Mat _t)
{
	CV_Assert(!_s.empty() && ! _t.empty());
	
	resizeSameSize(_s,  _t);

	const int S = 1;
	const int polarCols = (_s.cols >> 1)*S;
	const int polarRows = (_s.rows >> 1)*S;
	
	cv::Size	SZ(polarCols*2, polarRows*2);

	cv::Mat ps = cv::Mat::zeros(SZ, CV_8UC1);
	cv::Mat pt = cv::Mat::zeros(SZ, CV_8UC1);

	IplImage ipl_s = _s, ipl_ps = ps;
	IplImage ipl_t = _t, ipl_pt = pt;
	const double M = 40;
	
	cvLogPolar(&ipl_s, &ipl_ps, cvPoint2D32f(polarCols, polarRows), M);
	cvLogPolar(&ipl_t, &ipl_pt, cvPoint2D32f(polarCols, polarRows), M);

	cv::Mat ps_64f, pt_64f;
	ps.convertTo(ps_64f, CV_64F);
	pt.convertTo(pt_64f, CV_64F);

	cv::Point2d pot;
	pot = cv::phaseCorrelate(ps_64f, pt_64f);
#if 0
	try
	{
	
	}
	catch (const cv::Exception&e)
	{
		std::cout << e.msg;
	}
#endif // 0

	const float r = pot.y * 180 / (polarCols);

	const float scale = exp(pot.x / M);
	
	return r;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodBase::resizeSameSize(cv::Mat & _s, cv::Mat & _t)
{
	
	if ((_s.cols == _t.cols  )&&
		(_s.rows == _t.rows)){
		return;
	}

	const int col = std::max(_s.cols, _t.cols);
	const int row = std::max(_s.rows, _t.rows);
	const int T= _s.type();
	cv::Size  SZ(col,row);
	
	cv::Rect s_roi((col - _s.cols) / 2, (row - _s.rows) / 2, _s.cols, _s.rows);
	cv::Rect t_roi((col - _t.cols) / 2, (row - _t.rows) / 2, _t.cols, _t.rows);

	cv::Mat s = cv::Mat::zeros(SZ, T);
	cv::Mat t = cv::Mat::zeros(SZ, T);
	
	_s.copyTo(s(s_roi));
	_t.copyTo(t(t_roi));
	
	_s = s;
	_t = t;
	
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