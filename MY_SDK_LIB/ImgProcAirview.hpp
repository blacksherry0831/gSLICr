#pragma once
/*-----------------------------------------*/
#include "opencv_stl.h"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
class ImgProcAirView
{
public:
		ImgProcAirView();
		~ImgProcAirView();
private:
	int m_img_width;
	int m_img_height;
private:
	int  board_w;
	int  board_h;
	int  board_n;
	CvSize board_sz;
	int  black;
private:
	double m_real_board_2_camera;//The distance between  board center to camera center
	double m_board_cell_meters;
	double m_board_cell_pixels;
private:
	std::string m_xml_homography;
	CvMat *H;

private:
	CvPoint2D32f* corners;
	IplImage *gray_image;
private:
	void ReleaseStorage();
	
	void AllocateStorage(const IplImage *_img);

	void SetWH(const IplImage *_img);
	int IsSameWH(const IplImage *_img);

	void initParam();
	void SetBoard(const int _w, const int _h);
	void initParamPtr();
public:
	float  MetersPerPixel();
public:
	int HaveHomographyFiles();
	void SaveHomographyFiles();
	void LoadHomographyFiles();
public:
	CvPoint2D32f getPolygonCenter(CvPoint2D32f* _Pts,  const int _sz);
	int getPointQuadrant(const CvPoint2D32f _cPt, const CvPoint2D32f _Pt);
	void InitcornerPoints(CvPoint2D32f* _objPts, CvPoint2D32f* _imgPts,const int _sz);
public:
	bool IsHomographyValid();
	
public:
	void initHomography(IplImage *_img);
	void generateHomography(IplImage *_img);
public:
	int FindChessBoard(IplImage *_img);
	int BirdsImage(IplImage *_img);
public:
	void setDstBoard2Camera(const double _dst);
	void setBoardSize_W(const int _w);
	void setBoardSize_H(const int _h);
	void setCellSize(const double _sz);
	void setCellPixel(const double _sz);
};
