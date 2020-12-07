#pragma once
/*-----------------------------------------*/
#include "opencv_stl.h"
/*-----------------------------------------*/
#include "ImgProcBase.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class ImgProcAirView
{
public:
		ImgProcAirView();
		~ImgProcAirView();
private:
	CvPoint2D32f    objPts_Board[4];
	CvPoint2D32f	imgPts_Board[4];
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
	bool m_calibrate;
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
	static void SaveHomographyFiles(const IplImage * _img, const CvMat * _H);
	void LoadHomographyFiles();
public:
	static CvPoint2D32f getPolygonCenter(CvPoint2D32f* _Pts,  const int _sz);
	int getPointQuadrant(const CvPoint2D32f _cPt, const CvPoint2D32f _Pt);
	
	void InitcornerPoints(
		CvPoint2D32f* _objPts,
		CvPoint2D32f* _imgPts,
		const int _sz);

	void InitcornerPointsManual(const int _sz);

	void cornerPoints(const int _sz);

	void cornerPointsSort(const int _sz);
	void cornerPointsMapResult(const int _sz);

public:
	bool IsHomographyNullorZero();
public:
	void ColorInvert(CvArr* _src);
public:
	void initHomography(IplImage *_img);
	void generateHomographyAuto(IplImage *_img);
	void generateHomographyManual(IplImage *_img);
public:
	int FindChessBoard(IplImage *_img);
	void getHomographyTransform(const IplImage *_img);
	int ChessBoardManual(IplImage *_img);
	
	bool BirdsImage(IplImage *_src, IplImage *_dst);
public:
	void DrawChessboard(
		IplImage *_img,
		int _corner_count,
		int _found);

	void DrawChessboard4Points(IplImage *_img);

public:
	void setDstBoard2Camera(const double _dst);
	void setBoardSize_W(const int _w);
	void setBoardSize_H(const int _h);
	void setCellSize(const double _sz);
	void setCellPixel(const double _sz);
	void setCalibrate(bool _c);
public:

	void set_X_P(const int _i,const float _v);
	void set_Y_P(const int _i,const float _v);

	void set_X_P0(const float _v);
	void set_X_P1(const float _v);
	void set_X_P2(const float _v);
	void set_X_P3(const float _v);

	void set_Y_P0(const float _v);
	void set_Y_P1(const float _v);
	void set_Y_P2(const float _v);
	void set_Y_P3(const float _v);
};
