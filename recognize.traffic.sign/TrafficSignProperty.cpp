#include "TrafficSignProperty.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignProperty::TrafficSignProperty()
{
	this->initDefault();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignProperty::~TrafficSignProperty(void)
{
	this->release();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::initDefault()
{
	mImgBgra = nullptr;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::alloc(const int _w, const int _h)
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
void TrafficSignProperty::allocImage(const int _w, const int _h)
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
void TrafficSignProperty::releaseImage()
{
	cvReleaseImage(&this->mImgMask);
	cvReleaseImage(&this->mImgBgra);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::release()
{
	this->releaseImage();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::allocMem()
{
	this->alloc(this->mRect.width, this->mRect.height);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::setFileName(std::string _fn)
{
	this->mFileName = _fn;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignProperty::getFileName()
{
	return this->mFileName;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::setRectOrg(const CvRect _rect)
{
	this->mRectOrg = _rect;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::setRect(const CvRect _rect, const int _b)
{
	this->mRect = _rect;
	this->mBorder = _b;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::setColor(std::string _c)
{
	this->mColor = _c;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignProperty::getColor()
{
	return  mColor;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::setArea(float _a)
{
	this->mArea = _a;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
float TrafficSignProperty::getArea() const
{
	return this->mArea;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignProperty::getAreaStr() const
{
	return std::to_string((int) getArea());
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::cpyImageMask(IplImage * _img)
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
void TrafficSignProperty::cpyImage(IplImage * _img)
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
void TrafficSignProperty::drawMask(IplImage * _img)
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
int TrafficSignProperty::imageSize()
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
void TrafficSignProperty::saveImageTemplete(std::string _p)
{
	cvSaveImage(_p.c_str(), mImgBgra);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::saveImgResult(std::string _path)
{
	std::string ffp = _path + this->mFileName;
	imwrite(ffp.c_str(), mMatGrayTest);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::saveImgMatch(cv::Mat _match, std::string _path,std::string _src)
{

	if (!_match.empty()) {
		std::string ffp = _path +_src+ this->mFileName;
		imwrite(ffp.c_str(), _match);	
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
cv::Mat TrafficSignProperty::getDescriptor()
{
	return  this->mDescriptor;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<cv::KeyPoint> TrafficSignProperty::getKeyPoint()
{
	return this->mKp;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<cv::DMatch> TrafficSignProperty::getGoodDMatch(std::vector<cv::DMatch> _m)
{
	//计算特征点距离的最大值 
	std::vector< cv::DMatch > good_matches;

	float maxDist = 0;
	float minDist = FLT_MAX;
	const int SZ = _m.size();
	const float s = 0.5;
	for (int i = 0; i <SZ; i++)
	{
		const double d = _m[i].distance;
		if (d > maxDist) {
			maxDist = d;
		}
		if (d < minDist){
			minDist = d;
		}

	}

	//挑选好的匹配点
	for (int i = 0; i < SZ; i++){

		if (_m[i].distance <= maxDist * s){
			good_matches.push_back(_m[i]);
		}

	}
	return good_matches;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<cv::DMatch> TrafficSignProperty::ratioTest(std::vector<std::vector<cv::DMatch> > _matchePoints)
{
	const float minRatio = 0.67;
	
	std::vector< cv::DMatch > goodMatches;	;

	for (size_t i = 0; i<_matchePoints.size(); i++)
	{
		const cv::DMatch& bestMatch = _matchePoints[i][0];
		const cv::DMatch& betterMatch = _matchePoints[i][1];
		float distanceRatio = bestMatch.distance /betterMatch.distance;
		if (distanceRatio < minRatio)
		{
			goodMatches.push_back(bestMatch);
		}
	}

	return goodMatches;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
float TrafficSignProperty::getMeanDist(std::vector< cv::DMatch > _m)
{

	double sum = 0;
	float mean;
	for (std::vector<cv::DMatch>::iterator dite = _m.begin(); dite <_m.end(); dite++)
	{
		sum += dite->distance;
	}
	int matchSize = _m.size();
	
	if (matchSize>0) {
		mean = sum / matchSize;
	}else {
		mean = FLT_MAX;
	}
	return mean;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::cvt2gray()
{

	cvCvtColor(this->mImgBgra, this->mImgGray, CV_RGB2GRAY);
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignProperty::imgProcSift()
{

	

	cv::SiftFeatureDetector siftdtc(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold);
	cv::SiftDescriptorExtractor extractor;	

	siftdtc.detect(siftImg(), mKp);

#if 1
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;
	cv::Size Sz(siftImg()->width, siftImg()->height);
	cv::Mat dst = cv::Mat::zeros(Sz, CV_32FC1);
	cv::Mat dst_gray = cv::Mat::zeros(Sz, CV_8UC1);
	cv::Mat dst_bin = cv::Mat::zeros(Sz, CV_8UC1);

	IplImage *dst_img = (IplImage *)&IplImage(dst);
	IplImage *dst_img_gray = (IplImage *)&IplImage(dst_gray);
	IplImage *dst_img_bin = (IplImage *)&IplImage(dst_bin);

	cvCornerHarris(GrayImg(), dst_img, blockSize, apertureSize, k);

	double min,max;	
	cvMinMaxLoc(dst_img,&min,&max);
	
	float fk;
	float fb;
	double diff=max-min;
	if (diff!=0){
		fk = 255 / (max - min);
		fb = -fk*min;
	}else{
		fk = 255 / max;
		fb = 0;
	}
		
	cvConvertScale(dst_img, dst_img_gray,fk,fb);

	try
	{
			cvAdaptiveThreshold(dst_img_gray, dst_img_bin, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV);
	}
	catch (const cv::Exception& e)
	{
		std::cout << e.msg;
	}



	

	extractor.compute(siftImg(), mKp, mDescriptor);
#endif // 0
		
#if _DEBUG
	cv::drawKeypoints(this->mImgGray, mKp,this->mMatGrayTest);
#endif // _DEBUG
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool TrafficSignProperty::imgMatchFlannSift(std::vector<std::shared_ptr<TrafficSignProperty>> _tmps)
{
	cv::FlannBasedMatcher matcher;
	std::vector<cv::DMatch> matchePoints;
	cv::Mat img_match;	
	
	for each (auto t in _tmps){
			//if (this->getColor() == t->getColor()) 
			{
					matcher.match(this->mDescriptor,t->getDescriptor(),matchePoints,cv::Mat());
		
					drawMatches(
						siftImg(),
						getKeyPoint(),
						t->siftImg(),
						t->getKeyPoint(),
						matchePoints,
						img_match);	
			}
	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool TrafficSignProperty::imgMatchBfSift_CrossCheck(
	const int _i,
	std::vector<std::shared_ptr<TrafficSignProperty>> _tmps)
{	
	cv::Ptr<cv::DescriptorMatcher> bfmatcher(new cv::BFMatcher(cv::NORM_L2,true));//交叉验证
	std::vector<cv::DMatch> matchePoints;
	std::vector<cv::DMatch> good_matches;
	cv::Mat h_mat;
	std::vector<float> ls;

	std::shared_ptr<TrafficSignProperty>	score_min_sign;
	float									score_min = FLT_MAX;
	cv::Mat									score_min_match;

	for each (auto t in _tmps) {
		//if (this->getColor() == t->getColor()) 
		{
			bfmatcher->match(this->mDescriptor, t->getDescriptor(), matchePoints);
				
#if 1
			good_matches = getGoodDMatch(matchePoints);

		//	refineMatchesWithHomography(this->getKeyPoint(), t->getKeyPoint(),3, good_matches, h_mat);
						
			
#else
			good_matches = matchePoints;
#endif // 0

			float score = getMeanDist(good_matches);

			drawMatches(
				GrayImg(),
				getKeyPoint(),
				t->GrayImg(),
				t->getKeyPoint(),
				good_matches,
				mImgMatch,
				cvScalar(0, 255, 0));

			ls.push_back(score);

			if (score<score_min){
				score_min_sign = t;
				score_min_match = mImgMatch;
				score_min = score;
			}


		}
	}

	const std::string path = "TrafficSignImgMatch//";

	Base::FS_createDir(path);

	score_min_sign->saveImgMatch(score_min_match, path,std::to_string(_i)+ this->getFileName());

	return false;
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
bool TrafficSignProperty::imgMatchBfSift_RatioTest(std::vector<std::shared_ptr<TrafficSignProperty>> _tmps)
{
	const int K = 2;	
	std::vector<std::vector<cv::DMatch> > matchePoints;

	cv::Ptr<cv::DescriptorMatcher> bfmatcher(new cv::BFMatcher(cv::NORM_L2));//交叉验证
	
	std::vector<cv::DMatch> good_matches;
	cv::Mat img_match;

	for each (auto t in _tmps) {
		//if (this->getColor() == t->getColor()) 
		{
			bfmatcher->knnMatch(this->mDescriptor, t->getDescriptor(), matchePoints, K);
						
			drawMatches(
				siftImg(),
				getKeyPoint(),
				t->siftImg(),
				t->getKeyPoint(),
				good_matches,
				img_match,
				cvScalar(0, 255, 0));



		}
	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage * TrafficSignProperty::siftImg()
{

#if 1
	return this->mImgGray;
#else
	return this->mImgMask;
	//return this->mImgBgra;
#endif // 0
	

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage * TrafficSignProperty::GrayImg()
{
	return mImgGray;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool TrafficSignProperty::refineMatchesWithHomography
(
	const std::vector<cv::KeyPoint>& queryKeypoints,
	const std::vector<cv::KeyPoint>& trainKeypoints,
	float reprojectionThreshold,
	std::vector<cv::DMatch>& matches,
	cv::Mat& homography
)
{
	const int minNumberMatchesAllowed = 8;
	if (matches.size() < minNumberMatchesAllowed)
		return false;
	// Prepare data for cv::findHomography  
	std::vector<cv::Point2f> srcPoints(matches.size());
	std::vector<cv::Point2f> dstPoints(matches.size());
	for (size_t i = 0; i < matches.size(); i++)
	{
		srcPoints[i] = trainKeypoints[matches[i].trainIdx].pt;
		dstPoints[i] = queryKeypoints[matches[i].queryIdx].pt;
	}
	// Find homography matrix and get inliers mask  
	std::vector<unsigned char> inliersMask(srcPoints.size());
	homography = cv::findHomography(srcPoints,
		dstPoints,
		CV_FM_RANSAC,
		reprojectionThreshold,
		inliersMask);
	std::vector<cv::DMatch> inliers;
	for (size_t i = 0; i<inliersMask.size(); i++)
	{
		if (inliersMask[i])
			inliers.push_back(matches[i]);
	}
	matches.swap(inliers);  //释放空内存
	return matches.size() > minNumberMatchesAllowed;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/