#pragma once
#include "logic.h"
class cmdClear :
	public logic
{
public:
	cmdClear(void);
	~cmdClear(void);
	std::string clear();
};

