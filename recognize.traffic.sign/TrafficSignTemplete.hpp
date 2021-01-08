#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "TrafficSignParam.hpp"
#include "TrafficSignMethod.hpp"
/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/

/*-----------------------------------------*/
class TrafficSignTemplete
{
public:
	TrafficSignTemplete(void);
	~TrafficSignTemplete(void);
private:
	TrafficSignParam*  mParam;
public:
	void setTrafficSignParam(TrafficSignParam*  _p);
private:
	
public:
	void  SampleTempletePreprocess();
	void  SampleTestingPreprocess(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps);
public:
	std::vector<std::shared_ptr<TrafficSignProperty>> TempleteLoad();
	void  TempleteSift(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps);
	void  TempleteSave(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps);

};