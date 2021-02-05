#include "TrafficSignMethod.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignMethod::TrafficSignMethod(void)
{
	this->init();
	//this->allocImg();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignMethod::~TrafficSignMethod(void)
{
	this->releaseImg();
	this->destory();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethod::init()
{
	this->mMemStorage = cvCreateMemStorage(0);
	
	this->mImgOrg = nullptr;
	this->mImgHsv = nullptr;
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethod::destory()
{
	cvClearMemStorage(mMemStorage);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethod::allocImg()
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
void TrafficSignMethod::allocImg(const int _w, const int _h,const int _d)
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
void TrafficSignMethod::releaseImg()
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
void TrafficSignMethod::LoadImage(const std::string _p)
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
bool TrafficSignMethod::IsContourSizeInRange(const CvSeq * _c, const float _min, const float _max)
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
bool TrafficSignMethod::IsContourSizeInRange(const float _area, const float _min, const float _max)
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
CvRect TrafficSignMethod::rectExpandBorder(
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
void TrafficSignMethod::cutTempleteArea(const int _blockSz)
{
	cvCvtColor(mImgOrg, mImgHsv, CV_BGR2HSV);//CV_BGR2HSV

	cvInRangeS(mImgHsv, Orange_low, Y_up, mImgBinYellow);//yellow-orange

	cvInRangeS(mImgHsv, R00_low, R00_up, mImgBinRed00);//red
	cvInRangeS(mImgHsv, R01_low, R01_up, mImgBinRed01);//red
	cvOr(mImgBinRed00, mImgBinRed01, mImgBinRed);//red

	cvInRangeS(mImgHsv, Cyan_low, Cyan_up, mImgBinGreen);//cyan
	
	FillExternalContours(mImgBinGreen, mImgBlockGreen,		_blockSz / 2, _blockSz * 2,	"green");
	FillExternalContours(mImgBinYellow, mImgBlockYellow,	_blockSz / 2, _blockSz * 2,	"yellow");
	FillExternalContours(mImgBinRed, mImgBlockRed,			_blockSz / 2, _blockSz * 2,	"red");

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethod::saveTempleteAreaImage()
{
	const std::string path = "TrafficSignTemplate";

	Base::FS_createDir(path);

	const int SZ = mProperty.size();
	for (size_t i = 0; i < SZ; i++){
			
		std::shared_ptr<TrafficSignProperty>  p = mProperty.at(i);
			
		std::string  path_sub=Base::FS_createPath(path, mPathName);	
		
		std::string ffn;
		ffn.append(p->getColor()).append(".").
			append(p->getAreaStr()).append(".").
			append(mPathName).append(".").
			append(std::to_string(i)).append(".").
			append(mFileName);
		
		std::string  fullpath=path_sub+ffn;

		p->saveImageTemplete(fullpath);
		
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::shared_ptr<TrafficSignProperty> TrafficSignMethod::getTrafficSignMax()
{

	const int SZ = mProperty.size();

	std::shared_ptr<TrafficSignProperty> p_max;
	for (size_t i = 0; i < SZ; i++) {
		std::shared_ptr<TrafficSignProperty>  p = mProperty.at(i);

		if (p_max ==nullptr){
			p_max = p;
		}else{
			if (p->imageSize() >p_max->imageSize() )
			{
				p_max = p;
			}
		}

	}
	
	return  p_max;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::shared_ptr<TrafficSignProperty>> TrafficSignMethod::ImgFragProcSift()
{

	for each (auto p in mProperty){
			p->imgProcSift();
	}

	return mProperty;

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::shared_ptr<TrafficSignProperty>> TrafficSignMethod::MatchSift(
	std::vector<std::shared_ptr<TrafficSignProperty>> _tmps,
	std::vector<std::shared_ptr<TrafficSignProperty>> _smps)
{

	for (int si = 0; si <_smps.size(); si++)
	{
		std::shared_ptr<TrafficSignProperty> s = _smps.at(si);

		s->imgMatchBfSift_CrossCheck(si,_tmps);
	}

	return std::vector<std::shared_ptr<TrafficSignProperty>>();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethod::FillExternalContours(
	IplImage *pBinary,
	IplImage* _imgOut,
	const float _areaMin,
	const float _areaMax,
	std::string _colour)
{
	const int B = 10;
	CvSeq *pContour = NULL;
	
	if (_imgOut) {
		cvZero(_imgOut);
	}

	// 执行条件   
	if (pBinary==nullptr) {
		return;
	}

	cvFindContours(pBinary, mMemStorage, &pContour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);// 查找所有轮廓   
	for (; pContour != NULL; pContour = pContour->h_next){															
								
			if (CV_IS_SEQ_CLOSED(pContour)) {
									
										const float conArea = fabs(cvContourArea(pContour, CV_WHOLE_SEQ));

										if (IsContourSizeInRange(conArea,_areaMin,_areaMax)){

														cvDrawContours(_imgOut, pContour, ColorWhite, ColorWhite, 0, CV_FILLED);										
														const CvRect rect = cvBoundingRect(pContour, B);
#if 0
														cvRectangle(_imgOut,
															cvPoint(rect.x, rect.y),
															cvPoint(rect.x + rect.width, rect.y + rect.height),
															ColorWhite,
															1, 8, 0);
#endif // 0
														const CvRect rect_ex = rectExpandBorder(rect, B,pBinary->width,pBinary->height);
										
														std::shared_ptr<TrafficSignProperty>  p(new TrafficSignProperty());
														p->setRectOrg(rect);
														p->setRect(rect_ex,B);
														p->setColor(_colour);
														p->setArea(conArea);
														p->setFileName(mFileName);

														p->allocMem();

														p->drawMask(_imgOut);
														p->cpyImage(mImgOrg);
														p->cvt2gray();

														mProperty.push_back(p);

										}
											

										
					}									
	}
	
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/