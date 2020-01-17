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
#include "QT_SDK_LIB/IPrintQ.hpp"
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
private:
	int mWidth;
	int mHeight;
private:
	AVFrame *pFrame;
	AVFrame *pFrameRGB32;
private:
	AVFormatContext *pFormatCtx;	
	AVPacket *pPacket;
	AVDictionary *pAVDic;
private:
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
private:
	SwsContexSafe    mSwsContextSafe;
private:
	int videoStreamIdx;
private:
	const std::string rtsp_url = "rtsp://192.168.0.11/stream1";
private:
	int mThreadRun;
	int mDecodeLoop;
public:
    void startPlay();
	void stopPaly();
public:
	static int Success2True(const int& _t);
	static int PrintConsole(std::string _log);
public:
	void initFFMPEG();
public:
	void emit_RGB32_QImage();
	int dbg_is_equal(const int _s1, const int _s2);
private:
	int IsLoopRun();
public:
	void SetScale(const int _w,const int _h);
private:
	void AllocAvFrame();
	void FreeAvFrame();
private:
	void initPacket();
	void initAVDictionary();
	void initAVFormatContext();
private:
	void openRtspStream();
	void findRtspStream();
	void findRtspCodec();
protected:
	void init_param();
protected:
	void initPlayModule();
	void stopPlayModule();
	void freePlayModule();
	void releasePlayModule();
protected:
	int run_video_decode();
protected:
    void run();

signals:
	void sig_1_frame_RGB32(QImage, QDateTime); //每获取到一帧图像 就发送此信号
	
};

#endif // VIDEOPLAYER_H
