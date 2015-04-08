#pragma once
#include "logicBaseClass.h"

//This cmdClear class will clear all the tasks in the file
class cmdClear : public logicBaseClass {
public:
	cmdClear(void);
	~cmdClear(void);
	std::string executeClear(Storage&);
};