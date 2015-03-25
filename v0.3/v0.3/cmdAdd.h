#pragma once
#include "logic.h"
class cmdAdd :
	public logic
{
public:
	cmdAdd(void);
	~cmdAdd(void);
	string executecmdAdd();
	string addEventWithDeadline();
	string addEventWithoutDeadline();
	string addTimedEvent();
	string printFeedback(Event);
};

