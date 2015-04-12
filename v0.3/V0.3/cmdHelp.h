//@author A0114301E
#pragma once
#include "logicBaseClass.h"

class CmdHelp: public LogicBaseClass {
private:
	
public:
	CmdHelp(void);
	~CmdHelp(void);
	std::string helpMessage();
};