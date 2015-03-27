#pragma once
#include "logic.h"
class cmdDisplay :
	public logic
{
public:
	cmdDisplay(void);
	~cmdDisplay(void);
	string executecmdDisplay();
	string cmdDisplayDone();
	string cmdDisplayActive();
	string cmdDisplayToday();
};

