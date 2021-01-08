#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
#include "cpp_def.h"
/*-----------------------------------------*/
class TrafficSignParam
{
public:
	TrafficSignParam(void);
	~TrafficSignParam(void);
private:
	void initDefault();
private:
	int mBlockSize;
public:
	int getBlockSize();
private:
	std::string  mPathRootSampleTemplete;
	std::string  mPathRootSampleTesting;
	std::string  mPathRootTemplete;
private:
	std::string  mForward;
	std::string  mLeft;
	std::string  mRight;
	std::string  mSides;
public:
	std::string getForwardPrefix();
	std::string getLeftPrefix();
	std::string getRightPrefix();
	std::string getSidesPrefix();
public:
	std::string getForwardPathSampleTemplete();
	std::string getLeftPathSampleTemplete();
	std::string getRightPathSampleTemplete();
	std::string getSidesPathSampleTemplete();
public:
	std::string getForwardPathSampleTesting();
	std::string getLeftPathSampleTesting();
	std::string getRightPathSampleTesting();
	std::string getSidesPathSampleTesting();
public:
	std::string getForwardPathTemplete();
	std::string getLeftPathTemplete();
	std::string getRightPathTemplete();
	std::string getSidesPathTemplete();
public:
	std::vector<std::string> getSampleTempletePaths();
	std::string getSampleTempletePath();
	void setSampleTempletePath(std::string _p);
public:
	std::vector<std::string> getSampleTestingPaths();
	std::string getSampleTestingPath();
	void setSampleTestingPath(std::string _p);
public:
	std::vector<std::string> getTempletePaths();
	std::string getTempletePath();
	void setTempletePath(std::string _p);
public:
	static std::string pathConn(std::string _p,std::string _sub);
public:

};

