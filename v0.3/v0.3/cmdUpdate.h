#pragma once
#include "logicBaseClass.h"
class cmdUpdate :
	public logicBaseClass
{
public:
	cmdUpdate(void);
	~cmdUpdate(void);
	std::string executecmdUpdate();
	std::string updateName(Event, int);
	std::string updateEndingTime(Event, int);
	std::string updateStartingTime(Event, int);
	std::string printFeedback(std::string, Event);
};

