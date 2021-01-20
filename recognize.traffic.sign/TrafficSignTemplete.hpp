#pragma once
/*-----------------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------------*/
#include "opencv_basic.h"
/*-----------------------------------------*/
#include "TrafficSignParam.hpp"
#include "TrafficSignMethod.hpp"
#include "TrafficSignMethodHu.hpp"
/*-----------------------------------------*/
#include "MY_SDK_LIB/Base.h"
/*-----------------------------------------*/
#include "TrafficSignPropertyHu.hpp"
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
	void DrawExactTemplete();
public:
	void  SampleTempletePreprocess();
	void  SampleTestingPreprocess(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps);

	std::vector<std::shared_ptr<TrafficSignProperty>> TempleteLoad();
	void  TempleteSift(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps);
	void  TempleteSave(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps);

public:
	void  SampleTempletePreprocessHu();
	void  SampleTestingPreprocessHu(std::vector<std::shared_ptr<TrafficSignPropertyHu>>& _ps);

	std::vector<std::shared_ptr<TrafficSignPropertyHu>> TempleteLoadHu();
	void  TempleteSaveHu(std::vector<std::shared_ptr<TrafficSignPropertyHu>>& _ps);
	void  TempleteHu(std::vector<std::shared_ptr<TrafficSignPropertyHu>>& _ps);
	

};