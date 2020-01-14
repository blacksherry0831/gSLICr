#include "videoplayer.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
VideoPlayer::VideoPlayer()
{
	videoStreamIdx = -1;
	this->init_param();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
VideoPlayer::~VideoPlayer()
{
	freePlayModule();
	mThreadRun = 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::startPlay()
{
	mThreadRun = 1;
    //调用 QThread 的start函数 将会自动执行下面的run函数 run函数是一个新的线程
    this->start();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initAVDictionary()
{
	pAVDic=NULL;
	char option_key[] = "rtsp_transport";
	char option_value[] = "tcp";
	av_dict_set(&pAVDic, option_key, option_value, 0);
	char option_key2[] = "max_delay";
	char option_value2[] = "100";
	av_dict_set(&pAVDic, option_key2, option_value2, 0);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::init_param()
{
	pFormatCtx=NULL;
	pCodecCtx = NULL;
	pCodec = NULL;
	pFrame = NULL;
	pFrameRGB32 = NULL;
	pPacket = NULL;
	
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::initPlayModule()
{
	initAVDictionary();

	//分配一个avformatcontext
	pFormatCtx = avformat_alloc_context();  //FFMEG的所有操作均要通过avformatcontext进行
	
	pFrame = av_frame_alloc();	
	pFrameRGB32 = av_frame_alloc();
	
	pPacket = av_packet_alloc(); //分配一个packet
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::freePlayModule()
{
	av_packet_free(&pPacket);
	av_frame_free(&pFrame);
	av_frame_free(&pFrameRGB32);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::run_video_decode()
{
	
	if (av_read_frame(pFormatCtx, pPacket) < 0)   //读取视频的一帧，并保存值packet中
	{
		return 0; //这里认为视频读取完了
	}

	if (pPacket->stream_index == videoStreamIdx) {
		int  got_picture;
		const int ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, pPacket);   //视频解码

		if (ret < 0) {
			printf("decode error.\n");
			return 0;
		}

		//视频解码后的数据格式为YUV420，这里将其转为rgb数据格式，利于保存为图片
		if (got_picture) {
			this->emit_RGB32_QImage();
		}
	}

	av_packet_unref(pPacket); //释放资源,否则内存会一直上升

	return 1;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::run()
{
    
	this->initPlayModule();
	
    avformat_network_init();   //初始化FFmpeg网络模块
    av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
	
    //打开视频连接
    if (avformat_open_input(&pFormatCtx, rtsp_url.data(), NULL, &pAVDic) != 0) {
        printf("can't open the file. \n");
        return;
    }

    //查数据流
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        printf("Could't find stream infomation.\n");
        return;
    }

    

    //循环查找视频中包含的流信息，直到找到视频类型的流
    //便将其记录下来 保存到videoStream变量中
    //这里我们现在只处理视频流  音频流先不管他
    for (int i = 0; (unsigned)i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStreamIdx = i;
        }
    }

    //如果videoStream为-1 说明没有找到视频流
    if (videoStreamIdx == -1) {
        printf("Didn't find a video stream.\n");
        return;
    }

    //查找解码器
    pCodecCtx = pFormatCtx->streams[videoStreamIdx]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    ///2017.8.9---lizhen
    pCodecCtx->bit_rate =0;   //初始化为0
    pCodecCtx->time_base.num=1;  //下面两行：一秒钟25帧
    pCodecCtx->time_base.den=10;
    pCodecCtx->frame_number=1;  //每包一个视频帧

    //未找到编码器
    if (pCodec == NULL) {
        printf("Codec not found.\n");
        return;
    }

    //打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        printf("Could not open codec.\n");
        return;
    }

    

	mWidth	= 	pCodecCtx->width;
	mHeight	= 	pCodecCtx->height;
	const int y_size = mWidth * mHeight;
	av_new_packet(pPacket, y_size); //分配packet的数
  
	mSwsContextSafe.SetSwsContextSrc(mWidth, mHeight);

			while (mThreadRun)
			{
				//视频流读取
				if (0 == run_video_decode()) {
					break;
				}
			}

	freePlayModule();

}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::stopPaly()
{
	mThreadRun = 0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::emit_RGB32_QImage()
{
		int WidthScale =0;
		int HeightScale =0;

		mSwsContextSafe.GetDstSize(WidthScale, HeightScale);

		QImage q_img(WidthScale, HeightScale, QImage::Format_RGB32);
		
		Q_ASSERT(dbg_is_equal(q_img.byteCount(),avpicture_get_size(AV_PIX_FMT_RGB32, WidthScale, HeightScale)));
		
		avpicture_fill((AVPicture *)pFrameRGB32, q_img.bits(), AV_PIX_FMT_RGB32, WidthScale, HeightScale);
			
		mSwsContextSafe.SwsContextScale(pFrame, pFrameRGB32);

		//把这个RGB数据 用QImage加载
		

		emit sig_1_frame_RGB32(q_img,QDateTime::currentDateTime() );  //发送信号	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int VideoPlayer::dbg_is_equal(const int _s1, const int _s2)
{
	return _s1==_s2;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void VideoPlayer::SetScale(const int _w, const int _h)
{
	mSwsContextSafe.SetSwsContextDst(_w, _h);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/