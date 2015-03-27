#pragma once
#include "logic.h"
class cmdSearch :
	public logic
{
private:
	Eventlist _eventFound;
public:
	cmdSearch(void);
	~cmdSearch(void);
	string executecmdSearch();
	string printEventFound();
};

