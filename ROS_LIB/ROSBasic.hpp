#pragma once
/*-----------------------------------*/
#include "cpp_stl.h"
/*-----------------------------------*/
#include <QtCore>
/*-----------------------------------*/
/**
*
*/
/*-----------------------------------*/
class ROSBasic
{

public:
	ROSBasic();
	~ROSBasic();
public:	
	static QString Json2Str(const QJsonObject _q_jo);
	static QString Json2Str(const QJsonArray _q_ja);



};