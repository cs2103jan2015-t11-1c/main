#pragma once
#include "logicBaseClass.h"

class cmdAdd: 
	public logicBaseClass
{
private:
	Event _newEvent;
public:
	cmdAdd(void);
	~cmdAdd(void);
	std::string executecmdAdd();
	std::string addEventWithDeadline();
	std::string addEventWithoutDeadline();
	std::string addTimedEvent();
	std::string printFeedback(Event);
};

