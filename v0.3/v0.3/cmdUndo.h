#pragma once
#include "logicBaseClass.h"
class cmdUndo :
	public logicBaseClass
{
public:
	cmdUndo(void);
	~cmdUndo(void);
	std::string undo(Storage& _storage);
	std::string printUndoMessage();
};

