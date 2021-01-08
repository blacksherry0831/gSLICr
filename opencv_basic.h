#ifndef OpenCV_BASIC_H
#define OpenCV_BASIC_H
//OPENCV        
/*********************************************************/
#include <cv.h>
#include <highgui.h>
/*********************************************************/
#if (CV_MAJOR_VERSION==2)&&(CV_MINOR_VERSION==4)
#include <opencv2/ml/ml.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/nonfree/nonfree.hpp"    
#include "opencv2/legacy/legacy.hpp"
#include <opencv2/opencv.hpp>
#endif
/*********************************************************/
#if (CV_MAJOR_VERSION==3)
#include <opencv2/ml.hpp> 
#endif
/*********************************************************/
#endif










