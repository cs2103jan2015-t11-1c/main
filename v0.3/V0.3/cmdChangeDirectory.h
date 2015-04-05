#pragma once
#include "logicbaseclass.h"
class cmdChangeDirectory :
	public logicBaseClass
{
public:
	cmdChangeDirectory(void);
	~cmdChangeDirectory(void);
	std::string executecmdChangeDirectory(Storage& _storage);
	std::string getFeedback(std::string);
};