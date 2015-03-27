#pragma once
#include "logic.h"
class cmdDelete :
	public logic
{
public:
	cmdDelete(void);
	~cmdDelete(void);
	string executecmdDelete();
	string printFeedback(list<int>);
};

