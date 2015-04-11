//@author A0114301E
#pragma once
#include "logicBaseClass.h"

class cmdHelp: 
	public logicBaseClass
{
private:
	
public:
	cmdHelp(void);
	~cmdHelp(void);
	std::string helpMessage();
};