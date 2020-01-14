#pragma once
#ifndef _SWS_CONTEX_SAFE_H_
#define _SWS_CONTEX_SAFE_H_
/*----------------------------------------------------------------*/
#include <QThread>
#include <QImage>
#include <queue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QQueue>
#include <QMutex>
/*----------------------------------------------------------------*/
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
class SwsContexSafe :public QObject
{
    Q_OBJECT

public:
	 explicit SwsContexSafe(QObject *parent = nullptr);
      ~SwsContexSafe();
public:
	void SwsContextScale(
		AVFrame *pFrame,
		AVFrame *pFrameRGB32);

	 void SetSwsContext();
	 void InitSwsContext();
	 void FreeSwsContext();
private:
	QMutex mSwsContextLock;
	struct SwsContext *pImgConvertCtx;
private:
	int mWidth;
	int mHeight;
private:
	int mWidthScale;
	int mHeightScale;
private:
	void SetSrcSize(const int _w,const int _h);
	void SetDstSize(const int _w,const int _h);
public:
	
	void GetDstSize(int& _w,int& _h) const;
	void SetSwsContextSrc(const int _w, const int _h);
	void SetSwsContextDst(const int _w_s, const int _h_s);

};

#endif // SAVEPICTURE_H
