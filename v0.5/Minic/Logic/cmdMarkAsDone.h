//@author A0114301E

#pragma once
#include "logicBaseClass.h"

//This class marks one task or multiple classes as done
//user input: done 1
//done 1 2 3
class CmdMarkAsDone : public LogicBaseClass {
public:
	CmdMarkAsDone(void);
	~CmdMarkAsDone(void);
	std::string executeMarkAsDone(Storage& _storage);
	std::string printFeedback(std::list<int>, Storage& _storage);
};

