#include "TrafficSignTemplete.hpp"
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignTemplete::TrafficSignTemplete(void)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
TrafficSignTemplete::~TrafficSignTemplete(void)
{
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignTemplete::setTrafficSignParam(TrafficSignParam * _p)
{
	this->mParam = _p;
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignTemplete::SampleTempletePreprocess()
{
	std::vector<std::string>  paths= mParam->getSampleTempletePaths();
	
	const int pSz = paths.size();

	for (size_t pi = 0; pi < pSz; pi++){

				std::string  path_t=paths.at(pi);
				std::vector<std::string> files;
				Base::FS_getFiles(path_t, "png", files);
	
				const int fSz = files.size();

				for (size_t fi = 0; fi < fSz; fi++){
								TrafficSignMethod tsm;
								tsm.LoadImage(files.at(fi));
								tsm.cutTempleteArea(this->mParam->getBlockSize());
								tsm.saveTempleteAreaImage();
				}

	}
	
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignTemplete::SampleTestingPreprocess(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps)
{
	std::vector<std::string>  paths = mParam->getSampleTestingPaths();

	const int pSz = paths.size();

	for (size_t pi = 0; pi < pSz; pi++) {

		std::string  path_t = paths.at(pi);
		std::vector<std::string> files;
		Base::FS_getFiles(path_t, "png", files);

		const int fSz = files.size();

		for (size_t fi = 0; fi < fSz; fi++) {
			TrafficSignMethod tsm;
			tsm.LoadImage(files.at(fi));
			tsm.cutTempleteArea(this->mParam->getBlockSize());
			
			std::vector<std::shared_ptr<TrafficSignProperty>> pp=tsm.ImgFragProcSift();
			
			tsm.MatchSift(_ps,pp);
			

		}

	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
std::vector<std::shared_ptr<TrafficSignProperty>> TrafficSignTemplete::TempleteLoad()
{
	std::vector<std::string>  paths = mParam->getTempletePaths();

	const int pSz = paths.size();

	std::vector<std::shared_ptr<TrafficSignProperty>>   properties;

	for (size_t pi = 0; pi < pSz; pi++) {

		std::string  path_t = paths.at(pi);
		std::vector<std::string> files;
		Base::FS_getFiles(path_t, "png", files);

		const int fSz = files.size();

		for (size_t fi = 0; fi < fSz; fi++) {
			TrafficSignMethod tsm;
			tsm.LoadImage(files.at(fi));
			tsm.cutTempleteArea(this->mParam->getBlockSize());
			std::shared_ptr<TrafficSignProperty>  p=tsm.getTrafficSignMax();
			
			if (p!=nullptr){
				properties.push_back(p);
			}

			
		}

	}

	return properties;

}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignTemplete::TempleteSift(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps)
{
	const int pSz = _ps.size();
	for (size_t pi = 0; pi < pSz; pi++) {
		std::shared_ptr<TrafficSignProperty>  p = _ps.at(pi);
		p->imgProcSift();
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/
void TrafficSignTemplete::TempleteSave(std::vector<std::shared_ptr<TrafficSignProperty>>& _ps)
{
	const std::string path = "TrafficSignImgProc//";

	Base::FS_createDir(path);

	const int pSz = _ps.size();
	for (size_t pi = 0; pi < pSz; pi++) {
		std::shared_ptr<TrafficSignProperty>  p = _ps.at(pi);

		p->saveImgResult(path);
	}
}
/*-----------------------------------------*/
/**
*
*/
/*-----------------------------------------*/