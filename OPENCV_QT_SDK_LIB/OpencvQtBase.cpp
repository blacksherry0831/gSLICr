#include "OpencvQtBase.h"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
OpencvQtBase::OpencvQtBase(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
OpencvQtBase::~OpencvQtBase(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
QSharedPointer<QImage> OpencvQtBase::getPtrQImage(IplImage* const img)
{
	const uchar * imgData = (uchar *)img->imageData;

	QImage::Format f = getQFormat(img);

	QSharedPointer<QImage> image = QSharedPointer<QImage>(new QImage(imgData, img->width, img->height, f));//uses an existing memory buffer
	return image;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage* OpencvQtBase::CloneIplImage(const QImage* qImage)
{

	int width = qImage->width();
	int height = qImage->height();
	CvSize Size;
	Size.height = height;
	Size.width = width;
	IplImage *IplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 3);
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			QRgb rgb = qImage->pixel(x, y);
			cvSet2D(IplImageBuffer, y, x, CV_RGB(qRed(rgb), qGreen(rgb), qBlue(rgb)));
		}
	}
	return IplImageBuffer;

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
IplImage * OpencvQtBase::getIplImagePtr(const QImage * qImage)
{
	return nullptr;
}
/*-----------------------------------------*/
/**
*根据图片的通道数返回图片格式
*/
/*-----------------------------------------*/
QImage::Format OpencvQtBase::getQFormat(const IplImage * const _img)
{
	if (_img->depth==IPL_DEPTH_8U){

		if (_img->nChannels==1){
			return QImage::Format::Format_Grayscale8;
		}else if (_img->nChannels == 3)	{
			return QImage::Format::Format_RGB888;
		}else if (_img->nChannels == 4) {
			return QImage::Format::Format_ARGB32;
		}else if (_img->nChannels == 2) {
			return QImage::Format::Format_RGB16;
		}else{
			Q_ASSERT(0);
		}

	}
	else
	{
			Q_ASSERT(0);
	}
	return QImage::Format::Format_Invalid;
}

/*-----------------------------------------*/

//将IpImage转换成QIamge
void OpencvQtBase::CopyIplImage2QImage(const IplImage * const img,QImage * qImage)
{
	const int width = img->width;
	const int height = img->height;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int r, g, b;
			const int CH = img->nChannels;
			if (3 == CH)
			{
				b = (int)CV_IMAGE_ELEM(img, uchar, i, j * CH + 0);
				g = (int)CV_IMAGE_ELEM(img, uchar, i, j * CH + 1);
				r = (int)CV_IMAGE_ELEM(img, uchar, i, j * CH + 2);
			}
			else if (1 == CH)
			{
				b = (int)CV_IMAGE_ELEM(img, uchar, i, j);
				g = b;
				r = b;
			}
			else
			{
				Q_ASSERT(0);
			}
			qImage->setPixel(j, i, qRgb(r, g, b));
		}
	}
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void OpencvQtBase::CopyQImage2IplImage(IplImage * img, const QImage*  qImage)
{
	int width = qImage->width();
	int height = qImage->height();
	CvSize Size;
	Size.height = height;
	Size.width = width;
	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			QRgb rgb = qImage->pixel(x, y);
			
			CvScalar color_t=cvScalar(qBlue(rgb),qGreen(rgb),qRed(rgb),qAlpha(rgb));

			cvSet2D(img, y, x,color_t);
		}
	}
	
}

/*-----------------------------------------*/
/*
*@note 原文：https ://blog.csdn.net/u014472566/article/details/38894029 
*/
/*-----------------------------------------*/

//将IpImage克隆成QIamge 且QImage只为RGB格式
QImage * OpencvQtBase::CloneQImage(const IplImage * const img)
{
	const int width=img->width;
	const int height=img -> height;

	QImage *qmg = new QImage(width,height,QImage::Format_RGB32);
	CopyIplImage2QImage(img, qmg);
	return qmg;
}

/*-----------------------------------------*/

//将IpImage克隆成QIamge  根据IpImage的通道数转换成相应格式的QImage
QImage OpencvQtBase::CloneQImageEx(const IplImage * const img)
{
	const int width = img->width;
	const int height = img->height;

	const QImage::Format f=getQFormat(img);  //获取图片格式

	QImage qimg(width, height, f);  //初始化图片
	
	CopyIplImage2QImage(img, &qimg);  //将IpImage转换成QIamge

	return qimg;
}

/*-----------------------------------------*/

//将QImage转换成IpImage  (且只转换灰度化的IpImage)
void OpencvQtBase::InitImageHeader(IplImage* _img, const QImage* _qImage)
{

	const int width = _qImage->width();
	const int height = _qImage->height();
	Q_ASSERT(width%4==0);
	const CvSize Size=cvSize(width,height);			
	const QImage::Format f = _qImage->format();
	int Channel = 0;
	int Depth = 0;
	
	if (f == QImage::Format::Format_Grayscale8 ||
		f == QImage::Format::Format_Mono ||
		f == QImage::Format::Format_Indexed8)
	{
		Channel = 1;
		Depth = IPL_DEPTH_8U;
		Q_ASSERT(width == _qImage->bytesPerLine());
	}
	else
	{
		Q_ASSERT(0);
	}
	
	
	cvInitImageHeader(_img, Size, Depth, Channel);
	cvSetData(_img, (void *)( _qImage->bits()), _qImage->bytesPerLine());
	
}
