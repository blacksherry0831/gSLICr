#include "SwsContexCore.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SwsContexCore::SwsContexCore(QObject *parent) : QObject(parent)
{
	InitSwsContext();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SwsContexCore::~SwsContexCore()
{
	FreeSwsContext();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexCore::SwsContextScale(
									AVFrame *pFrame,
									AVFrame *pFrameRGB32)
{
	QMutexLocker locker(&mSwsContextLock);

	if ((pFrame!=NULL) &&
		(pFrameRGB32!=NULL)){
						if (pImgConvertCtx != NULL) {
							sws_scale(pImgConvertCtx,
								(uint8_t const * const *)pFrame->data,
								pFrame->linesize, 0, pFrame->height,
								pFrameRGB32->data,
								pFrameRGB32->linesize);
						}
	}	
	
}
/*----------------------------------------------------------------*/
/**
*这里我们改成了 将解码后的YUV数据转换成RGB32
*/
/*----------------------------------------------------------------*/
void SwsContexCore::SetSwsContext(
	const int _w,
	const int _h,
	const int _ws,
	const int _hs)
{
	QMutexLocker locker(&mSwsContextLock);
	
	if ((_w>0)&&
		(_h>0)&&
		(_ws>0)&&
		(_hs>0)) {
			sws_freeContext(pImgConvertCtx);
			pImgConvertCtx = sws_getContext(
				_w,
				_h,
				AV_PIX_FMT_YUV420P,
				_ws,
				_hs,
				AV_PIX_FMT_RGB32,
				SWS_BICUBIC,
				NULL, NULL, NULL);
	}	

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexCore::InitSwsContext()
{
	QMutexLocker locker(&mSwsContextLock);
	pImgConvertCtx = NULL;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexCore::FreeSwsContext()
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
