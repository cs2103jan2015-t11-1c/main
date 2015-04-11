//@author A0115429H
#pragma once
#include "logicBaseClass.h"
#include <ctime>
class cmdDisplay : public logicBaseClass {
public:
	cmdDisplay(void);
	~cmdDisplay(void);
	bool isEmptyEventsStorage(Storage& _storage);
	std::string executecmdDisplay(Storage& _storage);
	std::string cmdDisplayDone(Storage& _storage);
	std::string cmdDisplayActive(Storage& _storage);
	std::string cmdDisplayToday(Storage& _storage);
	std::string cmdDisplayTomorrow(Storage& _storage);
	std::string cmdDisplayAll(Storage& _storage);
	bool isEventToday(int taskStartMonth, int taskStartDay, int taskEndMonth, int taskEndDay);
	bool isEventTomorrow(int taskStartMonth, int taskStartDay, int taskEndMonth, int taskEndDay);
	std::string eventsToDisplay(std::list<Event> events);
	std::string allEvents(std::list<Event> events);
};
