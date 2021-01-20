#include "TrafficSignParam.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignParam::TrafficSignParam(void)
{
	this->initDefault();
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignParam::~TrafficSignParam(void)
{

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignParam::initDefault()
{
	this->mPathRootSampleTemplete = "Sample";

	this->mForward = "Forward";
	this->mLeft    = "Left";
	this->mRight   = "Right";


	this->mBlockSize = 6300;

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
int TrafficSignParam::getBlockSize()
{
	return mBlockSize;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getForwardPrefix()
{
	return mForward;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getLeftPrefix()
{
	return  mLeft;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getRightPrefix()
{
	return  mRight;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::string> TrafficSignParam::getAllArrowType()
{
	std::vector<std::string> at;

	at.push_back(getForwardPrefix());
	at.push_back(getLeftPrefix());
	at.push_back(getRightPrefix());
	
	return at;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignParam::setSampleTempletePath(const std::string _p)
{
	this->mPathRootSampleTemplete = _p;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::string> TrafficSignParam::getSampleTestingPaths()
{
	std::vector<std::string> paths;
	paths.push_back(this->getForwardPathSampleTesting());
	paths.push_back(this->getLeftPathSampleTesting());
	paths.push_back(this->getRightPathSampleTesting());

	return paths;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getSampleTestingPath()
{
	return mPathRootSampleTesting;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignParam::setSampleTestingPath(std::string _p)
{

	mPathRootSampleTesting = _p;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::string> TrafficSignParam::getTempletePaths()
{
	std::vector<std::string> paths;
	paths.push_back(this->getForwardPathTemplete());
	paths.push_back(this->getLeftPathTemplete());
	paths.push_back(this->getRightPathTemplete());
	
	return paths;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getTempletePath()
{
	return mPathRootTemplete;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignParam::setTempletePath(std::string _p)
{
	mPathRootTemplete = _p;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::pathConn(std::string _p, std::string _sub)
{
	std::string path;
	path.append(_p)
		.append("\\")
		.append(_sub);
	return  path;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getForwardPathSampleTemplete()
{
	return  pathConn(this->mPathRootSampleTemplete,this->mForward);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getLeftPathSampleTemplete()
{
	return  pathConn(this->mPathRootSampleTemplete, this->mLeft);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getRightPathSampleTemplete()
{
  return  pathConn(this->mPathRootSampleTemplete, this->mRight);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getForwardPathSampleTesting()
{
	return  pathConn(this->mPathRootSampleTesting, this->mForward);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getLeftPathSampleTesting()
{
	return  pathConn(this->mPathRootSampleTesting, this->mLeft);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getRightPathSampleTesting()
{
	return  pathConn(this->mPathRootSampleTesting, this->mRight);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getForwardPathTemplete()
{
	return  pathConn(this->mPathRootTemplete, this->mForward);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getLeftPathTemplete()
{
	return  pathConn(this->mPathRootTemplete, this->mLeft);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getRightPathTemplete()
{
	return  pathConn(this->mPathRootTemplete, this->mRight);
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::string TrafficSignParam::getSampleTempletePath()
{
	return this->mPathRootSampleTemplete;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::string> TrafficSignParam::getSampleTempletePaths()
{
	std::vector<std::string> paths;
	paths.push_back(this->getForwardPathSampleTemplete());
	paths.push_back(this->getLeftPathSampleTemplete());
	paths.push_back(this->getRightPathSampleTemplete());

	return paths;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/