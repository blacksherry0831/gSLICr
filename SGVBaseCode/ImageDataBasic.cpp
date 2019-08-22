#include "ImageDataBasic.h"
/*----------------------------------------------------------------*/
/**
*构造函数\n
*在做超像素运算之前，设置基本的参数
*
*@param  filename  图像的文件名
*@param  filesavepath   中间结果输出路径
*/
/*----------------------------------------------------------------*/
ImageDataBasic::ImageDataBasic(
	std::string filename,
	std::string filesavepath)
{
	this->initParam();
	assert(filename!="");
	SetImageDataBasic(filename,filesavepath);
	InitMemoryData(nullptr,filename,filesavepath);
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
ImageDataBasic::ImageDataBasic(
	IplImage* img,
	std::string filesavepath)
{
	std::string filename="MemoryIMG";
	this->initParam();
	SetImageDataBasic(filename,filesavepath);
	InitMemoryData(img,filename,filesavepath);
}
/*----------------------------------------------------------------*/
/**
*初始化成员变量
*
*
*/
/*----------------------------------------------------------------*/
void ImageDataBasic::initParam(void)
{	
	TRACE_FUNC();
	this->FileReadFullPath="";
	this->FileWritePath="";
	
	int sise_int=sizeof(int);
	int size_intp=sizeof(int*);
	
	this->srcCv_ImgBGRA=nullptr;
		
}
/*----------------------------------------------------------------*/
/**
*设置图像的输入、输出路径
*
* @param filename      文件名
* @param filesavepath  中间结果的输出路径
*
*/
/*----------------------------------------------------------------*/
void ImageDataBasic::SetImageDataBasic(std::string filename, std::string filesavepath){

	TRACE_FUNC();
	FileReadFullPath=filename;
	FileWritePath=filesavepath;
	
}
 /*----------------------------------------------------------------*/
 /**
 *析构函数释放分配的内存
 *
 *
 */
 /*----------------------------------------------------------------*/
ImageDataBasic::~ImageDataBasic()
{
	this->ReleaseMemory();
}
/*----------------------------------------------------------------*/
/**
*清理中间过程分配的内存
*
*
*/
/*----------------------------------------------------------------*/

void ImageDataBasic::ReleaseMemory(void)
{		
	cvReleaseImage(&srcCv_ImgBGRA); 	
}
/*----------------------------------------------------------------*/
 /**
 *初始化已分配的内存
 *
*@param filename  图像文件名
*@param filesavepath 图像保存路径
 */
 /*----------------------------------------------------------------*/
 void ImageDataBasic::InitMemoryData(
	 IplImage* img,
	 std::string filename,
	 std::string filesavepath)
 {  
	 TRACE_FUNC();
	 ReleaseMemory();
	 /*************************************************************************************************/ 
	
	 IplImage *src_img_t;
	if (img==nullptr){
		 printf("cvLoadImage: %s \n",filename.c_str());
		 src_img_t=cvLoadImage(filename.c_str(),CV_LOAD_IMAGE_UNCHANGED); 
		 if (src_img_t==NULL){
			printf("cvLoadImage: Fail %s \n",filename.c_str());
		 }
	}else{
		printf("cvCreateImage: %s \n");
		src_img_t=cvCreateImage(cvGetSize(img),img->depth,4);
		if (img->nChannels==4){
			 cvCopyImage(img,src_img_t);
		}else if (img->nChannels==3){
			cvCvtColor(img,src_img_t,CV_BGR2BGRA);
		}
		else if (img->nChannels==1){
			cvCvtColor(img,src_img_t,CV_GRAY2BGRA);
		}else{
			ASSERT(0); 
		}
	   
	}	
	 ConvertImg2Eighth4Ch(&src_img_t);

	 srcCv_ImgBGRA=cvCloneImage(src_img_t);

	 ConvertImg3ChTo4Ch(&srcCv_ImgBGRA);

	 cvReleaseImage(&src_img_t);
	 /********************************************************************/	 
 }
/*-------------------------------------------------------------------------------------------*/
/**
*将图像转换到8的整数倍4通道
*@param [in][out] src
*/
/*-------------------------------------------------------------------------------------------*/
void ImageDataBasic::ConvertImg2Eighth4Ch(IplImage **src)
{
	TRACE_FUNC();
	CvSize SizeOld = cvGetSize(*src);
	CvSize SizeNew = cvGetSize(*src);
	int depth = (*src)->depth;
	int nChannels = (*src)->nChannels;

	ASSERT(src != nullptr);
	ASSERT(*src != nullptr);
	if (SizeOld.width % 8 != 0) {
		SizeNew.width = SizeOld.width - SizeOld.width % 8 + 8;
	}
	if (SizeOld.height % 8 != 0) {
		SizeNew.height = SizeOld.height - SizeOld.height % 8 + 8;
	}
	if ((SizeOld.width == SizeNew.width)
		&& (SizeOld.height == SizeNew.height)) {
		return;
	}
	IplImage *temp = cvCloneImage(*src);
	cvReleaseImage(src);
	*src = cvCreateImage(SizeNew, depth, nChannels);
	cvResize(temp, *src);
	cvReleaseImage(&temp);
#if 1
	ConvertImg3ChTo4Ch(src);
	//	cvSaveImage("A.png",*src);
#endif

}
/*-------------------------------------------------------------------------------------------*/
/**
*将图像从三通道转换到四通道
*@param [in][out] src 三通道的图像
*/
/*-------------------------------------------------------------------------------------------*/
void ImageDataBasic::ConvertImg3ChTo4Ch(IplImage **src)
{
	TRACE_FUNC();
	CvSize SizeOld = cvGetSize(*src);
	int depth = (*src)->depth;
	int nChannels = (*src)->nChannels;

	ASSERT(src != nullptr);
	ASSERT(*src != nullptr);

	if (nChannels == 3) {
		IplImage *temp = cvCloneImage(*src);
		cvReleaseImage(src);
		*src = cvCreateImage(SizeOld, depth, 4);
		cvCvtColor(temp, *src, CV_BGR2BGRA);
		cvReleaseImage(&temp);

	}

}
/*-------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*-------------------------------------------------------------------------------------------*/
IplImage* ImageDataBasic::GetIplImagePtr()
{
	return this->srcCv_ImgBGRA;
}
/*-------------------------------------------------------------------------------------------*/
/**
*
*
*/
/*-------------------------------------------------------------------------------------------*/