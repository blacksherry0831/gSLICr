#include "SwsContexSafe.h"
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SwsContexSafe::SwsContexSafe(QObject *parent) :SwsContexCore(parent)
{
	this->SetDstSize(0, 0);
	this->SetSrcSize(0, 0);
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
SwsContexSafe::~SwsContexSafe()
{

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
void SwsContexSafe::SetSetSwsContextInner()
{
	this->SetSwsContext(this->mWidth, this->mHeight, this->mWidthScale, this->mHeightScale);
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
		SetSrcSize(_w, _h);
		SetSetSwsContextInner();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SetSwsContextDst(const int _w_s, const int _h_s)
{
		SetDstSize(_w_s, _h_s);
		SetSetSwsContextInner();
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void SwsContexSafe::SwsContextScaleEx(AVFrame * pFrame, AVFrame * pFrameRGB32)
{
	if ((pFrame != NULL) &&
		(pFrameRGB32 != NULL)) {

					if ((pFrame->width == mWidth) &&
						(pFrame->height == mHeight)) {


							this->SwsContextScale(pFrame, pFrameRGB32);

					}

	}	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/