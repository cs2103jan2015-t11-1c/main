//@author A0114301E
#pragma once
#include "logicBaseClass.h"
class cmdUndo :
	public logicBaseClass
{
public:
	cmdUndo(void);
	~cmdUndo(void);
	std::string undo(Storage& _storage, std::vector<CommandType>&);
	std::string printUndoMessage();
};

