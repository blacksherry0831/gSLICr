#include "ImgProcCluster.hpp"
/*-----------------------------------------*/

/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcCluster::ImgProcCluster(void)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
ImgProcCluster::~ImgProcCluster(void)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImgProcCluster::IsSimilar(
	std::vector<int>& _set_0,
	std::vector<int>& _set_1)
{
	const int DIM0 = _set_0.size();
	const int DIM1 = _set_1.size();

	for (int si = 0; si <DIM0; si++){
		for (int sj = 0; sj <DIM1; sj++) {
			
			if (_set_0[si]==_set_1[sj]){
				return true;
			}

		}
	}
	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImgProcCluster::RemoveLine_Float(
	float* _mat,
	const int _wh,
	const int _li)
{

	for (size_t ci = 0; ci < _wh; ci++) {
		const int IDX_I = _li*_wh + ci;
		const int I_v = _mat[IDX_I];
		_mat[IDX_I] = 0;
	}

	return false;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
bool ImgProcCluster::MergeNeighbor_Float(
	float * _mat,
	const int _wh,
	const int _i,
	const int _j)
{
	
	for (size_t ci = 0; ci < _wh; ci++) {
		const int IDX_I = _i* _wh + ci;
		const int IDX_J = _j* _wh + ci;
		const int I_v = _mat[IDX_I];
		const int J_v = _mat[IDX_J];
		const int IJ_v = I_v | J_v;
		_mat[IDX_J] = IJ_v;
	}

	return true;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::getMatCluster(const cv::Mat & _m)
{

	assert(_m.cols == _m.rows);
	const int WH = _m.cols;
	float* similar = (float*)_m.ptr<float>(0);

	getMatCluster_Float(similar,WH);

#if _DEBUG
	cv::Scalar ss = cv::sum(_m);
	assert(ss[0] == WH);
#endif // _DEBUG
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::getMatCluster_Float(float * _mat, const int _wh)
{
	for (int ci = _wh - 1; ci >= 0; ci--) {

		std::vector<int> sameClass;

		for (int ri = 0; ri <_wh; ri++) {
			const int IDX = ci + ri*_wh;
			const int W = _mat[IDX];
			if (W) {
				sameClass.push_back(ri);
			}
		}

		if (sameClass.size() > 0) {
			const int ri_min = sameClass.at(0);
			for (int ri = 1; ri < sameClass.size(); ri++) {
				const int ri_current = sameClass.at(ri);
				MergeNeighbor_Float(_mat,_wh, ri_current, ri_min);
				RemoveLine_Float(_mat,_wh, ri_current);
			}
		}
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::getMatTriangular(const cv::Mat & _m)
{

	assert(_m.cols == _m.rows);
	float* labels = (float*) _m.ptr<float>(0);
	const int WH = _m.cols;
	
	getMatTriangular_Float(labels, WH);
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::getMatTriangular_Float(float* _mat,const int _wh)
{

	for (size_t ri = 0; ri <_wh; ri++) {
		for (size_t ci = 0; ci < ri; ci++) {
			const int IDX = ri*_wh + ci;
			_mat[IDX] = 0;
		}
	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::GetClusterRelation_old(const cv::Mat& _m)
{
	const int dx4[4] = { -1,  0,  1,  0 };
	const int dy4[4] = { 0, -1,  0,  1 };

	const float* labels = _m.ptr<float>(0);
	const int width = _m.cols;
	const int height = _m.rows;
	const int sz = width*height;
	const cv::Size mat_size(width, height);

	cv::Mat nlabels_mat(mat_size, CV_32FC1);
	cv::Mat xvec_mat(mat_size, CV_32SC1);
	cv::Mat yvec_mat(mat_size, CV_32SC1);

	float* nlabels = nlabels_mat.ptr<float>(0);
	int* xvec = xvec_mat.ptr<int>(0);
	int* yvec = yvec_mat.ptr<int>(0);
	for (int i = 0; i < sz; i++) nlabels[i] = -1;

	int label(1);

#if 1

	for (int j = 0; j < height; j++) {
		
		const int row_idx = j*width;
		int count=0;


		for (int k = 0; k < width; k++) {
				const int IDX = k+row_idx;
			
				if ((labels[IDX]!=0)&&
					(0 > nlabels[IDX]))
				{
					nlabels[IDX] = label;
					xvec[count++] = k;
					yvec[count++] = j;
					
					const int COUNT_START = count;

					for (int c = COUNT_START; c < count; c++)
					{
						for (int n = 0; n < 4; n++)
						{
							const int x = xvec[c] + dx4[n];
							const int y = yvec[c] + dy4[n];

							if ((x >= 0 && x < width) && (y >= 0 && y < height))
							{
								const int nindex = y*width + x;

								if (0 > nlabels[nindex] && labels[IDX] == labels[nindex])
								{
									xvec[count] = x;
									yvec[count] = y;
									nlabels[nindex] = label;
									count++;
								}
							}

						}
					}
				
					
				
			}

		
		}

		label++;
	
}
	
#endif

	int numlabels = label;
		
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void find_all_same(std::vector<int>& _same_type,int _spi, const float* _labels)
{
	const int WH=0;
	for (size_t spi = 0; spi < WH; spi++) {

		const int IDX = spi*WH + spi;

		if (_labels[IDX]) {
			_same_type.push_back(spi);
		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void find_one_block(std::vector<int>& _same_type, int _spi, const float* _labels, int*  _visit)
{
	const int WH=0;
	for (size_t spi = 0; spi < WH; spi++) {

		const int IDX = spi*WH + spi;

		if (_labels[IDX]) {
			_same_type.push_back(spi);
		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::GetClusterRelation(const cv::Mat & _m)
{
	getMatTriangular(_m);
	getMatCluster(_m);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::GetClusterRelation_Recurve(const cv::Mat & _m)
{
	assert(_m.cols == _m.rows);
	const float* labels = _m.ptr<float>(0);
	const int WH = _m.cols;
	const int sz = WH*WH;
	const cv::Size mat_size(WH, WH);
	const cv::Size visit_size(WH, 1);
	cv::Mat visit_mat(visit_size, CV_32SC1);
	cv::Mat nlabels_mat(mat_size, CV_32FC1);
	float*  nlabels = nlabels_mat.ptr<float>(0);
	for (int i = 0; i < sz; i++) nlabels[i] = -1;
	int*  visit = visit_mat.ptr<int>(0);
	for (int i = 0; i < sz; i++) visit[i] = FALSE;

	for (size_t spi = 0; spi < WH; spi++) {

		if (visit[spi] == FALSE) {

			std::vector<int> same_type;

			same_type.push_back(spi);

			find_one_block(same_type, spi, labels, visit);
			visit[spi] = TRUE;
		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void ImgProcCluster::EnforceLabelConnectivity(
	const int*					labels,//input labels that need to be corrected to remove stray labels
	const int					width,
	const int					height,
	int*&						nlabels,//new labels
	int&						numlabels,//the number of labels changes in the end if segments are removed
	const int&					K) //the number of superpixels desired by the user
{
	//	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	//	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

	const int dx4[4] = { -1,  0,  1,  0 };
	const int dy4[4] = { 0, -1,  0,  1 };

	const int sz = width*height;
	const int SUPSZ = sz / K;
	//nlabels.resize(sz, -1);
	for (register int i = 0; i < sz; i++) nlabels[i] = -1;
	int label(0);
	int* xvec = new int[sz];
	int* yvec = new int[sz];
	int oindex(0);
	int adjlabel(0);//adjacent label
	for (register int j = 0; j < height; j++)
	{
		for (register int k = 0; k < width; k++)
		{
			if (0 > nlabels[oindex])
			{
				nlabels[oindex] = label;
				//--------------------
				// Start a new segment
				//--------------------
				xvec[0] = k;
				yvec[0] = j;
				//-------------------------------------------------------
				// Quickly find an adjacent label for use later if needed
				//-------------------------------------------------------
				{for (register int n = 0; n < 4; n++)
				{
					int x = xvec[0] + dx4[n];
					int y = yvec[0] + dy4[n];
					if ((x >= 0 && x < width) && (y >= 0 && y < height))
					{
						int nindex = y*width + x;
						if (nlabels[nindex] >= 0) adjlabel = nlabels[nindex];
					}
				}}

				int count(1);
				for (register int c = 0; c < count; c++)
				{
					for (register int n = 0; n < 4; n++)
					{
						int x = xvec[c] + dx4[n];
						int y = yvec[c] + dy4[n];

						if ((x >= 0 && x < width) && (y >= 0 && y < height))
						{
							int nindex = y*width + x;

							if (0 > nlabels[nindex] && labels[oindex] == labels[nindex])
							{
								xvec[count] = x;
								yvec[count] = y;
								nlabels[nindex] = label;
								count++;
							}
						}

					}
				}

#if TRUE
				//-------------------------------------------------------
				// If segment size is less then a limit, assign an
				// adjacent label found before, and decrement label count.
				//-------------------------------------------------------

				//图块尺寸小于超像素平均尺寸的二分之一
				if (count <= SUPSZ >> 2)
				{
					for (register int c = 0; c < count; c++)
					{
						int ind = yvec[c] * width + xvec[c];
						nlabels[ind] = adjlabel;
					}
					label--;
				}
#endif

				label++;
			}
			oindex++;
		}
	}
	numlabels = label;

	if (xvec) delete[] xvec;
	if (yvec) delete[] yvec;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/