#include "ImgProcCalibrate.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcCalibrate::ImgProcCalibrate()
{
	this->initParam();
	this->initParamPtr();
	
	this->LoadCalibrationFiles();
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcCalibrate::~ImgProcCalibrate()
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::SetBoard(const int _w, const int _h)
{
	board_w = _w;
	board_h = _h;
	board_n = _w * _h;
	board_sz = cvSize(_w, _h);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::initParam() 
{
	this->SetBoard(11, 8);
	
	black = 1;
	num_boards = 15;
	m_frame = 0;
	m_frame_gap = 10;
	successes = 0;
	m_img_width=0;
	m_img_height=0;

	this->m_xml_intrinsics="Intrinsics.xml";
	this->m_xml_distortion="Distortion.xml";
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::initParamPtr()
{
	this->image_points=nullptr;
	this->object_points = nullptr;
	this->point_counts = nullptr;
	this->intrinsic_matrix = nullptr;
	this->distortion_coeffs = nullptr;
	this->corners = nullptr;
	this->gray_image = nullptr;

	this->mapx=nullptr;
	this->mapy=nullptr;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcCalibrate::IsDetectFrame()
{

	return (m_frame % m_frame_gap) == 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcCalibrate::IncFrame()
{
	return m_frame++;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcCalibrate::HaveCalibrationFiles()
{
	std::ifstream i_file(m_xml_intrinsics, std::ios::binary);
	std::ifstream d_file(m_xml_distortion, std::ios::binary);
	
	if (i_file && d_file) {
		return true;
	}
	else
	{
		return false;
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::SaveCalibrationFiles()
{
	// SAVE THE INTRINSICS AND DISTORTIONS
	cvSave(m_xml_intrinsics.c_str(), intrinsic_matrix);
	cvSave(m_xml_distortion.c_str(), distortion_coeffs);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::LoadCalibrationFiles()
{

	if (this->HaveCalibrationFiles()) {
		intrinsic_matrix = (CvMat*)cvLoad(m_xml_intrinsics.c_str());
		distortion_coeffs = (CvMat*)cvLoad(m_xml_distortion.c_str());
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImgProcCalibrate::IsLoadCalibrationFiles()
{

	if (intrinsic_matrix!=nullptr && distortion_coeffs!=nullptr){
		return true;
	}else{
		return false;
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::DrawProgressBar(IplImage * _img)
{
	const int T=10;
	const int W = _img->width;
	const int H = _img->height - T/2;
	const float p_scale = 1.0*successes/ num_boards;
	const int p_len = p_scale*W;
	cvDrawLine(_img,cvPoint(0,H),cvPoint(p_len,H),cvScalar(0,255,0),T);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::Calculate_Intrinsics_Distortion(IplImage *_img,int& _find) 
{
	try
	{

		if (this->IsLoadCalibrationFiles()){
		
		}else{
			//没有配置文件
			_find = this->FindChessBoard(_img);
			this->Calculate(_img);
		}

	

	}
	catch (const cv::Exception& e)
	{
		std::cout<< e.msg << std::endl;
	}
	
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcCalibrate::FindChessBoard(IplImage* _img)
{
	
	
	int  corner_count;
	int step;

	if(successes < num_boards) {
			
		if (black == 1) {
			cvNot(_img, _img);//找角点需要反色
		}
		//Skip every board_dt frames to allow user to move chessboard
		if (IsDetectFrame()) {
			//Find chessboard corners:
			const int found = cvFindChessboardCorners(
				_img, board_sz, corners, &corner_count,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
			);

			//Get Subpixel accuracy on those corners
			cvCvtColor(_img, gray_image, CV_BGR2GRAY);
			cvFindCornerSubPix(gray_image, corners, corner_count,
				cvSize(11, 11), cvSize(-1, -1), cvTermCriteria(
					CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

			//Draw it
			cvDrawChessboardCorners(_img, board_sz, corners,
				corner_count, found);
			//      cvShowImage( "Calibration", image );
			if (black == 1) {
				cvNot(_img, _img);//找角点需要反色
			}
			// If we got a good board, add it to our data
			if (corner_count == board_n) {
				
				step = successes*board_n;
				for (int i = step, j = 0; j<board_n; ++i, ++j) {
					CV_MAT_ELEM(*image_points, float, i, 0) = corners[j].x;
					CV_MAT_ELEM(*image_points, float, i, 1) = corners[j].y;
					CV_MAT_ELEM(*object_points, float, i, 0) = j / board_w;
					CV_MAT_ELEM(*object_points, float, i, 1) = j%board_w;
					CV_MAT_ELEM(*object_points, float, i, 2) = 0.0f;
				}
				CV_MAT_ELEM(*point_counts, int, successes, 0) = board_n;
				successes++;
				return 1;
				
			}
			else {
																		
			}

		} 
				  
	} 
	return 0;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::Calculate(IplImage *_img)
{

	if (successes<num_boards) {
		return;
	}

	//ALLOCATE MATRICES ACCORDING TO HOW MANY CHESSBOARDS FOUND
	CvMat* object_points2 = cvCreateMat(successes*board_n, 3, CV_32FC1);
	CvMat* image_points2 = cvCreateMat(successes*board_n, 2, CV_32FC1);
	CvMat* point_counts2 = cvCreateMat(successes, 1, CV_32SC1);
	
	//TRANSFER THE POINTS INTO THE CORRECT SIZE MATRICES
	for (int i = 0; i<successes*board_n; ++i) {
		CV_MAT_ELEM(*image_points2, float, i, 0) =
			CV_MAT_ELEM(*image_points, float, i, 0);
		CV_MAT_ELEM(*image_points2, float, i, 1) =
			CV_MAT_ELEM(*image_points, float, i, 1);
		CV_MAT_ELEM(*object_points2, float, i, 0) =
			CV_MAT_ELEM(*object_points, float, i, 0);
		CV_MAT_ELEM(*object_points2, float, i, 1) =
			CV_MAT_ELEM(*object_points, float, i, 1);
		CV_MAT_ELEM(*object_points2, float, i, 2) =
			CV_MAT_ELEM(*object_points, float, i, 2);
	}

	for (int i = 0; i<successes; ++i) { //These are all the same number
		CV_MAT_ELEM(*point_counts2, int, i, 0) =
			CV_MAT_ELEM(*point_counts, int, i, 0);
	}


		intrinsic_matrix = cvCreateMat(3, 3, CV_32FC1);
		distortion_coeffs = cvCreateMat(4, 1, CV_32FC1);

		CV_MAT_ELEM(*intrinsic_matrix, float, 0, 0) = 1.0f;
		CV_MAT_ELEM(*intrinsic_matrix, float, 1, 1) = 1.0f;

		//CALIBRATE THE CAMERA!
		cvCalibrateCamera2(
			object_points2, image_points2,
			point_counts2, cvGetSize(_img),
			intrinsic_matrix, distortion_coeffs,
			NULL, NULL, 0  //CV_CALIB_FIX_ASPECT_RATIO
		);

		this->SaveCalibrationFiles();
	
		cvReleaseMat(&object_points2);
		cvReleaseMat(&image_points2);
		cvReleaseMat(&point_counts2);


}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::Init_Intrinsics_Distortion(IplImage *_img)
{
	if (IsSameWH(_img)){
		
	}else{
		SetWH(_img);
		ReleaseStorage();
		AllocateStorage(_img);
	}
	

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::AllocateStorage(const IplImage *_img)
{
	
	//ALLOCATE STORAGE
	 image_points = cvCreateMat(num_boards*board_n, 2, CV_32FC1);
	 object_points = cvCreateMat(num_boards*board_n, 3, CV_32FC1);
	 point_counts = cvCreateMat(num_boards, 1, CV_32SC1);
	
	 corners = new CvPoint2D32f[board_n];
	 gray_image = cvCreateImage(cvGetSize(_img), 8, 1);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::SetWH(const IplImage * _img)
{
	this->m_img_width = _img->width;
	this->m_img_height = _img->height;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcCalibrate::IsSameWH(const IplImage * _img)
{
	CV_Assert(nullptr!=_img);
	return (_img->width==m_img_width)&&(_img->height==m_img_height);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::ReleaseStorage()
{
	cvReleaseMat(&object_points);
	cvReleaseMat(&image_points);
	cvReleaseMat(&point_counts);
	
	cvReleaseImage(&mapx);
	cvReleaseImage(&mapy);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCalibrate::calibration_image(IplImage * _img) 
{


	CvPoint cxcy;

	if (intrinsic_matrix == NULL || distortion_coeffs == NULL) {
		std::cout << "没有校准文件";
		return;
	}

	cxcy.x = cvmGet(intrinsic_matrix, 0, 2);
	cxcy.y = cvmGet(intrinsic_matrix, 1, 2);
		
	int image_h = _img->height;
	int image_w = _img->width;

	if (mapx==nullptr && mapy==nullptr ){
		
		mapx = cvCreateImage(cvGetSize(_img), IPL_DEPTH_32F, 1);
		mapy = cvCreateImage(cvGetSize(_img), IPL_DEPTH_32F, 1);
		cvInitUndistortMap(
			intrinsic_matrix,
			distortion_coeffs,
			mapx,
			mapy
		);

	}


	if (_img!=nullptr)
	{
		IplImage *t = cvCloneImage(_img);
	
		cvRemap(t, _img, mapx, mapy);     // Undistort image
		cvReleaseImage(&t);
#if 0
#if DRAW_LINE
		for (int i = 0; i<12; i++) {
			cvLine(image, cvPoint(0, image_h / 12 * i), cvPoint(image_w, image_h / 12 * i), CV_RGB(0, 0, 255));
			cvLine(image, cvPoint(image_w / 12 * i, 0), cvPoint(image_w / 12 * i, image_h), CV_RGB(0, 0, 255));
		}
#else
		for (int i = 0; i<12; i++) {
			cvCircle(_img, cxcy, i*(50), CV_RGB(0, 0, 255));
		}
#endif
	
#if DRAW_LINE 
		for (int i = 0; i<12; i++) {
			cvLine(image, cvPoint(0, image_h / 12 * i), cvPoint(image_w, image_h / 12 * i), CV_RGB(255, 0, 0));
			cvLine(image, cvPoint(image_w / 12 * i, 0), cvPoint(image_w / 12 * i, image_h), CV_RGB(255, 0, 0));
		}
#else
		for (int i = 0; i<12; i++) {
			cvCircle(_img, cxcy, i*(50), CV_RGB(255, 0, 0));
		}
#endif
#endif
	}
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/