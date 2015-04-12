//@author A0115429H
#pragma once
#include "logicbaseclass.h"

//This cmdChangeDirectory class will change the location of the file saved
class cmdChangeDirectory: public logicBaseClass {
public:
	cmdChangeDirectory(void);
	~cmdChangeDirectory(void);
	std::string executecmdChangeDirectory(Storage&);
	std::string getFeedback(std::string);
};