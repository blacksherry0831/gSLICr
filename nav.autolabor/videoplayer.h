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
	VideoPlayer(const std::string _url);
    ~VideoPlayer();
private:
	int Width();
	int Height();
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
	 std::string rtsp_url;
private:
	int mThreadRun;
	int mDecodeLoop;
private:
	int mFpsOut;
	int mFrameCount;
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
	int frameInterval();
	int dbg_is_equal(const int _s1, const int _s2);
private:
	int IsLoopRun();
public:
	void SetScale(const int _w,const int _h);
	void SetRtspUrl(std::string _url);
	double  getFpsRaw();
private:
	void AllocAvFrame();
	void FreeAvFrame();
private:
	void initPacket();
	void initAVDictionary();
	void initAVFormatContext();
private:
	int  openRtspStream();
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
public slots:
	void SetOutputFps(const int _fps);
	int  IncFrameIsOut();
	int  fpsOut1();
	int  fpsOut5();
	int  fpsOut10();
	int  fpsOut25();
/*************************************************************************/
signals:
	
	void sig_1_frame_RGB32_ref(QSharedPointer<QImage>, const QDateTime);
	
};

#endif // VIDEOPLAYER_H
