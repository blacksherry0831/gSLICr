#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
class Base
{
public:
	Base(void);
	~Base(void);
public:
    static	int str2int(int &int_temp, const std::string &string_temp);
	static  std::string int2str(int value_t);
	static  std::string float2str(float _f_v);
public:
	static char pathSplit();

	//static string GetNameExt4path(void);

	static std::string base_name(std::string const & path);

	static std::string file_name_without_ext(std::string const  path);

	static std::string file_name_ext(std::string const  path);

	static std::string comine_str(std::string f_str, std::string s_str);

	static std::vector<std::string> split  (const std::string &s, char delim);

	static std::vector<std::string> split  (const std::string &s, std::string delim);

	static void SaveString2Disk(
		std::string ffile_name_t,
		std::string str_t);
	
	static int IsEqual(std::string str_0,std::string str_1);
	
public:
	static void sleep(int ms);
	static int is_file_exist(const char * file_path);
	static int get_number(std::string str_t);
public:
	static double Math_GetAverageValue(double* Data, int DataNum);

	static double Math_GetAverageValue8U(unsigned char* Data, int DataNum);

	static float Math_GetAverageValueF(float* Data, int DataNum);
	
	static double Math_GetVarianceValue(
		double* Data,
		int DataNum,
		double avg,
		double *variance);

	static float Math_GetVarianceValueF(
		float* Data,
		const int DataNum,
		const float avg,
		float *variance);

	static float Math_GetVarianceValue8U(
		unsigned char* Data,
		int DataNum,
		float avg);
	
	static double Math_GetMaxValue(double* Data, long DataNum);

	static float Math_GetMaxValueF(float* Data, long DataNum);

	static float Math_GetMinValueF(float* Data, long DataNum);
	
	
	static void	  Math_AbsArray(double * Data, long Num);

	static void  Math_GetMaxValueIndexF(
		float* data,
		float size,
		int* sort,
		int sort_num);

	static void  Math_GetMaxValueIndex(
		double* data,
		float size,
		int* sort,
		int sort_num);




public:
	static float Math_GetSumF(float * Data,int DataNum);
public:
	static std::string& replace_str(std::string& str, const std::string& to_replaced, const std::string& newchars);
	static void STD_push_back(std::vector<std::string> &dst, std::vector<std::string> &src);
	static void STD_push_back(std::vector<float> &dst, std::vector<float> &src);
	static std::vector<float> CombineVector(std::vector<float> v0, std::vector<float> v1);
public:
	static int FS_deleteFile(const std::string file_full_path);
	static int FS_copyFile(const std::string src,const std::string dst);

	static int FS_MoveFile(const std::string src, const std::string dst);
	
	static int FS_copyFileSTL(const std::string src, const std::string dst);

	static void FS_getFiles(std::string path, std::string exd, std::vector<std::string>& files);	
	
	static void FS_getDirs(std::string path, std::string flag, std::vector<std::string>& files);
private:
	static void FS_getFilesWin(std::string path, std::string exd, std::vector<std::string>& files);
	static void FS_getFilesLinux(std::string path, std::string exd, std::vector<std::string>& files);
	static void FS_getDirsWin(std::string path, std::string flag, std::vector<std::string>& files);
public:
	static std::string FS_getFileName(const std::string&  path);
	static std::string FS_getSuperDirPath(std::string path);
	static std::string FS_getEndDirName(std::string path);
	
	static std::string FS_getDirName(std::string path);

	static bool FS_checkUserPath(std::string userPath);
	static bool FS_checkUserPath_add_divide(std::string& userPath);
	
	static std::string FS_createPath(std::string path_base, std::string path_sub, boolean CREATE_FLAG=true);
	static std::string FS_createDir(std::string _path);
public:
	static int CRACK_FILE_NAME_get_idx(std::string file_full_name);
	
	static int CRACK_FILE_NAME_get_channel(std::string file_full_name);

	static int CRACK_FILE_NAME_get_FRAME(std::string file_full_name);
	static int CRACK_FILE_NAME_get_PROPERTY(std::string file_full_name, std::string _property);
	
	static int CRACK_FILE_NAME_get_circle(std::string file_full_name);
	static int CRACK_FILE_NAME_get_circle_byPath(std::string path);
	static std::string CRACK_FILR_NAME_get_ipAddr(std::string file_full_name);

	static std::string CRACK_PATH_GetFrameChannelDiff(std::string file_base, std::string file_name, std::string add_str="",boolean create_flag=true);
	static std::string CRACK_PATH_GetFrameChannelDiff(std::string file_base,int CIRCLE,int CHANNEL, std::string add_str,boolean create_flag=true);
public:
	static std::string TIME_getCurrentTime(std::string _format= "%Y%m%d%H%M%S");

};

