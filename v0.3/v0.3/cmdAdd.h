#pragma once
#include "logic.h"
class cmdAdd :
	public logic
{
private:
	Event _newEvent;
public:
	cmdAdd(void);
	~cmdAdd(void);
	string executecmdAdd();
	string addEventWithDeadline();
	string addEventWithoutDeadline();
	string addTimedEvent();
	string printFeedback(Event);
};

