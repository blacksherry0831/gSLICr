#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/
class TrafficSignProperty
{
public:
	TrafficSignProperty();
	~TrafficSignProperty(void);
private:
	const int		nfeatures = 0;
	const int		nOctaveLayers = 3;
	const double	contrastThreshold = 0.04;
	const double	edgeThreshold = 100;
private:
	IplImage*		mImgBgra;
	IplImage*		mImgGray;
	IplImage*		mImgMask;
	CvRect			mRect;
	CvRect			mRectOrg;
	int				mBorder;
	std::string		mColor;
	float			mArea;
	cv::Mat			mImgMatch;
private:
	cv::Mat			mMatGrayTest;
private:
	std::string     mFullPath;
	std::string     mFilePath;
private:
	std::string     mFileName;
	std::string     mPathName;
private:
	std::vector<cv::KeyPoint> mKp;
	cv::Mat					  mDescriptor;
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
	std::string getFileName();
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
	void saveImageTemplete(std::string _p);
	void saveImgResult(std::string _path);
	void saveImgMatch(cv::Mat _match,std::string _path,std::string _src);
public:
	cv::Mat getDescriptor();
	std::vector<cv::KeyPoint> getKeyPoint();

	std::vector< cv::DMatch > getGoodDMatch(std::vector< cv::DMatch > _m);

	std::vector< cv::DMatch > ratioTest(std::vector<std::vector<cv::DMatch> > _matchePoints);

	float					  getMeanDist(std::vector< cv::DMatch > _m);
public:
	void cvt2gray();
public:
	void imgProcSift();
	bool imgMatchFlannSift(std::vector<std::shared_ptr<TrafficSignProperty>> _tmps);
	bool imgMatchBfSift_CrossCheck(const int _i, std::vector<std::shared_ptr<TrafficSignProperty>> _tmps);
	bool imgMatchBfSift_RatioTest(std::vector<std::shared_ptr<TrafficSignProperty>> _tmps);
public:
	IplImage * siftImg();
	IplImage * GrayImg();

	bool refineMatchesWithHomography(
		const std::vector<cv::KeyPoint>& queryKeypoints,
		const std::vector<cv::KeyPoint>& trainKeypoints,
		float reprojectionThreshold,
		std::vector<cv::DMatch>& matches,
		cv::Mat & homography);


};

