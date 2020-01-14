#pragma once
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
/*----------------------------------------------------------------*/
#include <QThread>
#include <QImage>
#include <QDebug>
#include <QMutex>
#include <QDateTime>
/*----------------------------------------------------------------*/
#include <stdio.h>
#include <iostream>
/*----------------------------------------------------------------*/
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
}
/*----------------------------------------------------------------*/
#include "SwsContexSafe.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/

class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    explicit VideoPlayer();
    ~VideoPlayer();

    void startPlay();

    void stopPaly();

	void initPlayModule();
	void freePlayModule();
public:
	void emit_RGB32_QImage();
	int dbg_is_equal(const int _s1, const int _s2);
private:
	int mThreadRun;
private:
	int mWidth;
	int mHeight;
public:
	void SetScale(const int _w,const int _h);
private:
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrame;
	AVFrame *pFrameRGB32;
	AVPacket *pPacket;
	SwsContexSafe    mSwsContextSafe;
	AVDictionary *pAVDic;
private:
	int videoStreamIdx;
private:
	 const std::string rtsp_url = "rtsp://192.168.0.11/stream1";
private:
	void initAVDictionary();
protected:
	void init_param();
protected:
	int run_video_decode();
protected:
    void run();

signals:
	void sig_1_frame_RGB32(QImage, QDateTime); //每获取到一帧图像 就发送此信号
	
};

#endif // VIDEOPLAYER_H
