#pragma once
#include "logicBaseClass.h"
class cmdSearch : public logicBaseClass {
private:
	Eventlist _eventFound;
	std::vector<int> _eventNumbers;
public:
	cmdSearch(void);
	~cmdSearch(void);
	std::string executecmdSearch(Storage& _storage);
	void searchForEvent(std::list<Event>, int);
	std::string printEventFound();
	std::string lowercaseCommandWord(std::string commandWord);
};

