#pragma once
/*-----------------------------------------*/

/*-----------------------------------------*/
#include "TrafficSignPropertyHu.hpp"
/*-----------------------------------------*/
class TrafficSignResult
{
public:
	TrafficSignResult(void);
	~TrafficSignResult(void);
private:
	std::shared_ptr<TrafficSignPropertyHu>	mSample;
	std::shared_ptr<TrafficSignPropertyHu>	mTemplate;
private:
	double	mArrowAngle;
	CvPoint	mRectCenter;
public:
	void setSampleTemplate(
		std::shared_ptr<TrafficSignPropertyHu>	_sample,
		std::shared_ptr<TrafficSignPropertyHu>	_template);
public:
	std::vector<cv::Point> BinImgPoints_ImgCoord() const;
public:
	double	getAngle()	const;
	CvPoint	getRectCenter()	const;

	void DrawArrow(IplImage* _src);
	CvScalar getColor();
	std::string  getColorStr()	const;

};