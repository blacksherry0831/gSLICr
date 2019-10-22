#include "MemcpyCv_gSLICr.hpp"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
MemcpyCv_gSLICr::MemcpyCv_gSLICr(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
MemcpyCv_gSLICr::~MemcpyCv_gSLICr(void)
{

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGR_BGR(const gSLICr::UChar4Image* inimg, cv::Mat& outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const gSLICr::Vector4u* inimg_ptr = inimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < inimg->noDims.y; y++)
		for (int x = 0; x < inimg->noDims.x; x++)
		{
			int idx = x + y * inimg->noDims.x;
			outimg.at<cv::Vec3b>(y, x)[0] = inimg_ptr[idx].b;
			outimg.at<cv::Vec3b>(y, x)[1] = inimg_ptr[idx].g;
			outimg.at<cv::Vec3b>(y, x)[2] = inimg_ptr[idx].r;
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_BGRA(const gSLICr::UChar4Image* inimg, cv::Mat& outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const gSLICr::Vector4u* inimg_ptr = inimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < inimg->noDims.y; y++)
		for (int x = 0; x < inimg->noDims.x; x++)
		{
			int idx = x + y * inimg->noDims.x;
			outimg.at<cv::Vec4b>(y, x)[0] = inimg_ptr[idx].b;
			outimg.at<cv::Vec4b>(y, x)[1] = inimg_ptr[idx].g;
			outimg.at<cv::Vec4b>(y, x)[2] = inimg_ptr[idx].r;
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_MatBGRA_to_4image_BGR(const cv::Mat& inimg, gSLICr::UChar4Image* outimg)
{
	TimeMeasure tm("load_MatBGRA_to_4image_BGR");
	gSLICr::Vector4u* outimg_ptr = outimg->GetData(MEMORYDEVICE_CPU);

	for (int y = 0; y < outimg->noDims.y; y++)
		for (int x = 0; x < outimg->noDims.x; x++)
		{
			int idx = x + y * outimg->noDims.x;
			outimg_ptr[idx].b = inimg.at<cv::Vec4b>(y, x)[0];
			outimg_ptr[idx].g = inimg.at<cv::Vec4b>(y, x)[1];
			outimg_ptr[idx].r = inimg.at<cv::Vec4b>(y, x)[2];
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_IplimageBGRA_to_4image_BGR(const IplImage* _inimg, gSLICr::UChar4Image * _outimg)
{
	TimeMeasure tm("load_IplimageBGRA_to_4image_BGR");
	gSLICr::Vector4u* outimg_ptr = _outimg->GetData(MEMORYDEVICE_CPU);
	const int nChs = _inimg->nChannels;
	for (int y = 0; y < _outimg->noDims.y; y++)
		for (int x = 0; x < _outimg->noDims.x; x++)
		{
			const int idx = x + y * _outimg->noDims.x;
			outimg_ptr[idx].b = CV_IMAGE_ELEM(_inimg, unsigned char, y, x * nChs + 0);
			outimg_ptr[idx].g = CV_IMAGE_ELEM(_inimg, unsigned char, y, x * nChs + 1);
			outimg_ptr[idx].r = CV_IMAGE_ELEM(_inimg, unsigned char, y, x * nChs + 2);
		}
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_Iplimage4u_to_4image_4u(const IplImage * _inimg, gSLICr::UChar4Image * _outimg)
{
	TimeMeasure tm("load_Iplimage4u_to_4image_4u");
	gSLICr::Vector4u*	outimg_ptr	= _outimg->GetData(MEMORYDEVICE_CPU);
	char*				inimg_ptr = _inimg->imageData;
	const int src_SZ = _inimg->imageSize;
	const int dst_SZ = _outimg->dataSize*4;
	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr,inimg_ptr,src_SZ);
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(
	const gSLICr::UChar4Image * _inimg,
	cv::Mat & _outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const gSLICr::Vector4u* inimg_ptr = _inimg->GetData(MEMORYDEVICE_CPU);
	uchar*				outimg_ptr = _outimg.ptr<uchar>(0);
	const int src_SZ = _inimg->dataSize*4;
	const int dst_SZ = _outimg.size().area()*_outimg.channels();
	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr, inimg_ptr, src_SZ);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(const gSLICr::FloatImage * _inimg, cv::Mat & _outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR.float");
	const float* inimg_ptr = _inimg->GetData(MEMORYDEVICE_CPU);
	float*				outimg_ptr = _outimg.ptr<float>(0);
	const int FloatSize = sizeof(float);
	const int src_SZ = _inimg->dataSize * sizeof(float);
	
	const int DEPTH = _outimg.depth();
	
	int FloatSizeCv= 0;

	if (DEPTH==CV_32F){
		FloatSizeCv = FloatSize;
	}
	
	const int dst_SZ = _outimg.size().area()*_outimg.channels()*FloatSizeCv;

	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr, inimg_ptr, src_SZ);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::cpy_svg_2_img(cv::Mat _img, cv::Mat _svg, cv::Mat _result)
{
	assert(_img.cols == _svg.cols);
	assert(_img.rows == _svg.rows);

	const int*	img_ptr_t = _img.ptr<int>(0);
	const int*	svg_ptr_t = _svg.ptr<int>(0);
	int*	result_ptr_t = _result.ptr<int>(0);
	
	for (int ci = 0; ci < _img.cols; ci++){
		for (int ri = 0; ri <_img.rows; ri++){

			const int idx = ci + ri*_img.cols;
			const int pixel_color = img_ptr_t[idx];
			if (ci%2==0 && ri%2==0 && pixel_color!=0xffffffff)	{
				  result_ptr_t[idx] = svg_ptr_t[idx];
			}else{
				result_ptr_t[idx] = img_ptr_t[idx];
			}
			
		}
	}
	
}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
void MemcpyCv_gSLICr::load_4Image_to_MatBGRA_4u(const gSLICr::IntImage * _inimg, cv::Mat & _outimg)
{
	TimeMeasure tm("load_4Image_to_MatBGR_BGR");
	const int* inimg_ptr = _inimg->GetData(MEMORYDEVICE_CPU);
	uchar*				outimg_ptr = _outimg.ptr<uchar>(0);
	const int src_SZ = _inimg->dataSize * sizeof(int);

	const int dst_SZ = _outimg.size().area()*_outimg.channels()*_outimg.depth();
	
	ASSERT(src_SZ == dst_SZ);
	memcpy(outimg_ptr, inimg_ptr, src_SZ);

}
/*-------------------------------------------------------------------------*/
/**
*
*/
/*-------------------------------------------------------------------------*/
