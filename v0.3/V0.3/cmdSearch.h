//@author A0114301E
#pragma once
#include "logicBaseClass.h"
class CmdSearch : public LogicBaseClass {
private:
	Eventlist _eventFound;
	std::vector<int> _eventNumbers;
public:
	CmdSearch(void);
	~CmdSearch(void);
	std::string executecmdSearch(Storage& _storage);
	void searchForEvent(std::list<Event>, int);
	std::string printEventFound();
	std::string lowercaseCommandWord(std::string commandWord);
};

