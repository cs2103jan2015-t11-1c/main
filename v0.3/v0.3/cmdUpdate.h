#pragma once
#include "logicBaseClass.h"
class cmdUpdate :
	public logicBaseClass
{
public:
	cmdUpdate(void);
	~cmdUpdate(void);
	std::string executecmdUpdate(Storage&);
	std::string updateName(Event, int, Storage&);
	std::string updateEndingTime(Event, int, Storage&);
	std::string updateStartingTime(Event, int, Storage&);
	std::string printFeedback(std::string, Event);
};

