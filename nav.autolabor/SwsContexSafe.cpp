#include "SwsContexSafe.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SwsContexSafe::SwsContexSafe(QObject *parent) : QObject(parent)
{
	this->SetDstSize(0, 0);
	this->SetSrcSize(0, 0);
	InitSwsContext();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SwsContexSafe::~SwsContexSafe()
{
	FreeSwsContext();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SwsContextScale(
									AVFrame *pFrame,
									AVFrame *pFrameRGB32)
{
	QMutexLocker locker(&mSwsContextLock);
	if (pImgConvertCtx != NULL) {
		sws_scale(pImgConvertCtx,
			(uint8_t const * const *)pFrame->data,
			pFrame->linesize, 0, mHeight,
			pFrameRGB32->data,
			pFrameRGB32->linesize);
	}
	
}
/*----------------------------------------------------------------*/
/**
*这里我们改成了 将解码后的YUV数据转换成RGB32
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SetSwsContext()
{
	QMutexLocker locker(&mSwsContextLock);
	sws_freeContext(pImgConvertCtx);

	if ((0 < mWidth)&&
		(0 < mHeight)&&
		(0 < mWidthScale)&&
		(0 < mHeightScale)) {
		pImgConvertCtx = sws_getContext(mWidth, mHeight, AV_PIX_FMT_YUV420P,
			mWidthScale, mHeightScale, AV_PIX_FMT_RGB32,
			SWS_BICUBIC, NULL, NULL, NULL);
	}	

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::InitSwsContext()
{
	QMutexLocker locker(&mSwsContextLock);
	pImgConvertCtx = NULL;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::FreeSwsContext()
{
	QMutexLocker locker(&mSwsContextLock);
	sws_freeContext(pImgConvertCtx);
	pImgConvertCtx = NULL;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SetSrcSize(const int _w, const int _h)
{
	this->mWidth = _w;
	this->mHeight = _h;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SetDstSize(const int _w, const int _h)
{
	this->mWidthScale = _w;
	this->mHeightScale = _h;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::GetDstSize(int & _w, int & _h) const
{
	_w = this->mWidthScale;
	_h = this->mHeightScale;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SetSwsContextSrc(const int _w, const int _h)
{
	SetSrcSize(_w,_h);
	this->SetSwsContext();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SetSwsContextDst(const int _w_s, const int _h_s)
{
	SetDstSize(_w_s, _h_s);
	this->SetSwsContext();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
