#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "device_functions.h"
#include "math_functions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#define  WeightZoom (10000)

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#include<assert.h>
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
#define Unclassify (-2)
#define  Remove (-1)
#if 1
#define  Unknow (0)   
#endif
#define  Ground11  (-11)
#define  Ground12  (-12)
#define  Ground13  (-13)
#define  Ground (1)
#define  GroundCv   cvScalar(Ground,0,0,0)
#define  GroundPending  (-14)
#if 0
#define  NotSky   (1.5)
#endif
#define  Vertical (2)
#define  VerticalCv  cvScalar(Vertical,0,0,0)
#define  VerticalPending (-21)
#if 0
#define  NotGround (2.5)
#endif 
#define  Sky  (3)
#define  SkyCv  cvScalar(Sky,0,0,0)
#define  SkyPending (-31)
#ifdef Vertical 
#if Vertical 
#define Vertical_Tree      (4)
#define Vertical_Building  (5)
#endif
#endif 
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
typedef signed int          INT32;
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaInit_CUI(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" bool cudaDeInit_CUI(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C" void cudaGetLastError_Sync_CUI(void);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
extern "C"  void classify_SkyVerticalGround_gpu(
	double horizontal_line,
	INT32*	 Matrix_Category_Lable_host,
	double* SkyWeightArray_host,
	double* VerticalWeightArray_host,
	double* GroundWeightArray_host,
	double* SkyWeightSp_host,
	double* VerticalWeightSp_host,
	double* GroundWeightSp_host,
	int*    labels_host,
	int     Numlabels,
	int Width,
	int Height);
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
//__inline__ __host__ __device__ float GetPosWeightArrayV(float horizontal_line, float n,float sigma,float i)
//{
//	float Weight=(1/(sqrt(2*M_PI)*sigma))*exp(-pow(i,2)/pow(sigma,2))*WeightZoom;
//	return Weight;
//}
/*------------------------------------------------------------------------------------------*/
/**
*
*int i = blockIdx.x * blockDim.x + threadIdx.x;

Read more at: http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#ixzz3Ts8QtgEN 
Follow us: @GPUComputing on Twitter | NVIDIA on Facebook
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void	FillWeightArrayV_Kernel(double horizontal_line, double n,double* WeightArray_dev,float Height)
{
	
	int i = blockIdx.x * blockDim.x + threadIdx.x;	
	if (i>Height) return;
	double sigma;
	double L,L_1,L_2;
	L_1=horizontal_line;
	L_2=Height-horizontal_line;
	L=(L_1>L_2)?L_2:L_1;
	//sigma=L/3;
	
	sigma=L/6;//调整sigma 位置

	int x=i-L;
	int y=0-x+horizontal_line;	
		
	if (y>=0&&y<Height){
		//WeightArray_dev[y]=(1/(sqrt(2*M_PI)*sigma))*exp(-pow((float)x,2)/pow(sigma,2))*WeightZoom;
		WeightArray_dev[y]=(1/(sqrt(2*M_PI)*sigma))*exp(-pow((float)x,2)/pow(sigma,2))*WeightZoom*2;//2015年5月22日17:31:00 立面密度乘以二;
	}
	
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void	FillWeightArrayS_out_Kernel(double horizontal_line, double n,double* WeightArray_dev,float Height)
{
#if 0
int i = blockIdx.x * blockDim.x + threadIdx.x;	
	if (i>Height) return;
	double C_1,C_2;
	double L_1,L_2;
	L_1=Height-horizontal_line;
	L_2=horizontal_line;
	C_1=(2*n+2.0)/((2*n+1)*pow(L_1,(2*n+2)/(2*n+1.0)));
	C_2=(2*n+2.0)/((2*n+1)*pow(L_2,(2*n+2)/(2*n+1.0)));
	/**************************************************/
	int x=i-Height+horizontal_line;
	int y=horizontal_line-x-1;
	/**************************************************/
	if (y>=0&&y<Height){
		if (x<0){
			WeightArray_dev[y]=-1*C_1*pow(-x,1.0/(2*n+1))*WeightZoom;
		}else if (x>=0){
			WeightArray_dev[y]=C_2*pow(x,1.0/(2*n+1))*WeightZoom;
		}else{
			assert(0);
		}
	}
	/**************************************************/
#endif
#if 1
	int i = blockIdx.x * blockDim.x + threadIdx.x;	
	if (i>Height) return;
	double C_1,C_2;
	double L_1,L_2;
	L_1=Height-horizontal_line;
	L_2=horizontal_line;
	C_1=(2*n+2.0)/((2*n+1)*pow(L_1,(2*n+2)/(2*n+1.0)));
	C_2=(2*n+2.0)/((2*n+1)*pow(L_2,(2*n+2)/(2*n+1.0)));
	/**************************************************/
	int x=horizontal_line-i;
	int y=horizontal_line-x-1;
	/**************************************************/
	if (y>=0&&y<Height){
		if (x<0){
			WeightArray_dev[y]=-1*C_1*pow(-x*1.0,1.0/(2*n+1))*WeightZoom;
		}else if (x>=0){
			WeightArray_dev[y]=C_2*pow(x*1.0,1.0/(2*n+1))*WeightZoom;
		}else{
			assert(0);
		}
	}
	/**************************************************/
#endif
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
__global__ void	FillWeightArrayG_out_Kernel(double horizontal_line, double n,double* WeightArray_dev,float Height)
{

	int i = blockIdx.x * blockDim.x + threadIdx.x;	
	if (i>Height) return;

	double C_1,C_2;
	double L_1,L_2;	
	L_1=Height-horizontal_line;
	L_2=horizontal_line;
	C_1=(2*n+2.0)/((2*n+1)*pow(L_1,(2*n+2)/(2*n+1.0)));
	C_2=(2*n+2.0)/((2*n+1)*pow(L_2,(2*n+2)/(2*n+1.0)));
	
	int x=i-Height+horizontal_line;
	int y=horizontal_line-x-1;

		if (y>=0&&y<Height){
			if (x<0){
				//奇函数
				WeightArray_dev[y]=-1*(-1*C_1*pow(-1.0*x,1.0/(2*n+1)))*WeightZoom;
			}else{
				WeightArray_dev[y]=-1*C_2*pow(x*1.0,1.0/(2*n+1))*WeightZoom;
			}
			/*if (WeightArray_dev[y]<0){
				WeightArray_dev[y]=0;
			}*/
			
		}
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
 void FillWeightArrayV(double horizontal_line, double n,int Height,double* WeightArray_dev)
{
	
	FillWeightArrayV_Kernel<<<(Height+1023)/1024,1024>>>(horizontal_line,n,WeightArray_dev,Height);
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
 void FillWeightArrayS_out(double horizontal_line, double n,int Height,double* WeightArray_dev)
 {

	 FillWeightArrayS_out_Kernel<<<(Height+1023)/1024,1024>>>(horizontal_line,n,WeightArray_dev,Height);
 }
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
 void FillWeightArrayG_out(double horizontal_line, double n,int Height,double* WeightArray_dev)
 {

	 FillWeightArrayG_out_Kernel<<<(Height+1023)/1024,1024>>>(horizontal_line,n,WeightArray_dev,Height);
 }
 /*------------------------------------------------------------------------------------------*/
 /**
 *
 *
 *
 */
 /*------------------------------------------------------------------------------------------*/
 __global__ void Statistical_SVGsum_Fill_Category_Lable(
	 int    Numlabels,
	 double* SkyWeightSp_dev,
	 double* VerticalWeightSp_dev,
	 double* GroundWeightSp_dev,
	 INT32*	Matrix_Category_Lable_dev,
	 double* SVG_SpSum,
	 double* SkyWeightArray_dev,
	 double* VerticalWeightArray_dev,
	 double* GroundWeightArray_dev,
	 int Height,
	 int Width,
	 int*labels_dev)
 {
 
	 int spi = blockIdx.x * blockDim.x + threadIdx.x;	
	 if (spi<Numlabels){
		 SkyWeightSp_dev[spi]=0;
		 VerticalWeightSp_dev[spi]=0;
		 GroundWeightSp_dev[spi]=0;
		 SVG_SpSum[spi]=0;


	 for (register int x=0;x<Width;x++){
		 for (register int y=0;y<Height;y++){
			
			 int pixelIdx=y*Width+x;

			 if (spi==labels_dev[pixelIdx]){

				  SkyWeightSp_dev[spi]+=SkyWeightArray_dev[y];
				  VerticalWeightSp_dev[spi]+=VerticalWeightArray_dev[y];
				  GroundWeightSp_dev[spi]+=GroundWeightArray_dev[y];
				  SVG_SpSum[spi]+=1;

			 }
			
		 }
	 }
#if 1
	SkyWeightSp_dev[spi]/=SVG_SpSum[spi];
	 VerticalWeightSp_dev[spi]/=SVG_SpSum[spi];
	 GroundWeightSp_dev[spi]/=SVG_SpSum[spi];
	 //////////////////////////////////////////////////////////////
	 if ((SkyWeightSp_dev[spi]>=VerticalWeightSp_dev[spi])
		 &&(SkyWeightSp_dev[spi]>=GroundWeightSp_dev[spi])){
			 Matrix_Category_Lable_dev[spi]=Sky;
	 }
	 //////////////////////////////////////////////////////////////
	 if ((GroundWeightSp_dev[spi]>=VerticalWeightSp_dev[spi])
		 &&(GroundWeightSp_dev[spi]>=SkyWeightSp_dev[spi])){
			 Matrix_Category_Lable_dev[spi]=Ground;
	 }
	 //////////////////////////////////////////////////////////////
	 if ((VerticalWeightSp_dev[spi]>=SkyWeightSp_dev[spi])
		 &&(VerticalWeightSp_dev[spi]>=GroundWeightSp_dev[spi])){
			 Matrix_Category_Lable_dev[spi]=Vertical;
	 }	
	 ////////////////////////////////////////////////////////////
#endif
	 }	
	 
 }
  /*------------------------------------------------------------------------------------------*/
 /**
 *
 *
 *
 */
 /*------------------------------------------------------------------------------------------*/
 void Statistical_SVGsum_Fill_Category_Lable_CPU(
	 int    Numlabels,	
	 INT32*	Matrix_Category_Lable_host,
	 double* SkyWeightArray_host,
	 double* VerticalWeightArray_host,
	 double* GroundWeightArray_host,
	 double* SkyWeightSp_host,
	 double* VerticalWeightSp_host,
	 double* GroundWeightSp_host,
	 int Height,
	 int Width,
	 int*labels_host)
 {
		 cudaError_t cudaStatus;
		 double* SVG_SpSum_host=new double[Numlabels];
		 memset(SVG_SpSum_host,0,sizeof(double)*Numlabels);
		 memset(SkyWeightSp_host,0,sizeof(double)*Numlabels);
		 memset(VerticalWeightSp_host,0,sizeof(double)*Numlabels);
		 memset(GroundWeightSp_host,0,sizeof(double)*Numlabels);
		 for (register int x=0;x<Width;x++){
			 for (register int y=0;y<Height;y++){
				 int pixelIdx=y*Width+x;
				 int spi=labels_host[pixelIdx];
				 	 SkyWeightSp_host[spi]+=SkyWeightArray_host[y];
					 VerticalWeightSp_host[spi]+=VerticalWeightArray_host[y];
					 GroundWeightSp_host[spi]+=GroundWeightArray_host[y];
					 SVG_SpSum_host[spi]+=1;
			 }
		 }
		 for (int spi=0;spi<Numlabels;spi++){
			 SkyWeightSp_host[spi]/=SVG_SpSum_host[spi];
			 VerticalWeightSp_host[spi]/=SVG_SpSum_host[spi];
			 GroundWeightSp_host[spi]/=SVG_SpSum_host[spi];
#if 1
			 //////////////////////////////////////////////////////////////
			 if ((SkyWeightSp_host[spi]>=VerticalWeightSp_host[spi])
				 &&(SkyWeightSp_host[spi]>=GroundWeightSp_host[spi])){
					 Matrix_Category_Lable_host[spi]=Sky;
			 }
			 //////////////////////////////////////////////////////////////
			 if ((GroundWeightSp_host[spi]>=VerticalWeightSp_host[spi])
				 &&(GroundWeightSp_host[spi]>=SkyWeightSp_host[spi])){
					 Matrix_Category_Lable_host[spi]=Ground;
			 }
			 //////////////////////////////////////////////////////////////
			 if ((VerticalWeightSp_host[spi]>=SkyWeightSp_host[spi])
				 &&(VerticalWeightSp_host[spi]>=GroundWeightSp_host[spi])){
					 Matrix_Category_Lable_host[spi]=Vertical;
			 }	
			 ////////////////////////////////////////////////////////////
#endif
		 }
		 delete [] SVG_SpSum_host;
		/* delete [] SkyWeightSp_host;
		 delete [] VerticalWeightSp_host;
		 delete [] GroundWeightSp_host;*/
 }
/*------------------------------------------------------------------------------------------*/
/**
*
*
*@Param [out] Matrix_Category_Lable 
*/
/*------------------------------------------------------------------------------------------*/
 __global__ void Fill_Category_Lable(
	 double* SkyWeightSp_dev,
	 double* VerticalWeightSp_dev,
	 double* GroundWeightSp_dev,
	 INT32*	Matrix_Category_Lable)
{
	 int spi = blockIdx.x * blockDim.x + threadIdx.x;	
	  //////////////////////////////////////////////////////////////
	  if ((SkyWeightSp_dev[spi]>=VerticalWeightSp_dev[spi])
		  &&(SkyWeightSp_dev[spi]>=GroundWeightSp_dev[spi])){
			  Matrix_Category_Lable[spi]=Sky;
	  }
	  //////////////////////////////////////////////////////////////
	  if ((GroundWeightSp_dev[spi]>=VerticalWeightSp_dev[spi])
		  &&(GroundWeightSp_dev[spi]>=SkyWeightSp_dev[spi])){
			  Matrix_Category_Lable[spi]=Ground;
	  }
	  //////////////////////////////////////////////////////////////
	  if ((VerticalWeightSp_dev[spi]>=SkyWeightSp_dev[spi])
		  &&(VerticalWeightSp_dev[spi]>=GroundWeightSp_dev[spi])){
			  Matrix_Category_Lable[spi]=Vertical;
	  }	
	  //////////////////////////////////////////////////////////////
}
/*------------------------------------------------------------------------------------------*/
/**
*
*
*
*/
/*------------------------------------------------------------------------------------------*/
 void classify_SkyVerticalGround_gpu(
	 double horizontal_line,
	 INT32*	 Matrix_Category_Lable_host,
	 double* SkyWeightArray_host,
	 double* VerticalWeightArray_host,
	 double* GroundWeightArray_host,
	 double* SkyWeightSp_host,
	 double* VerticalWeightSp_host,
	 double* GroundWeightSp_host,
	 int*    labels_host,
	 int     Numlabels,
	 int Width,
	 int Height)
{
	 cudaError_t cudaStatus;
	 double *SkyWeightArray_dev;
	 double *VerticalWeightArray_dev;
	 double *GroundWeightArray_dev;
	 cudaStatus = cudaMalloc((void**)&SkyWeightArray_dev,Height * sizeof(double));
	 cudaStatus = cudaMalloc((void**)&VerticalWeightArray_dev,Height* sizeof(double));
	 cudaStatus = cudaMalloc((void**)&GroundWeightArray_dev,Height * sizeof(double));
	 {
		 /////////////////////////////////////////////////////////////////////////////////
#if 1
 FillWeightArrayG_out(horizontal_line,1,Height,GroundWeightArray_dev);
#endif
 #if 1
 FillWeightArrayV(horizontal_line,1,Height,VerticalWeightArray_dev);
#endif
#if 1
 FillWeightArrayS_out(horizontal_line,1,Height,SkyWeightArray_dev);
#endif
		
		
		
		 /////////////////////////////////////////////////////////////////////////////////
		 double* SkyWeightSp_dev;
		 double* VerticalWeightSp_dev;
		 double* GroundWeightSp_dev;
		 double* SVG_SpSum_dev;
		 int* labels_dev;
		 INT32* Matrix_Category_Lable_dev;
		 //////////////////////////////////////////////////////////////////////////////
		  cudaStatus = cudaMalloc((void**)&SkyWeightSp_dev, Numlabels*sizeof(double));
		  cudaStatus = cudaMalloc((void**)&VerticalWeightSp_dev,Numlabels*sizeof(double));
		  cudaStatus = cudaMalloc((void**)&GroundWeightSp_dev,Numlabels*sizeof(double));
		  cudaStatus = cudaMalloc((void**)&SVG_SpSum_dev,Numlabels*sizeof(double));
		  cudaStatus = cudaMalloc((void**)&labels_dev,Width*Height * sizeof(int));
		  cudaStatus = cudaMalloc((void**)&Matrix_Category_Lable_dev,Numlabels * sizeof(double));
		  cudaMemcpy(labels_dev,labels_host,Width*Height*sizeof(int),cudaMemcpyHostToDevice);
		  /////////////////////////////////////////////////////////////////////////////
#if 0
Statistical_SVGsum_Fill_Category_Lable<<<(Numlabels+1023)/1024,1024>>>(
								 Numlabels,
								 SkyWeightSp_dev,
								 VerticalWeightSp_dev,
								 GroundWeightSp_dev,
								 Matrix_Category_Lable_dev,
								 SVG_SpSum_dev,
								 SkyWeightArray_dev,
								 VerticalWeightArray_dev,
								 GroundWeightArray_dev,
								 Height,
								 Width,
								 labels_dev);
		 cudaGetLastError_Sync_CUI();
		 cudaMemcpy(Matrix_Category_Lable_host,Matrix_Category_Lable_dev,Numlabels*sizeof(double) ,cudaMemcpyDeviceToHost);
		 cudaGetLastError_Sync_CUI();
#else		 
		 /* double* VerticalWeightArray_host=new double[Height];
		  double* GroundWeightArray_host=new double[Height];
		  double* SkyWeightArray_host=new double[Height];*/
		  cudaStatus=cudaMemcpy(VerticalWeightArray_host,VerticalWeightArray_dev,Height*sizeof(double),cudaMemcpyDeviceToHost);
		  cudaStatus=cudaMemcpy(GroundWeightArray_host,GroundWeightArray_dev,Height*sizeof(double),cudaMemcpyDeviceToHost);
		  cudaStatus=cudaMemcpy(SkyWeightArray_host,SkyWeightArray_dev,Height*sizeof(double),cudaMemcpyDeviceToHost);
#if _MSC_VER
 {
			  char data_t[1024];																			
			  ofstream outfile;								   
			  outfile.open("Matrix_Weight_GVS_zlm_cuda.data",ios::out);
			  for( int i = 0; i <Height; i++ ){
				  {
					   double value_t=i;
					  sprintf_s(data_t,1024," %0.2e ",value_t);
					  outfile<<data_t;		
				  }
				  {
					  double value_t=GroundWeightArray_host[i];
					  sprintf_s(data_t,1024," %0.2e ",value_t);
					  outfile<<data_t;										
				  }
				  {
					  double value_t=VerticalWeightArray_host[i];
					  sprintf_s(data_t,1024," %0.2e ",value_t);
					  outfile<<data_t;										
				  }
				  {
					  double value_t=SkyWeightArray_host[i];
					  sprintf_s(data_t,1024," %0.2e ",value_t);
					  outfile<<data_t;										
				  }
				  outfile<<endl;			 
			  } 
			  outfile.close();
		  }
#endif
		 

		  Statistical_SVGsum_Fill_Category_Lable_CPU(
			  Numlabels,	
			  Matrix_Category_Lable_host,
			  SkyWeightArray_host,
			  VerticalWeightArray_host,
			  GroundWeightArray_host,
			  SkyWeightSp_host,
			  VerticalWeightSp_host,
			  GroundWeightSp_host,
			  Height,
			  Width,
			  labels_host);
		  //delete [] SkyWeightArray_host;
		  //delete [] VerticalWeightArray_host;
		  //delete [] GroundWeightArray_host;
#endif		 
		 /////////////////////////////////////////////////
		 cudaFree(SkyWeightSp_dev);
		 cudaFree(VerticalWeightSp_dev);
		 cudaFree(GroundWeightSp_dev);
		 cudaFree(SVG_SpSum_dev);
		 cudaFree(labels_dev);
		 cudaFree(Matrix_Category_Lable_dev);
	 }
	 cudaFree(SkyWeightArray_dev);
	 cudaFree(VerticalWeightArray_dev);
	 cudaFree(GroundWeightArray_dev);
} 
 /*------------------------------------------------------------------------------------------*/
 /**
 *
 *
 *
 */
 /*------------------------------------------------------------------------------------------*/