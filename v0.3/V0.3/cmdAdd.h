#pragma once
#include "logicBaseClass.h"
//@author A0115429H
//This cmdAdd class will add three types of event to the storage:
//Floating task, Deadline task and Timed task
class cmdAdd: public logicBaseClass{
private:
	Event _newEvent;
public:
	cmdAdd(void);
	~cmdAdd(void);
	std::string executecmdAdd(Storage&);
	std::string addEventWithDeadline(Storage& _storage);
	std::string addEventWithoutDeadline(Storage& _storage);
	std::string addTimedEvent(Storage& _storage);
	std::string printFeedback(Event);
	void updateStorage(Storage&);
};