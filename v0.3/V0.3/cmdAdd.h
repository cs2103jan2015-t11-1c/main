//@author A0115429H
#pragma once
#include "logicBaseClass.h"

//This cmdAdd class will add three types of event to the storage:
//Floating task, Deadline task and Timed task
class CmdAdd: public LogicBaseClass{
private:
	Event _newEvent;
public:
	CmdAdd(void);
	~CmdAdd(void);
	std::string executecmdAdd(Storage&);
	std::string addEventWithDeadline(Storage&);
	std::string addEventWithoutDeadline(Storage&);
	std::string addTimedEvent(Storage&);
	std::string printFeedback(Event);
	void updateStorage(Storage&);
};