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

	static void CombineSimilar(
		std::vector<std::vector<int>>&  _similar_set,
		const int _i,
		const int _j);

	static bool IsAdjacent(
		const cv::Mat & _m,
		const int _ri,
		const int _ci);

	static bool MergeNeighbor(
		const cv::Mat & _m,
		const int _i,
		const int _j);

	static bool RemoveLine(
		const cv::Mat & _m,
		const int _i);

	static bool RemoveLine_Float(float* _mat, const int _wh, const int _li);


	static void CombineSimilar(std::vector<std::vector<int>>&  _similar_set);
public:
	static void getMatCluster(const cv::Mat & _m);
	static void getMatCluster_Float(float * _mat, const int _wh);
	static void getMatTriangular(const cv::Mat & _m);
	static void getMatTriangular_Float(float * _mat, const int _wh);
public:
	static void GetClusterRelation(const cv::Mat& _m);
	
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