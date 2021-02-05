#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
#include <map>
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/
#include "TrafficSignPropertyBase.hpp"
/*-----------------------------------------*/
class TrafficSignPropertyHu :public TrafficSignPropertyBase
{
public:
	TrafficSignPropertyHu();
	~TrafficSignPropertyHu(void);
private:
	CvSeq*			mContours;
	CvMemStorage*	mMemStorage;
	double			mHuSimilar;
	double			mRotationAngle;
public:
	void CloneSeq(const CvSeq* _seq);
	CvSeq*	getSeq();
public:
	double getHuSimilar() const;
	std::string getHuSimilarStr() const;
public:
	void saveImgBinary(std::string _path);

	void saveImageTemplete(std::string _p);

	void imgProcHu();

	std::shared_ptr<TrafficSignPropertyHu>
		MatchHuProperty(std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps);

	float 
		MatchHuPropertySimilar(
			std::shared_ptr<TrafficSignPropertyHu>& _tmp_out,
			std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps);

	std::shared_ptr<TrafficSignPropertyHu>
		MatchHuProperty2(std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps);

	double matchShapesSeq(const CvSeq* _seq);

	double matchShapesImg(TrafficSignPropertyHu * _tsph);

	static void MatchOutPut(const int									_si, 
							std::shared_ptr<TrafficSignPropertyHu>		_s,
							std::shared_ptr<TrafficSignPropertyHu>		_t);

	static void copyImgRect(
		IplImage * _src,
		IplImage * _dst,
		IplImage * _mask,
		CvRect _r);

	double	getTempleteAngle(std::shared_ptr<TrafficSignPropertyHu> _t);

	double	getArrowAngle(const std::string _type);

	double calcRotateAngle1(
		cv::Mat & roi,
		cv::Mat & tmpl,
		std::vector<std::vector<cv::Point>>& roiContours);

	void Rotate(const cv::Mat & srcImage, cv::Mat & destImage, double angle);

	void resize2square(cv::Mat & _src, cv::Mat & _square);
	cv::Mat resizeMat(cv::Mat  _src, int _rc);

	void DrawArrow(std::string _type);

	int getIntMax(std::vector<int> _data);
	

};

