#include "TrafficSignMethodHu.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignMethodHu::TrafficSignMethodHu(void)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignMethodHu::~TrafficSignMethodHu(void)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool TrafficSignMethodHu::IsContourSizeInRange(const CvSeq * _c, const float _min, const float _max)
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
bool TrafficSignMethodHu::IsContourSizeInRange(const float _area, const float _min, const float _max)
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
CvRect TrafficSignMethodHu::rectExpandBorder(
	CvRect _r,
	const int _b,
	const int _w,
	const int _h)
{
	const int BX2=_b*2;

	const int rx = getTopLeft(_r.x,_b);
	const int ry = getTopLeft(_r.y, _b);

	const int rw = getWidthHeight(rx, _r.width, BX2,_w );
	const int rh = getWidthHeight(ry, _r.height, BX2,_h );

	return 	 cvRect(rx, ry, rw, rh);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int TrafficSignMethodHu::getTopLeft( int _tl, const int _b)
{
	const int B = _b;
	
	for (int i = B; i > 0; i--){
		
	
		if (_tl == 0 )
		{
			break;
		}

		--_tl;

	}

	assert(_tl >= 0);

	return _tl;
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int TrafficSignMethodHu::getWidthHeight(const int _tl, int _wh, const int _b, const int R)
{
	const int B = _b;

	for (int i = B; i > 0; i--) {

		if (_tl + _wh == R) {
			break;
		}

		_wh++;

	}

	assert(_tl + _wh <=R);

	return _wh;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodHu::cutTempleteArea(const int _blockSz)
{
	cvCvtColor(mImgOrg, mImgHsv, CV_BGR2HSV);//CV_BGR2HSV

	cvInRangeS(mImgHsv, Orange_low, Y_up, mImgBinYellow);//yellow-orange

	cvInRangeS(mImgHsv, R00_low, R00_up, mImgBinRed00);//red
	cvInRangeS(mImgHsv, R01_low, R01_up, mImgBinRed01);//red
	cvOr(mImgBinRed00, mImgBinRed01, mImgBinRed);//red

	cvInRangeS(mImgHsv, Cyan_low, Cyan_up, mImgBinGreen);//cyan

	this->mProperty.clear();

	FillExternalContours(mImgBinGreen, mImgBlockGreen,		_blockSz / 2, _blockSz * 2,	"green");
	FillExternalContours(mImgBinYellow, mImgBlockYellow,	_blockSz / 2, _blockSz * 2,	"yellow");
	FillExternalContours(mImgBinRed, mImgBlockRed,			_blockSz / 2, _blockSz * 2,	"red");

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignMethodHu::saveTempleteAreaImage()
{
	const std::string path = "TrafficSignTemplate";

	Base::FS_createDir(path);

	const int SZ = mProperty.size();
	for (size_t i = 0; i < SZ; i++){
			
		std::shared_ptr<TrafficSignPropertyHu>  p = mProperty.at(i);
			
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
void TrafficSignMethodHu::FillExternalContours(
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
													
#if 1
														double pm = cvContourPerimeter(pContour)*1E-3;
														pContour = cvApproxPoly(pContour, sizeof(CvContour), mMemStorage, CV_POLY_APPROX_DP, pm, 0);
#endif // 0

														cvDrawContours(_imgOut, pContour, ColorWhite, ColorWhite, 0, CV_FILLED,CV_AA);
														//cvDrawContours(_imgOut, pContour, ColorWhite, ColorWhite, 0, 10, CV_AA);
														const CvRect rect = cvBoundingRect(pContour, B);
#if 0
														cvRectangle(_imgOut,
															cvPoint(rect.x, rect.y),
															cvPoint(rect.x + rect.width, rect.y + rect.height),
															ColorWhite,
															1, 8, 0);
#endif // 0
														const CvRect rect_ex = rectExpandBorder(rect, B,pBinary->width,pBinary->height);
										
														std::shared_ptr<TrafficSignPropertyHu>  p(new TrafficSignPropertyHu());
														p->setRectOrg(rect);
														p->setRect(rect_ex,B);
														p->setColor(_colour);
														p->setArea(conArea);
														p->setFileName(mFileName);
														p->setPathName(mPathName);
														p->allocMem();

														p->drawMask(_imgOut);
														p->cpyImage(mImgOrg);
														p->cvt2gray();
														p->CloneSeq(pContour);

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
std::shared_ptr<TrafficSignPropertyHu> TrafficSignMethodHu::getImgRectMax()
{
	const int SZ = mProperty.size();

	std::shared_ptr<TrafficSignPropertyHu> p_max;
	for (size_t i = 0; i < SZ; i++) {
		
		auto  p = mProperty.at(i);

		if (p_max == nullptr) {
			p_max = p;
		}else {
			if (p->imageSize() >p_max->imageSize())
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
std::vector<std::shared_ptr<TrafficSignPropertyHu>> 
TrafficSignMethodHu::getProperty()
{
	return mProperty;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<TrafficSignResult>
TrafficSignMethodHu::MatchHu(
	std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps,
	const int _output)
{
	std::vector<TrafficSignResult>  results;

	for (int si = 0; si <mProperty.size(); si++)
	{
		std::shared_ptr<TrafficSignPropertyHu> sample = mProperty.at(si);
		std::shared_ptr<TrafficSignPropertyHu> temp;

		float	similar = sample->MatchHuPropertySimilar(temp, _tmps);
		
		if (similar <1+1E-3){

#if _DEBUG
 if(_output) TrafficSignPropertyHu::MatchOutPut(si,sample, temp);
#endif // _DEBUG
 		
				sample->getTempleteAngle(temp);	

				TrafficSignResult result;
				result.setSampleTemplate(sample,temp);
				results.push_back(result);


		}
								
	}

	return results;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/