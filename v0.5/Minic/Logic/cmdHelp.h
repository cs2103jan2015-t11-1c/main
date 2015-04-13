//@author A0114301E
#pragma once
#include "logicBaseClass.h"

//This class displays help function for user to see all commands available
class CmdHelp: public LogicBaseClass {
private:
	
public:
	CmdHelp(void);
	~CmdHelp(void);
	std::string helpMessage();
};