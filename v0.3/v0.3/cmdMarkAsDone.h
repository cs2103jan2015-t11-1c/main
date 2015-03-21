#pragma once
#include "logic.h"
class cmdMarkAsDone :
	public logic
{
public:
	cmdMarkAsDone(void);
	~cmdMarkAsDone(void);
	string exercuteMarkAsDone();
};

