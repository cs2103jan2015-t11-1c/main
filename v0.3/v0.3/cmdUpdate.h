#pragma once
#include "logic.h"
class cmdUpdate :
	public logic
{
public:
	cmdUpdate(void);
	~cmdUpdate(void);
	string executecmdUpdate();
	string updateName(Event, int);
	string updateEndingTime(Event, int);
	string updateStartingTime(Event, int);
	string printFeedback(string, Event);
};

