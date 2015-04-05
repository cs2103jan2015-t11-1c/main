#pragma once
#include "logicBaseClass.h"
class cmdMarkAsDone :
	public logicBaseClass
{
public:
	cmdMarkAsDone(void);
	~cmdMarkAsDone(void);
	std::string executeMarkAsDone(Storage& _storage);
	std::string printFeedback(std::list<int>, Storage& _storage);
};

