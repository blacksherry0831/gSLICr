#include "Base.h"
/*-----------------------------------------*/
#if _MSC_VER
#include <windows.h>
#endif
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
Base::Base(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
Base::~Base(void)
{

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::str2int(int & int_temp, const std::string & string_temp)
{
	
		std::stringstream stream(string_temp);
		stream >> int_temp;
		return int_temp;

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::int2str(int value_t)
{
	std::stringstream stream;
	stream << value_t;

	return stream.str();
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::float2str(float _f_v)
{
	std::ostringstream buffer;
	buffer << _f_v;
	return buffer.str();
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
char Base::pathSplit()
{
	char split_t;

#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
	split_t='\\';
#endif

#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	split_t = '/';	
#endif
	return split_t;

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::base_name(std::string const & path)
{
	return path.substr(path.find_last_of("/\\") + 1);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::file_name_without_ext(std::string const path)
{
	std::string base_name = Base::base_name(path);
	
	std::vector<std::string> name_ext=split(base_name, ".");

	std::string name;
	std::string ext;
	
	if (name_ext.size()==2) {
		name=name_ext.at(0);
		ext=name_ext.at(1);	
	}
	return name;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::file_name_ext(std::string const path)
{
	std::string suffixStr = path.substr(path.find_last_of('.') + 1);//获取文件后缀 
	return suffixStr;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::comine_str(std::string f_str, std::string s_str)
{
	return f_str.append(s_str);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::vector<std::string> Base::split  (const std::string &s, char delim)
{

	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;

	while (std::getline(ss, item, delim)) {

		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::vector<std::string> Base::split  (const std::string &s, std::string delim)
{
	std::vector<std::string> v;
	std::string::size_type pos1, pos2;
	pos2 = s.find(delim);
	pos1 = 0;
	while(std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));

		pos1 = pos2 + delim.size();
		pos2 = s.find(delim, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));

	return v;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::SaveString2Disk(std::string file_name_t,std::string str_t)
{
#if _DEBUG	

	std::ofstream ofs;
	ofs.open(file_name_t);

	assert(ofs.is_open());
	ofs<<str_t;

	ofs.close();

#endif
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::IsEqual(std::string str_0,std::string str_1)
{
	int result_t=str_0.compare(str_1);

	if (result_t==0){
		return TRUE;
	}else{
		return FALSE;
	}
}
/*----------------------------------*/
/**
*
*/
/*----------------------------------*/
void Base::sleep(int ms)
{

#if __GNUC__
	usleep(ms * 1000);
#endif

#if _MSC_VER
	Sleep(ms);
#endif

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int  Base::is_file_exist(const char * file_path)
{

	if (file_path == NULL)
		return FALSE;
	
	if (access(file_path, 0) == 0) {
		return TRUE;
	}else{
		return FALSE;
	}

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::get_number(std::string str_t)
{

	std::string str_new_t;

	for (size_t i = 0; i <str_t.size(); i++)
	{
			char char_t=str_t.at(i);

			if (isdigit(char_t)) {
				str_new_t += char_t;
			}
	}
		
	return atoi(str_new_t.c_str());
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
double Base::Math_GetAverageValue(double* Data, int DataNum)
{
	double sum = 0;
	ASSERT(DataNum>0);
	for (int i = 0; i<DataNum; i++) {
		sum += Data[i];
	}
	sum /= DataNum;
	return sum;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
double Base::Math_GetAverageValue8U(unsigned char * Data, int DataNum)
{
	double sum = 0;
	ASSERT(DataNum>0);
	for (int i = 0; i<DataNum; i++) {
		sum += Data[i];
	}
	sum /= DataNum;
	return sum;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
float Base::Math_GetAverageValueF(float * Data, int DataNum)
{
	if (DataNum==0){
		return 0;
	}else{
		ASSERT(DataNum>0);	
		double sum = Math_GetSumF(Data, DataNum);
		sum /= DataNum;
		return sum;
	}
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
double Base::Math_GetVarianceValue(
	double* Data,
	int DataNum,
	double avg,
	double *variance) {

	*variance = 0;
	for (int i = 0; i<DataNum; i++) {
		*variance += (avg - Data[i])*(avg - Data[i]);
	}
	*variance /= DataNum;
	*variance = sqrtl(*variance);
	return *variance;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
float Base::Math_GetVarianceValueF(float * Data,const int DataNum, const float avg, float * variance)
{
	*variance = 0;
	if (DataNum>0)
	{
			*variance = 0;
			for (int i = 0; i<DataNum; i++) {
				*variance += (avg - Data[i])*(avg - Data[i]);
			}
			*variance /= DataNum;
			*variance = sqrtl(*variance);
	}		
	return *variance;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
float Base::Math_GetVarianceValue8U(unsigned char * Data, int DataNum, float avg)
{
	float sigma = 0;

	for (int i = 0; i<DataNum; i++) {
		sigma += (avg - Data[i])*(avg - Data[i]);
	}
	sigma /= DataNum;
	sigma = sqrtl(sigma);
	return sigma;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
double Base::Math_GetMaxValue(double* Data, long DataNum)
{
	double *Data_cp = new double[DataNum];
	double  max_value;
	memcpy(Data_cp, Data, sizeof(double)*DataNum);
	std::sort(Data_cp, Data_cp + DataNum, std::greater<double>());
	max_value = Data_cp[0];
	delete[]Data_cp;
	return  max_value;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
float Base::Math_GetMaxValueF(float * Data, long DataNum)
{
	float *Data_cp = new float[DataNum];
	float  max_value;
	memcpy(Data_cp, Data, sizeof(float)*DataNum);
	std::sort(Data_cp, Data_cp + DataNum, std::greater<float>());
	max_value = Data_cp[0];
	delete[]Data_cp;
	return  max_value;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
float Base::Math_GetMinValueF(float * Data, long DataNum)
{
	float *Data_cp = new float[DataNum];
	float  max_value;
	memcpy(Data_cp, Data, sizeof(float)*DataNum);
	std::sort(Data_cp, Data_cp + DataNum, std::less<float>());
	max_value = Data_cp[0];
	delete[]Data_cp;
	return  max_value;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::Math_AbsArray(double * Data, long Num)
{
	for (size_t i = 0; i <Num; i++) {

		Data[i] = fabs(Data[i]);
	}
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::Math_GetMaxValueIndexF(float * data, float size, int * sort, int sort_num)
{
	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::Math_GetMaxValueIndex(double * data, float size, int * sort, int sort_num)
{
	double* data_t = new double[(long long)size];
	memcpy(data_t, data, sizeof(double)*((long long)size));
	/*****寻找最值***************************************************************/
	for (int sj = 0; sj<sort_num; sj++) {

		float max_value = data[0];
		int max_value_i = 0;
		/*******************************/
		for (register int i = 0; i<size; i++) {
			if (data_t[i]>max_value) {
				max_value = data_t[i];
				max_value_i = i;
			}
		}
		/*******************************/
		sort[sj] = max_value_i;
		data_t[max_value_i] = FLT_MIN;

	}
	/*******************************************************************************/
	delete[]data_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
float Base::Math_GetSumF(float * Data, int DataNum)
{
	float sum = 0;
#if 0
	for (size_t i = 0; i <DataNum; i++){		
		sum += Data[i];
	}
#else
	std::vector<float>   data(&Data[0], &Data[DataNum]);
	sum=std::accumulate(data.begin(),data.end(), 0.0f);
#endif // 0

	return sum;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string & Base::replace_str(std::string & str, const std::string & to_replaced, const std::string & newchars)
{
	for (std::string::size_type pos(0); pos != std::string::npos; pos += newchars.length())
	{
		pos = str.find(to_replaced, pos);
		if (pos != std::string::npos)
			str.replace(pos, to_replaced.length(), newchars);
		else
			break;
	}
	return   str;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::STD_push_back(std::vector<std::string> &dst, std::vector<std::string> &src)
{
	dst.insert(dst.end(), src.begin(), src.end());
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::STD_push_back(std::vector<float>& dst, std::vector<float>& src)
{
	dst.insert(dst.end(), src.begin(), src.end());
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::vector<float> Base::CombineVector(std::vector<float> v0, std::vector<float> v1)
{
	std::vector<float> v_out;

	v_out.insert(v_out.end(), v0.begin(), v0.end());

	v_out.insert(v_out.end(), v1.begin(), v1.end());

	return v_out;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::FS_deleteFile(const std::string file_full_path)
{
	if (Base::is_file_exist(file_full_path.c_str())) {
	
		return remove(file_full_path.c_str());
	
	}else{

		return TRUE;
	}


}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::FS_copyFile(const std::string src, const std::string dst)
{
	Base::FS_deleteFile(dst);
	int copy_result_t = 0;

#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	copy_result_t = FS_copyFileSTL(src,dst);
#endif

#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
	copy_result_t = CopyFileA(src.c_str(), dst.c_str(), false);
	
	DWORD ERROR_CODE;
	if (copy_result_t == 0)
	{
		ERROR_CODE = GetLastError();
	}
	assert(copy_result_t != 0);
#endif
	

	return copy_result_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::FS_MoveFile(const std::string src, const std::string dst)
{
	FS_copyFileSTL(src, dst);
	FS_deleteFile(src);
	return 0;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::FS_copyFileSTL(const std::string src, const std::string dst)
{
	std::ifstream ifs(src, std::ios::binary);
	std::ofstream ofs(dst.data(), std::ios::binary);

	ofs << ifs.rdbuf();

	return TRUE;

}

/************************************************************************/
/*  获取文件夹下所有文件名
输入：
path    :   文件夹路径
exd     :   所要获取的文件名后缀，如jpg、png等；如果希望获取所有
文件名, exd = ""
输出：
files   :   获取的文件名列表

shao, 20140707
*/
/************************************************************************/
void Base::FS_getFiles(std::string path, std::string exd, std::vector<std::string>& files)
{

#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	FS_getFilesLinux(path, exd, files);
#endif

#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
	FS_getFilesWin(path,exd,files);
#endif
	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::FS_getFilesLinux(std::string path, std::string exd, std::vector<std::string>& files)
{
	const char *Path = path.data();
	std::vector<char> currentPathStd(path.size()+1024);
	char* currentPath = currentPathStd.data();
	strcpy(currentPath, Path);//保存到m_CurrentPath
	char fullpath[128];
	files.clear();

	

#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	
	assert(false);

	DIR *dir;
	if (!(dir = opendir(Path)))
	{
		assert(false);
		return;
	}
	
	struct dirent *d_ent;
	
	
	while ((d_ent = readdir(dir)) != NULL)
	{
		struct stat file_stat;
		//if ( strncmp(d_ent->d_name, ".", 1) == 0 )
		//{
		//	continue;	// 忽略"."目录
		//}
		memset(fullpath, '\0', sizeof(fullpath));
		strcpy(fullpath, Path);
		if (!strcmp(fullpath, "/"))
		{
			fullpath[0] = '\0';
		}
		strcat(fullpath, "/");
		strcat(fullpath, d_ent->d_name);
		if (lstat(fullpath, &file_stat) < 0)
		{
			assert(false);
			return;
		}
		//保存信息到自己的数据结构，在函数外面保存文件名
		
		std::string path_full_name = path+ std::string(d_ent->d_name);
		
		files.push_back(path_full_name);
	}

	closedir(dir);	
#endif

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::FS_getFilesWin(std::string path, std::string exd, std::vector<std::string>& files)
{

#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	std::string pathName, exdName;

	if (FS_checkUserPath(path) == false) {
		path.append("\\");
	}



	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是文件夹中仍有文件夹,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					FS_getFiles(pathName.assign(path).append(fileinfo.name), exd, files);
			}
			else
			{
				const std::string file_name_t = fileinfo.name;
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {

					const std::string ext_t = Base::file_name_ext(file_name_t);

					if (file_name_t.find(exd) != std::string::npos) {
						files.push_back(pathName.assign(path).append(fileinfo.name));
					}



				}

			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
#endif
	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::FS_getDirs(std::string path, std::string flag, std::vector<std::string>& files)
{

#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
	FS_getDirsWin(path, flag, files);
#endif
#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	assert(false);
#endif
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
void Base::FS_getDirsWin(std::string path, std::string flag, std::vector<std::string>& files)
{
	//文件句柄  
	long   hFile = 0;
	std::string pathName, exdName;
	const std::string exd = "";
	
	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}else{
		exdName = "\\*";
	}

#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
	
	//文件信息  
	struct _finddata_t fileinfo;	

	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是文件夹中仍有文件夹,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				std::string file_name = fileinfo.name;
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0 && file_name.find(flag)!= std::string::npos) {
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
				}
					
			}else{
				
					
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
#endif

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::FS_getFileName(const std::string&  path)
{
	return path.substr(path.find_last_of("/\\") + 1);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::FS_getSuperDirPath(std::string path)
{
	int pos = path.find_last_of("/\\");

	return path.substr(0,pos);
		
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::FS_getDirName(std::string path)
{
	std::vector<std::string>  vs = Base::split(path, '\\');
	std::string dir_name_t = vs.at(vs.size() - 1);//chX.
	return dir_name_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::FS_getEndDirName(std::string path)
{
	std::vector<std::string>  vs = Base::split(path, '\\');
	std::string dir_name_t = vs.at(vs.size() - 1);//chX.
	return dir_name_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::CRACK_FILE_NAME_get_idx(std::string file_full_name)
{
	return CRACK_FILE_NAME_get_channel(file_full_name);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::CRACK_FILE_NAME_get_channel(std::string file_full_name)
{
	std::string base_name = Base::base_name(file_full_name);
	std::vector<std::string>  vs = Base::split(base_name, '.');

	const std::string CHANNEL_STR = "ch";
	for (size_t i = 0; i <vs.size(); i++){
		const std::string str_t= vs.at(i);
		if (str_t.find(CHANNEL_STR) == std::string::npos) {
		
		}else{
				return Base::get_number(str_t);
		}
	}

	ASSERT(0);
	return -1;
}
int Base::CRACK_FILE_NAME_get_FRAME(std::string file_full_name)
{
	std::string base_name = Base::base_name(file_full_name);
	std::vector<std::string>  vs = Base::split(base_name, '.');

	const std::string CHANNEL_STR = "frame";
	for (size_t i = 0; i <vs.size(); i++) {
		const std::string str_t = vs.at(i);
		if (str_t.find(CHANNEL_STR) == std::string::npos) {

		}
		else {
			return Base::get_number(str_t);
		}
	}

	ASSERT(0);
	return -1;
}
int Base::CRACK_FILE_NAME_get_PROPERTY(std::string file_full_name, std::string _property)
{

	std::string base_name = Base::base_name(file_full_name);
	std::vector<std::string>  vs = Base::split(base_name, '.');
	
	for (size_t i = 0; i <vs.size(); i++) {
		const std::string str_t = vs.at(i);
		if (str_t.find(_property) == std::string::npos) {

		}
		else {
			return TRUE;
		}
	}

	return FALSE;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int  Base::CRACK_FILE_NAME_get_circle(std::string file_full_name)
{
	std::string base_name = Base::base_name(file_full_name);
	std::vector<std::string>  vs = Base::split(base_name, '.');

	const std::string CHANNEL_STR = "circle";
	for (size_t i = 0; i <vs.size(); i++) {
		const std::string str_t = vs.at(i);
		if (str_t.find(CHANNEL_STR) == std::string::npos) {

		}
		else {
			return Base::get_number(str_t);
		}
	}

	ASSERT(0);
	return -1;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
int Base::CRACK_FILE_NAME_get_circle_byPath(std::string path)
{	
	std::vector<std::string>  vs = Base::split(path, '\\');
	std::string number_t = vs.at(vs.size()-1);//chX.
	return Base::get_number(number_t);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::FS_createPath(std::string path_base, std::string path_sub, boolean CREATE_FLAG)
{
	FS_checkUserPath_add_divide(path_base);
			
	std::string create_path_t = path_base + path_sub;

	FS_checkUserPath_add_divide(create_path_t);
			
	const char * file_full_path_t = create_path_t.c_str();
	
	if (CREATE_FLAG) {
		FS_createDir(file_full_path_t);
	}

	return create_path_t;
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::FS_createDir(std::string _path)
{
#if defined(_WIN32) || defined(_WIN64) || defined( _MSC_VER)
	CreateDirectoryA(_path.c_str(), NULL);
#endif
#if defined(linux) || defined(__linux) || defined(__linux__) ||defined( __GNUC__)
	mode_t mode = 0755;
	::mkdir(_path.c_str(), mode);
#endif
	return "true";
}

/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::CRACK_FILR_NAME_get_ipAddr(std::string file_full_name)
{
	std::vector<std::string>  file_cal_t;
		file_cal_t.push_back("192.168.9.0");
		file_cal_t.push_back("192.168.9.1");
		file_cal_t.push_back("192.168.9.2");
		file_cal_t.push_back("192.168.9.3");
		file_cal_t.push_back("192.168.9.4");
		file_cal_t.push_back("192.168.9.5");
		file_cal_t.push_back("192.168.9.6");
		file_cal_t.push_back("192.168.9.7");
	
		return file_cal_t.at(CRACK_FILE_NAME_get_idx(file_full_name));

}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::CRACK_PATH_GetFrameChannelDiff(std::string file_base, std::string file_name, std::string add_str,boolean create_flag)
{
	const int video_idx = Base::CRACK_FILE_NAME_get_idx(file_base + file_name);
	const int CIRCLE = Base::CRACK_FILE_NAME_get_circle(file_base + file_name);
	return CRACK_PATH_GetFrameChannelDiff(file_base,CIRCLE,video_idx,add_str,create_flag);
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::CRACK_PATH_GetFrameChannelDiff(std::string file_base, int CIRCLE, int CHANNEL, std::string add_str,boolean create_flag)
{
	const int video_idx = CHANNEL;
	std::stringstream ss_file_full_path;

	if (FS_checkUserPath(file_base) == false) {
		file_base.append("\\");
	}

	ss_file_full_path << file_base;
	
#if TRUE
	ss_file_full_path << "circle" << CIRCLE << "\\";
	FS_createDir(ss_file_full_path.str());
#endif // TRUE
#if TRUE
	ss_file_full_path << "ch" << video_idx << add_str << "\\";
	FS_createDir(ss_file_full_path.str());
#endif // TRUE

	return ss_file_full_path.str();
	
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
bool  Base::FS_checkUserPath(std::string userPath)
{
	std::string sub = userPath.substr(userPath.size()-1,1);
	if (sub == "\\" || sub == "/")
	{
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
*
*/
/*-----------------------------------------*/
bool Base::FS_checkUserPath_add_divide(std::string & userPath)
{
	if (FS_checkUserPath(userPath))
	{
		return true;
	}
	else
	{
		userPath.push_back(pathSplit());
		return false;
	}
}
/*-----------------------------------------*/
/**
*
*
*/
/*-----------------------------------------*/
std::string Base::TIME_getCurrentTime(std::string _format)
{
	time_t now = time(NULL);
	struct tm timeinfo = *localtime(&now);
	char buf[1024];
	strftime(buf, sizeof(buf), _format.c_str(), &timeinfo);

	std::string time_t(buf);
	return time_t;
}
/*----------------------------------------------------------------*/
/**
* @note "%Y%m%d%H%M%S"==20130207142133
*/
/*----------------------------------------------------------------*/
