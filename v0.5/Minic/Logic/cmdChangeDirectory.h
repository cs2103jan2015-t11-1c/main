//@author A0115429H
#pragma once
#include "logicbaseclass.h"

//This cmdChangeDirectory class will change the location of the file saved
class CmdChangeDirectory: public LogicBaseClass {
public:
	CmdChangeDirectory(void);
	~CmdChangeDirectory(void);
	std::string executecmdChangeDirectory(Storage&);
	std::string getFeedback(std::string);
};