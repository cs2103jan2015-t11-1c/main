#pragma once
#include "logicBaseClass.h"
class cmdMarkAsDone :
	public logicBaseClass
{
public:
	cmdMarkAsDone(void);
	~cmdMarkAsDone(void);
	std::string exercuteMarkAsDone(Storage& _storage);
};

