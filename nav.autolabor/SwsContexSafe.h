#pragma once
#ifndef _SWS_CONTEX_SAFE_H_
#define _SWS_CONTEX_SAFE_H_
/*----------------------------------------------------------------*/
#include "SwsContexCore.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
class SwsContexSafe :public SwsContexCore
{
    Q_OBJECT

public:
	 explicit SwsContexSafe(QObject *parent = nullptr);
      ~SwsContexSafe();
private:
	int mWidth;
	int mHeight;
private:
	int mWidthScale;
	int mHeightScale;
private:
	void SetSrcSize(const int _w,const int _h);
	void SetDstSize(const int _w,const int _h);
private:
	void SetSetSwsContextInner();
public:	
	void GetDstSize(int& _w,int& _h) const;
	void SetSwsContextSrc(const int _w, const int _h);
	void SetSwsContextDst(const int _w_s, const int _h_s);
public:
	void SwsContextScaleEx(
		AVFrame *pFrame,
		AVFrame *pFrameRGB32);
};

#endif // SAVEPICTURE_H
