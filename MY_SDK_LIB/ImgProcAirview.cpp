#include "ImgProcAirView.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcAirView::ImgProcAirView()
{
	this->initParam();
	this->initParamPtr();
	
	this->LoadHomographyFiles();
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcAirView::~ImgProcAirView()
{
	this->ReleaseStorage();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::initParam() 
{
	this->m_calibrate = false;

	this->SetBoard(11, 8);
	this->black = 1;
	m_img_width=0;
	m_img_height=0;

	this->m_xml_homography = "Homography.xml";

	this->m_real_board_2_camera = 1;
	this->m_board_cell_meters   =0.03;
	this->m_board_cell_pixels = 2;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::SetBoard(const int _w, const int _h)
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
void ImgProcAirView::initParamPtr()
{
	this->H = nullptr;
	this->corners = nullptr;
	this->gray_image = nullptr;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcAirView::HaveHomographyFiles()
{
	std::ifstream h_file(m_xml_homography, std::ios::binary);
	
	if (h_file) {
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
void ImgProcAirView::SaveHomographyFiles(const IplImage* _img,const CvMat* _H)
{
	cvSave("Homography.xml", _H);
	cvvSaveImage("Homography.jpg", _img);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::LoadHomographyFiles()
{
	if (this->HaveHomographyFiles()){
		this->H = (CvMat*)cvLoad(m_xml_homography.c_str());
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
CvPoint2D32f ImgProcAirView::getPolygonCenter(
	CvPoint2D32f * _Pts,
	const int _sz)
{
	CvPoint2D32f c_t = cvPoint2D32f(0,0);
		
	for (size_t i = 0; i < _sz; i++){
		c_t.x += _Pts[i].x;
		c_t.y += _Pts[i].y;
	}

	c_t.x /= _sz;
	c_t.y /= _sz;

	return c_t;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcAirView::getPointQuadrant(const CvPoint2D32f  _cPt,const CvPoint2D32f  _Pt)
{
	CvPoint2D32f d_t = cvPoint2D32f(0, 0);

		d_t.x=_Pt.x - _cPt.x;
		d_t.y=_Pt.y - _cPt.y;

		if (d_t.x>0 && d_t.y>0){
			return 1;
		}else  if (d_t.x>0 && d_t.y<0){
			return 4;
		}else if (d_t.x<0 && d_t.y>0) {
			return 2;
		}else if (d_t.x<0 && d_t.y<0) {
			return 3;
		}else{
			return -1;
		}

		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::InitcornerPoints(
	CvPoint2D32f * _objPts,
	CvPoint2D32f * _imgPts,
	const int _sz)
{
	int quadMap[4];
	CvPoint2D32f imgPts[4];
	
	imgPts[0] = corners[0];
	imgPts[1] = corners[board_w - 1];
	imgPts[2] = corners[(board_h - 1)*board_w];
	imgPts[3] = corners[(board_h - 1)*board_w + board_w - 1];

#if 0
	imgPts[0] = cvPoint2D32f(347,366) ;
	imgPts[1] = cvPoint2D32f(523,364);
	imgPts[2] = cvPoint2D32f(312,402);
	imgPts[3] = cvPoint2D32f(551,399);
#endif // 0

	

	const CvPoint2D32f img_center=getPolygonCenter(imgPts,_sz);

	for (size_t i = 0; i < _sz; i++){
		const CvPoint2D32f P_t= imgPts[i];
		const int q=this->getPointQuadrant(img_center, P_t);
		if (q<0){
			return ;
		}else{
			quadMap[q-1] = q;
			_imgPts[q-1] = P_t;
		}
	
	}
	
	
	const float S = m_board_cell_pixels;
	
	const float   meters_per_pixel = this->MetersPerPixel();

	const int DST_C_B = m_real_board_2_camera / meters_per_pixel;

	const int B_H = S*(board_h - 1);
	const int B_W = S*(board_w - 1);
	const int X_OFF = (m_img_width-B_H)/2;
	const int Y_OFF = m_img_height- DST_C_B-B_W/2;

	_objPts[0]=cvPoint2D32f(B_H, B_W);//1
	_objPts[1]=cvPoint2D32f(0, B_W);//2
	_objPts[2]=cvPoint2D32f(0, 0);//3
	_objPts[3]=cvPoint2D32f(B_H, 0);//4
	
	_objPts[0].x += X_OFF; _objPts[0].y += Y_OFF;
	_objPts[1].x += X_OFF; _objPts[1].y += Y_OFF;
	_objPts[2].x += X_OFF; _objPts[2].y += Y_OFF;
	_objPts[3].x += X_OFF; _objPts[3].y += Y_OFF;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::InitcornerPointsManual(const int _sz)
{
#if 0
	imgPts_Board[0] = corners[0];
	imgPts_Board[1] = corners[board_w - 1];
	imgPts_Board[2] = corners[(board_h - 1)*board_w];
	imgPts_Board[3] = corners[(board_h - 1)*board_w + board_w - 1];
#endif // 0
#if 0
	imgPts_Board[0] = cvPoint2D32f(347, 366);
	imgPts_Board[1] = cvPoint2D32f(523, 364);
	imgPts_Board[2] = cvPoint2D32f(312, 402);
	imgPts_Board[3] = cvPoint2D32f(551, 399);
#endif // 0
	
	cornerPoints(_sz);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::cornerPoints(const int _sz)
{
	this->cornerPointsSort(_sz);
	this->cornerPointsMapResult(_sz);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::cornerPointsSort(const int _sz)
{
	int quadMap[4];
	CvPoint2D32f	imgPts[4];
	memcpy(imgPts, imgPts_Board, sizeof(imgPts));
	const CvPoint2D32f img_center = getPolygonCenter(imgPts, _sz);

	for (size_t i = 0; i < _sz; i++) {
		const CvPoint2D32f P_t = imgPts[i];
		const int q = this->getPointQuadrant(img_center, P_t);
		if (q<0) {
			return;
		}
		else {
			quadMap[q - 1] = q;
			imgPts_Board[q - 1] = P_t;
		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::cornerPointsMapResult(const int _sz)
{
	const float S = m_board_cell_pixels;

	const float   meters_per_pixel = this->MetersPerPixel();

	const int DST_C_B = m_real_board_2_camera / meters_per_pixel;

	const int B_H = S*(board_h - 1);
	const int B_W = S*(board_w - 1);
	const int X_OFF = (m_img_width - B_H) / 2;
	const int Y_OFF = m_img_height - DST_C_B - B_W / 2;

	objPts_Board[0] = cvPoint2D32f(B_H, B_W);//1
	objPts_Board[1] = cvPoint2D32f(0, B_W);//2
	objPts_Board[2] = cvPoint2D32f(0, 0);//3
	objPts_Board[3] = cvPoint2D32f(B_H, 0);//4

	objPts_Board[0].x += X_OFF; objPts_Board[0].y += Y_OFF;
	objPts_Board[1].x += X_OFF; objPts_Board[1].y += Y_OFF;
	objPts_Board[2].x += X_OFF; objPts_Board[2].y += Y_OFF;
	objPts_Board[3].x += X_OFF; objPts_Board[3].y += Y_OFF;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImgProcAirView::IsHomographyNullorZero()
{
	return ImgProcBase::IsMatNullorZero(H);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::ColorInvert(CvArr * _src)
{
	if (black == 1) {
		cvNot(_src, _src);//找角点需要反色
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::initHomography(IplImage * _img)
{
	if (IsSameWH(_img)) {

	}
	else {
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
void ImgProcAirView::generateHomographyAuto(IplImage * _img)
{

	if (this->IsHomographyNullorZero()){
		//已加载
	}
	else
	{
		this->FindChessBoard(_img);
	}

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::generateHomographyManual(IplImage * _img)
{
		
		this->ChessBoardManual(_img);

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcAirView::FindChessBoard(IplImage * _img)
{
	int corner_count = 0;
	ColorInvert(_img);
	int found = cvFindChessboardCorners(
		_img,
		board_sz,
		corners,
		&corner_count,
		CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS
	);
	
	if (found) {
	
		cvCvtColor(_img, gray_image, CV_BGR2GRAY);
		cvFindCornerSubPix(
			gray_image,
			corners,
			corner_count,
			cvSize(11, 11),
			cvSize(-1, -1),
			cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1)
		);

		CvPoint2D32f objPts[4], imgPts[4];

		this->InitcornerPoints(objPts, imgPts,4);
		
		// DRAW THE POINTS in order: B,G,R,YELLOW
		//
		cvCircle(_img, cvPointFrom32f(imgPts[0]), 9, CV_RGB(0, 0, 255), 3); //blue
		cvCircle(_img, cvPointFrom32f(imgPts[1]), 9, CV_RGB(0, 255, 0), 3); //green
		cvCircle(_img, cvPointFrom32f(imgPts[2]), 9, CV_RGB(255, 0, 0), 3); //red
		cvCircle(_img, cvPointFrom32f(imgPts[3]), 9, CV_RGB(255, 255, 0), 3); //yellow
		// DRAW THE FOUND CHESSBOARD
		
		cvDrawChessboardCorners(
			_img,
			board_sz,
			corners,
			corner_count,
			found
		);

		if (this->H==nullptr){
			H = cvCreateMat(3, 3, CV_32F);
			cvZero(H);
			cvGetPerspectiveTransform(objPts, imgPts, H);
			this->SaveHomographyFiles(_img,H);
			
		}
		
	}

	ColorInvert(_img);

	return found;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcAirView::ChessBoardManual(IplImage * _img)
{
	
	int corner_count = 0;	
	const int found = m_calibrate;

	if (found) {
		cvCvtColor(_img, gray_image, CV_BGR2GRAY);		
		this->InitcornerPointsManual(4);
		this->DrawChessboard4Points(_img);
		this->getHomographyTransform(_img);
		m_calibrate = false;
	}

	return found;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::getHomographyTransform(const IplImage *_img)
{
	CV_Assert(m_calibrate==true);
	if (this->H == nullptr) {
		H = cvCreateMat(3, 3, CV_32F);		
	}

	cvZero(H);
	cvGetPerspectiveTransform(objPts_Board, imgPts_Board, H);
	this->SaveHomographyFiles(_img, H);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImgProcAirView::BirdsImage(IplImage * _src, IplImage * _dst)
{
	if (this->IsHomographyNullorZero()) {
		
		cvWarpPerspective(
			_src,
			_dst,
			H,
			CV_INTER_LINEAR | CV_WARP_INVERSE_MAP | CV_WARP_FILL_OUTLIERS
		);
		return true;
		

	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::DrawChessboard(
	IplImage *_img,
	int _corner_count,
	int _found)
{

#if 1
	// DRAW THE FOUND CHESSBOARD
	cvDrawChessboardCorners(
		_img,
		board_sz,
		corners,
		_corner_count,
		_found
	);
#endif // 1
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::DrawChessboard4Points(IplImage * _img)
{
	// DRAW THE POINTS in order: B,G,R,YELLOW
	cvCircle(_img, cvPointFrom32f(imgPts_Board[0]), 9, CV_RGB(0, 0, 255), 3); //blue
	cvCircle(_img, cvPointFrom32f(imgPts_Board[1]), 9, CV_RGB(0, 255, 0), 3); //green
	cvCircle(_img, cvPointFrom32f(imgPts_Board[2]), 9, CV_RGB(255, 0, 0), 3); //red
	cvCircle(_img, cvPointFrom32f(imgPts_Board[3]), 9, CV_RGB(255, 255, 0), 3); //yellow
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::setDstBoard2Camera(const double _dst)
{
	this->m_real_board_2_camera = _dst;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::setBoardSize_W(const int _w)
{
	this->SetBoard(_w, board_h);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::setBoardSize_H(const int _h)
{
	this->SetBoard(board_w, _h);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::AllocateStorage(const IplImage *_img)
{
	corners = new CvPoint2D32f[board_n];
	gray_image = cvCreateImage(cvGetSize(_img), 8, 1);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::ReleaseStorage()
{
	delete[] corners;
	cvReleaseImage(&gray_image);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::SetWH(const IplImage * _img)
{
	this->m_img_width = _img->width;
	this->m_img_height = _img->height;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int ImgProcAirView::IsSameWH(const IplImage * _img)
{
	CV_Assert(nullptr!=_img);
	return (_img->width==m_img_width)&&(_img->height==m_img_height);
}

/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
float  ImgProcAirView::MetersPerPixel()
{
	const float   meters_per_pixel = m_board_cell_meters / m_board_cell_pixels;
	return meters_per_pixel;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::setCellSize(const double _sz)
{
	this->m_board_cell_meters = _sz;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::setCellPixel(const double _sz)
{
	this->m_board_cell_pixels = _sz;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::setCalibrate(bool _c)
{
	this->m_calibrate = _c;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_X_P(const int _i, const float _v)
{
	imgPts_Board[_i].x = _v;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_Y_P(const int _i, const float _v)
{
	imgPts_Board[_i].y = _v;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_X_P0(const float _v) 
{
	set_X_P(0, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_X_P1(const float _v) 
{
	set_X_P(1, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_X_P2(const float _v) 
{
	set_X_P(2, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_X_P3(const float _v) 
{
	set_X_P(3, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_Y_P0(const float _v) 
{
	set_Y_P(0,_v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_Y_P1(const float _v) 
{
	set_Y_P(1, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_Y_P2(const float _v) 
{
	set_Y_P(2, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcAirView::set_Y_P3(const float _v) 
{
	set_Y_P(3, _v);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/