#pragma once
#include "logicBaseClass.h"
class cmdDelete :
	public logicBaseClass
{
public:
	cmdDelete(void);
	~cmdDelete(void);
	std::string executecmdDelete();
	std::string printFeedback(std::list<int>);
};

