#pragma once
#include "logic.h"
class cmdAdd :
	public logic
{
public:
	cmdAdd(void);
	~cmdAdd(void);
	string exercutecmdAdd();
	string addEventWithDeadline();
	string addEventWithoutDeadline();
	string addTimedEvent();
};

