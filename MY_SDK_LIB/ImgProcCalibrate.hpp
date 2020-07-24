#pragma once
/*-----------------------------------------*/
#include "opencv_stl.h"
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
class ImgProcCalibrate 
{
public:
		ImgProcCalibrate();
		~ImgProcCalibrate();
private:
	 int  board_w;
	 int  board_h;
	 int  board_n;
	 CvSize board_sz;
private:
	 int	m_img_width;
	 int	m_img_height;
	 int  num_boards;
	 int  black;
	 int  m_frame;
	 int  m_frame_gap;
	 int  successes;
private:
	std::string m_xml_intrinsics;
	std::string m_xml_distortion;
private:
	CvMat* image_points;
	CvMat* object_points;
	CvMat* point_counts;
	CvMat* intrinsic_matrix;
	CvMat* distortion_coeffs;
	CvPoint2D32f* corners;
	IplImage *gray_image;
private:
	IplImage* mapx;
	IplImage* mapy;
private:
	void ReleaseStorage();
	
	void AllocateStorage(const IplImage *_img);
	void SetWH(const IplImage *_img);
	int IsSameWH(const IplImage *_img);
public:
	void SetBoard(const int _w,const int _h);
	void initParam();
	void initParamPtr();
public:
	int IsDetectFrame();
	int IncFrame();
public:
	int HaveCalibrationFiles();
	void SaveCalibrationFiles();
	void LoadCalibrationFiles();
	bool IsLoadCalibrationFiles();
public:
	void DrawProgressBar(IplImage *_img);
public:
	void Init_Intrinsics_Distortion(IplImage *_img);

	void Calculate_Intrinsics_Distortion(IplImage *_img, int& _find);

	int FindChessBoard(IplImage *_img);

	void Calculate(IplImage *_img);

	void calibration_image(IplImage * _img);

};
