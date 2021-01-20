#include "TrafficSignPropertyHu.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignPropertyHu::TrafficSignPropertyHu() : TrafficSignPropertyBase()
{
	mContours		=	nullptr;
	mMemStorage		=	cvCreateMemStorage(0);
	mHuSimilar		=	0;
	mRotationAngle = 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignPropertyHu::~TrafficSignPropertyHu(void)
{
	cvClearSeq(mContours);
	cvReleaseMemStorage(&mMemStorage);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyHu::CloneSeq(const CvSeq * _seq)
{
	mContours = cvCloneSeq(_seq,mMemStorage);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvSeq * TrafficSignPropertyHu::getSeq()
{
	return mContours;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
double TrafficSignPropertyHu::getHuSimilar() const
{
	return this->mHuSimilar;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignPropertyHu::getHuSimilarStr() const
{
	return std::to_string(this->mHuSimilar);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyHu::saveImgBinary(std::string _path)
{
	if (mImgMask!=0){
			const std::string ffp = _path + this->mFileName;
			cvSaveImage(ffp.c_str(), mImgMask);
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyHu::saveImageTemplete(std::string _p)
{
	cvSaveImage(_p.c_str(), mImgBgra);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignPropertyHu::imgProcHu()
{
	CvMoments moments;
	CvHuMoments huMoments;
	cvMoments(mImgMask, &moments, 1);
	cvGetHuMoments(&moments, &huMoments);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::shared_ptr<TrafficSignPropertyHu>
TrafficSignPropertyHu::MatchHuProperty(std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps)
{
	std::shared_ptr<TrafficSignPropertyHu>  match_t_min;
	std::vector<float>	match_v;
	float	match_v_min=FLT_MAX;
	for each( auto t in _tmps)
	{

		//if (t->getColor()==this->getColor())
		{
#if 1
			const double m=this->matchShapesSeq(t->getSeq());
#endif // 0
#if 0
			const double m = this->matchShapesImg(t.get());
#endif // 0
			match_v.push_back(m);

			if (m<match_v_min){
				match_v_min = m;
				match_t_min = t;
			}

		}
		
	}
	return match_t_min;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
float 
TrafficSignPropertyHu::MatchHuPropertySimilar(
	std::shared_ptr<TrafficSignPropertyHu>& _tmp_out,
	std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps)
{

	std::vector<float>	match_v;
	float	match_v_min = FLT_MAX;
	for each(auto t in _tmps)
	{

		//if (t->getColor()==this->getColor())
		{
#if 1
			const double m = this->matchShapesSeq(t->getSeq());
#endif // 0
#if 0
			const double m = this->matchShapesImg(t.get());
#endif // 0
			match_v.push_back(m);

			if (m<match_v_min) {
				match_v_min = m;
				_tmp_out = t;
			}

		}

	}

	return match_v_min;
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::shared_ptr<TrafficSignPropertyHu> 
TrafficSignPropertyHu::MatchHuProperty2(std::vector<std::shared_ptr<TrafficSignPropertyHu>> _tmps)
{
		
	std::map<std::string, double> match;

	for each(auto t in _tmps)
	{

		std::string prop = t->getPathName();
		const double m = this->matchShapesSeq(t->getSeq());

		auto  search = match.find(prop);
		
		if (search != match.end()) {
			match[prop] += m;
		}else {
			match[prop] = m;
		}
			
	}

	
	float	match_v_min = FLT_MAX;
	 std::string match_tp_min;
	for each (auto var in match)
	{
		const std::string	tp  = var.first;
		const double		tpv = var.second;

		if (tpv< match_v_min)
		{
			match_v_min = tpv;
			match_tp_min = tp;
		}

	}
	

	std::shared_ptr<TrafficSignPropertyHu>  match_t_min;
	
	for each(auto t in _tmps)
	{
		if (match_tp_min==t->getPathName()){
			if (this->getColor()==t->getColor())
			{
				match_t_min = t;
			}
		}

	}
	
	return match_t_min;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
double TrafficSignPropertyHu::matchShapesSeq(const CvSeq * _seq)
{
	this->mHuSimilar=cvMatchShapes(this->mContours, _seq, CV_CONTOURS_MATCH_I1);
	return this->mHuSimilar;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
double TrafficSignPropertyHu::matchShapesImg(TrafficSignPropertyHu * _tsph)
{
	this->mHuSimilar = cvMatchShapes(this->BinaryImg(), _tsph->BinaryImg(), CV_CONTOURS_MATCH_I2);
	return this->mHuSimilar;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
 void TrafficSignPropertyHu::MatchOutPut(
	 const int									_si,
	 std::shared_ptr<TrafficSignPropertyHu>		_s, 
	 std::shared_ptr<TrafficSignPropertyHu>		_t)
{
#if 1
	 IplImage  * s_img=_s->ColorBgraImg();
	 IplImage  * t_img = _t->ColorBgraImg();
#else
	 IplImage  * s_img = _s->BinaryImg();
	 IplImage  * t_img = _t->BinaryImg();
#endif // 0
	 
	 const int W = s_img->width + t_img->width;
	 const int H = std::max(s_img->height,t_img->height);

	 CvRect s_rect = cvRect(0, 0, s_img->width, s_img->height);
	 CvRect t_rect = cvRect(s_img->width, 0, t_img->width, t_img->height);

	 cv::Mat mat(cv::Size(W,H), CV_8UC4);	// CV_8UC1

	 IplImage* cb_img=& IplImage(mat);
	
	 _s->DrawArrow(_t->getPathName());
	 
	 //copyImgRect(s_img, cb_img,_s->BinaryImg(), s_rect);
	 //copyImgRect(t_img, cb_img,_t->BinaryImg(), t_rect);

	 copyImgRect(s_img, cb_img, nullptr, s_rect);
	 copyImgRect(t_img, cb_img, nullptr, t_rect);

	 const std::string path = "TrafficSignMatchHu//";

	 Base::FS_createDir(path);

	 std::string ffn;
	 ffn.append(_t->getColor()).append(".").
		 append(_s->getAreaStr()).append(".").
		 append(_s->getHuSimilarStr()).append(".").
		 append(_t->getPathName()).append(".").
		 append(std::to_string(_si)).append(".").
		 append(_s->getFileName());

	 std::string  fullpath = path + ffn;

	 cv::imwrite(fullpath.c_str(),mat);
	 	 
}
 /*-----------------------------------------*/
 /**
 *
 */
 /*-----------------------------------------*/
 void TrafficSignPropertyHu::copyImgRect(IplImage * _src, IplImage * _dst, IplImage * _mask, CvRect _r)
 {
	 cvSetImageROI(_dst, _r);
	 cvCopy(_src, _dst,_mask);
	 cvResetImageROI(_dst);
 }
 /*-----------------------------------------*/
 /**
 *
 */
 /*-----------------------------------------*/
 double TrafficSignPropertyHu::getTempleteAngle(std::shared_ptr<TrafficSignPropertyHu> _t)
 {
	 
	 cv::Mat roi(this->BinaryImg());
	 cv::Mat tmp(_t->BinaryImg());

	 std::vector<int> SZ;
	 SZ.push_back(roi.cols);
	 SZ.push_back(roi.rows);
	 SZ.push_back(tmp.cols);
	 SZ.push_back(tmp.rows);
	 	
	 int rc_max = getIntMax(SZ);

	 cv::Mat roi_square= resizeMat(roi,rc_max);
	 	 
	 cv::Mat roi_square_contours = roi_square.clone();

	 std::vector<std::vector<cv::Point>> roiContours;
	 
	 cv::findContours(roi_square_contours, roiContours, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

	 mRotationAngle = calcRotateAngle1(roi_square,tmp,roiContours);

	 return mRotationAngle;
 }
/*-----------------------------------------*/
/**
*@brief 四向模板匹配法  参数：二值化后的测试图片和二值化后的模板图片
*/
/*-----------------------------------------*/
 double TrafficSignPropertyHu::calcRotateAngle1(
	 cv::Mat & roi,
	 cv::Mat & tmpl,
	 std::vector<std::vector<cv::Point>>& roiContours)
 {
	 cv::RotatedRect minRect = minAreaRect(roiContours[0]);
	 double baseAngle = minRect.angle;

	 cv::Mat  image[4];
	 cv::Mat  imgret[4];

	 std::vector<double>  angles;
	 std::vector<double>  similars;
	 	 
	 double		similar=0;
	 double		similar_max = 0;
	 int		similar_idx = 0;

	 const int match_method = cv::TM_CCOEFF_NORMED;

	 for (int i = 0; i < 4; ++i) {		
		 const double angle = baseAngle + 90 * i;
		 angles.push_back(angle);
		 Rotate(roi, image[i], angle);


		 matchTemplate(tmpl,image[i] , imgret[i], match_method);

		 double minVal = -1;
		 double maxVal;
		 cv::Point minLoc;
		 cv::Point maxLoc;
		 cv::Point matchLoc;
		 minMaxLoc(imgret[i], &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

		 matchLoc = minLoc;
		 		
		 if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED){
			 matchLoc = minLoc;
			 similar = 1 - minVal;
		 } else {
			 matchLoc = maxLoc;
			 similar = maxVal;
		 }
		 		 
		 similars.push_back(similar);
		 
		 if (similar>similar_max){
			 similar_idx = i;
			 similar_max = similar;

		 }
		 
	 }
	 
	 return angles.at(similar_idx);
 }
 /*-----------------------------------------*/
 /**
 *
 */
 /*-----------------------------------------*/
  void TrafficSignPropertyHu::Rotate(
	  const cv::Mat &srcImage,
	  cv::Mat &destImage,
	  double angle)
 {
	 cv::Point2f center(srcImage.cols / 2, srcImage.rows / 2);//中心
	 cv::Mat M = getRotationMatrix2D(center, angle, 1);//计算旋转的仿射变换矩阵 
	 warpAffine(srcImage, destImage, M, cv::Size(srcImage.cols, srcImage.rows));//仿射变换  
	 circle(destImage, center, 2, cv::Scalar(255, 0, 0));
 }
  /*-----------------------------------------*/
  /**
  *
  */
  /*-----------------------------------------*/
  void TrafficSignPropertyHu::resize2square(cv::Mat & _src, cv::Mat & _square)
  {
	 
	  const int rc= std::max(_src.rows, _src.cols);
	  const int T = _src.type();
	  cv::Size  SZ(rc, rc);

	  cv::Rect s_roi((rc - _src.cols) / 2, (rc - _src.rows) / 2, _src.cols, _src.rows);
	 
	  _square = cv::Mat::zeros(SZ, T);
	 
	  _src.copyTo(_square(s_roi));


  }
  /*-----------------------------------------*/
  /**
  *
  */
  /*-----------------------------------------*/
  cv::Mat TrafficSignPropertyHu::resizeMat(cv::Mat _src, int _rc)
  {
	  
	  const int T = _src.type();
	  cv::Size  SZ(_rc, _rc);
	  cv::Rect  s_roi((_rc - _src.cols) / 2, (_rc - _src.rows) / 2, _src.cols, _src.rows);
	  cv::Mat   matmax = cv::Mat::zeros(SZ, T);

	  _src.copyTo(matmax(s_roi));

	  return matmax;

  }
  /*-----------------------------------------*/
  /**
  *
  */
  /*-----------------------------------------*/
  void TrafficSignPropertyHu::DrawArrow(std:: string _type)
  {
		cv::Mat  mat(this->ColorBgraImg());
		const int cols = mat.cols;
		const int rows = mat.rows;
		const int R = std::min(cols,rows)*2/3;
		
		cv::Point center = cv::Point(cols / 2, rows / 2);
		
		cv::Scalar color = cv::Scalar(0, 0, 0, 255);
		const int thickness = 2;

		if (_type == "Forward") {
			const double A = (mRotationAngle - 90) * CV_PI / 180;
			cv::arrowedLine(mat, center, cv::Point(center.x +R*cos(A), center.y+ R*sin(A)), color, thickness);
		}

		if (_type == "Left") {
			const double A = (mRotationAngle-180)* CV_PI / 180;
			cv::arrowedLine(mat, center, cv::Point(center.x + R*cos(A), center.y + R*sin(A)), color, thickness);
		}

		if (_type == "Right") {
			const double A = (mRotationAngle) * CV_PI / 180;
			cv::arrowedLine(mat, center, cv::Point(center.x + R*cos(A), center.y + R*sin(A)), color, thickness);
		}
		
  }
  /*-----------------------------------------*/
  /**
  *
  */
  /*-----------------------------------------*/
  int TrafficSignPropertyHu::getIntMax(std::vector<int> _data)
  {
	  std::vector<int>::iterator itMax = std::max_element(_data.begin(), _data.end());
	   return  *itMax;
  }
  /*-----------------------------------------*/
  /**
  *
  */
  /*-----------------------------------------*/