//@author A0114301E
#pragma once
#include "logicBaseClass.h"

//This cmdDelete class will delete one task or multiple tasks
class cmdDelete: public logicBaseClass {
public:
	cmdDelete(void);
	~cmdDelete(void);
	std::string executecmdDelete(Storage& _storage);
	std::string printFeedback(std::list<int>, Storage& _storage);
	std::string deleteRecurringEvents(std::list<int>, Storage&);
};