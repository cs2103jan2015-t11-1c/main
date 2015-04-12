//@author A0114301E
#pragma once
#include "logicBaseClass.h"
class CmdMarkAsDone : public LogicBaseClass {
public:
	CmdMarkAsDone(void);
	~CmdMarkAsDone(void);
	std::string executeMarkAsDone(Storage& _storage);
	std::string printFeedback(std::list<int>, Storage& _storage);
};

