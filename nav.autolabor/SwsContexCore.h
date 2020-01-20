#pragma once
#ifndef _SWS_CONTEX_CORE_H_
#define _SWS_CONTEX_CORE_H_
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
class SwsContexCore :public QObject
{
    Q_OBJECT

public:
	 explicit SwsContexCore(QObject *parent = nullptr);
      ~SwsContexCore();
private:
	QMutex mSwsContextLock;
	struct SwsContext *pImgConvertCtx;
private:
	 void InitSwsContext();
	 void FreeSwsContext();
protected:
	void SwsContextScale(
		AVFrame *pFrame,
		AVFrame *pFrameRGB32);

	void SetSwsContext(
		const int _w,
		const int _h,
		const int _ws,
		const int _hs);

};

#endif // SAVEPICTURE_H
