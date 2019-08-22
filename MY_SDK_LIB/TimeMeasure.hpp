#pragma once
/*----------------------------------------------------------------*/
#include "opencv_basic.h"
#include "cpp_basic.h"
#include "cpp_def_type.h"
/*----------------------------------------------------------------*/
#include "Base.h"
/*----------------------------------------------------------------*/
#if _MSC_VER
#include "windows.h"
#endif // _MSC_VER
/*----------------------------------------------------------------*/
/**
*
*
*
*/
/*----------------------------------------------------------------*/
class TimeMeasure
{
public:
	TimeMeasure(std::string _event);
	TimeMeasure();
	~TimeMeasure();
private:
	static const std::string mFile;
	static int mDebug;
	static int mSave;
private:
	int IsTimeMeasure;
	std::string mEVENT;

#if _MSC_VER
	LARGE_INTEGER litmp;
	LONGLONG QPart1, QPart2;
	double dfMinus, dfFreq, dfTim;
#endif // _MSC_VER

	double dur;
	clock_t start_time;
	clock_t end_time;
private:
	void Write2File(std::string _msg);
public:
	void start(std::string _event);
	std::string stop();
public:
	static void Config(const int _debug = 0, const int _save = 0);

};

