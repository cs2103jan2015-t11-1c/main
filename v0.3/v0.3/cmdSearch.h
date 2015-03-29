#pragma once
#include "logicBaseClass.h"
class cmdSearch :
	public logicBaseClass
{
private:
	Eventlist _eventFound;
public:
	cmdSearch(void);
	~cmdSearch(void);
	std::string executecmdSearch(Storage& _storage);
	std::string printEventFound();
};

