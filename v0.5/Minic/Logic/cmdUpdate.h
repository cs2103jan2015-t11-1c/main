//@author A0114301E

//This Update class updates tasks
//attributes can be updated including:
//task name, ending date&time, starting date&time, remove starting time,
//remove ending time
#pragma once
#include "logicBaseClass.h"
class CmdUpdate : public LogicBaseClass {
public:
	CmdUpdate(void);
	~CmdUpdate(void);
	std::string executecmdUpdate(Storage&);
	std::string updateName(Event, int, Storage&);
	std::string updateEndingTime(Event, int, Storage&);
	std::string updateStartingTime(Event, int, Storage&);
	std::string clearStartingTime(Event, int, Storage&);
	std::string clearEndingTime(Event, int, Storage&);
	std::string updateRecurringName(Event, int, Storage&);
	std::string updateRecurringStartTime(int, Storage&);
	std::string updateRecurringEndTime(int, Storage&);
	std::string printFeedback(std::string, Event);
	void updateStorage(Storage& _storage);
};
