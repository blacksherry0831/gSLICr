#include "TrafficSignResult.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignResult::TrafficSignResult(void)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignResult::~TrafficSignResult(void)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignResult::setSampleTemplate(
	std::shared_ptr<TrafficSignPropertyHu>	_sample,
	std::shared_ptr<TrafficSignPropertyHu>	_template)
{

	this->mSample = _sample;
	this->mTemplate = _template;

	const	std::string tp = mTemplate->getPathName();	
	this->mArrowAngle =this->mSample->getArrowAngle(tp);
		
	this->mRectCenter= this->mSample->getRectOrgCenter();

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
double	TrafficSignResult::getAngle()	const
{
	return this->mArrowAngle;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvPoint	TrafficSignResult::getRectCenter()	const
{
	return	this->mRectCenter;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignResult::DrawArrow(IplImage* _src)
{
	CvScalar color= getColor();
	
	const int B = 10;
	CvRect rect= this->mSample->getRectOrg();
	cvRectangleR(_src, rect, color,B);
		
	const int cols = rect.width;
	const int rows = rect.height;
	const int R = std::min(cols, rows) * 2 / 3;

	cv::Point center = getRectCenter();
		
	const double A = getAngle();
	cv::arrowedLine(cv::Mat(_src), center, cv::Point(center.x + R*cos(A), center.y + R*sin(A)), color, B);



}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvScalar TrafficSignResult::getColor()
{

	const std::string color = getColorStr();

	CvScalar cvColor;
	const unsigned char A=255;

	if (color=="green"){
		cvColor = cvScalar(0,255,0, A);
	}else if (color == "yellow"){
		cvColor = cvScalar(0, 255, 255, A);
	}else if (color == "red"){
		cvColor = cvScalar(0, 0, 255, A);
	}else{
		CV_Assert(0);
	}
	

	return cvColor;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignResult::getColorStr() const
{
	const std::string color_t = this->mSample->getColor();
	return color_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<cv::Point> TrafficSignResult::BinImgPoints_ImgCoord() const
{
	return mSample->binaryImgPoints_ImgCoord();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/