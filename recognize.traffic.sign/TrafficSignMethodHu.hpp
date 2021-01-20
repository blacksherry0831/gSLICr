#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "TrafficSignPropertyHu.hpp"
#include "TrafficSignProperty.hpp"
/*-----------------------------------------*/
#include "TrafficSignMethodBase.hpp"
/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/
class TrafficSignMethodHu : public  TrafficSignMethodBase
{
public:
	TrafficSignMethodHu(void);
	~TrafficSignMethodHu(void);
private:
	std::vector<std::shared_ptr<TrafficSignPropertyHu>>   mProperty;

private:
	void FillExternalContours(
		IplImage * pBinary,
		IplImage * _imgOut,
		const float _areaMin,
		const float _areaMax,
		std::string _colour);

public:
	bool IsContourSizeInRange(const CvSeq* _c,const float _min,const float _max);
	bool IsContourSizeInRange(const float _area, const float _min, const float _max);
public:
	CvRect  rectExpandBorder(
		CvRect _r,
		const int _b,
		const int _w,
		const int _h);

	int getTopLeft( int _tl, const int _b);
	int getWidthHeight(const int _tl, int _wh, const int _b, const int R);
	
public:
	void cutTempleteArea(const int _blockSz);
	void saveTempleteAreaImage();
public:	
	std::shared_ptr<TrafficSignPropertyHu> getImgRectMax();
public:
	std::vector<std::shared_ptr<TrafficSignPropertyHu>> getProperty();

	std::vector<std::shared_ptr<TrafficSignPropertyHu>> 
		MatchHu( std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps);

};