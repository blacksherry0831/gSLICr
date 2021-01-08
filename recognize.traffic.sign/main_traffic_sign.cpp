/*----------------------------------------------------------------*/
#include "opencv_basic.h"
#include "cpp_def.h"
/*----------------------------------------------------------------*/
#include "TrafficSignParam.hpp"
#include "TrafficSignMethod.hpp"
#include "TrafficSignTemplete.hpp"
/*----------------------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void processTemplete()
{
	const std::string path_st = "X:\\ImageDataBase\\TrafficSignSample\\Template";
	
	TrafficSignParam param;
	param.setSampleTempletePath(path_st);

	TrafficSignTemplete temp;
	temp.setTrafficSignParam(&param);
	
	temp.SampleTempletePreprocess();

	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
void loadTemplete()
{
	const std::string path = "X:\\ImageDataBase\\\TrafficSignSample\\TrafficSignTemplate";

	const std::string path_st = "X:\\ImageDataBase\\TrafficSignSample\\Testing";

	TrafficSignParam param;
	param.setTempletePath(path);
	param.setSampleTestingPath(path_st);

	TrafficSignTemplete temp;
	temp.setTrafficSignParam(&param);
	
	std::vector<std::shared_ptr<TrafficSignProperty>> properties=temp.TempleteLoad();
	
	temp.TempleteSift(properties);

	temp.TempleteSave(properties); 

	temp.SampleTestingPreprocess(properties);
	
}
/*----------------------------------------------------------------*/
/**
*
*/
/*----------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	processTemplete();

	loadTemplete();
			
	return  0;
}
/*----------------------------------------------------------------*/
/**
*
*/
/*-----------------------------------------------------------------*/