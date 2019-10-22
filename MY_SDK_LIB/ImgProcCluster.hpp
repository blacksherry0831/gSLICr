 #pragma once
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
#include "opencv_stl.h"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
class ImgProcCluster
{
public:
	ImgProcCluster(void);
	~ImgProcCluster(void);
public:
	static bool IsSimilar(
		std::vector<int>&  _set_0,
		std::vector<int>&  _set_1);

	static bool RemoveLine_Float(
		float* _mat,
		const int _wh,
		const int _li);

	static bool MergeNeighbor_Float(
		float* _mat,
		const int _wh,
		const int _i,
		const int _j);

public:
	static void getMatCluster(const cv::Mat & _m);
	static void getMatCluster_Float(float * _mat, const int _wh);
	static void getMatTriangular(const cv::Mat & _m);
	static void getMatTriangular_Float(float * _mat, const int _wh);
public:
	static void GetClusterRelation_old(const cv::Mat& _m);
	static void GetClusterRelation_Recurve(const cv::Mat& _m);
public:
	static	void EnforceLabelConnectivity(
							const int * labels,
							const int width,
							const int height,
							int *& nlabels,
							int & numlabels,
							const int & K);

};