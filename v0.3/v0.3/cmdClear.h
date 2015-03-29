#pragma once
#include "logicBaseClass.h"
class cmdClear :
	public logicBaseClass
{
public:
	cmdClear(void);
	~cmdClear(void);
	std::string executeClear();
};

