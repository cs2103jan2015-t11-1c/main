#pragma once
#include "logicBaseClass.h"
class cmdDisplay :
	public logicBaseClass
{
public:
	cmdDisplay(void);
	~cmdDisplay(void);
	bool isEmptyEventsStorage(Storage& _storage);
	std::string executecmdDisplay(Storage& _storage);
	std::string cmdDisplayDone(Storage& _storage);
	std::string cmdDisplayActive(Storage& _storage);
	std::string cmdDisplayToday(Storage& _storage);
};

