#pragma once
#include "logicBaseClass.h"
class cmdDisplay :
	public logicBaseClass
{
public:
	cmdDisplay(void);
	~cmdDisplay(void);
	std::string executecmdDisplay();
	std::string cmdDisplayDone();
	std::string cmdDisplayActive();
	std::string cmdDisplayToday();
};

