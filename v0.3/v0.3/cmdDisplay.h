#pragma once
#include "logic.h"
class cmdDisplay :
	public logic
{
public:
	cmdDisplay(void);
	~cmdDisplay(void);
	string exercutecmdDisplay();
	string cmdDisplayDone();
};

