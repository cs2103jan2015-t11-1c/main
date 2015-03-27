#pragma once
#include "logic.h"
class cmdUndo :
	public logic
{
public:
	cmdUndo(void);
	~cmdUndo(void);
	string undo();
	string printUndoMessage();
};

