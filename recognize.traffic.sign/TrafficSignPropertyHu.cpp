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

	 cv::Mat mat(cv::Size(W,H), CV_8UC4);
	// cv::Mat mat(cv::Size(W, H), CV_8UC1);

	 IplImage* cb_img=& IplImage(mat);
	
	 copyImgRect(s_img, cb_img,_s->BinaryImg(), s_rect);
	 copyImgRect(t_img, cb_img,_t->BinaryImg(), t_rect);

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