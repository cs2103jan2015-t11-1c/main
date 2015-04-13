//@author A0114301E
#pragma once
#include "logicBaseClass.h"

//This cmdClear class will clear all the tasks in the file
class CmdClear : public LogicBaseClass {
public:
	CmdClear(void);
	~CmdClear(void);
	std::string executeClear(Storage&);
};