//@author A0114301E
#pragma once
#include "logicBaseClass.h"
class CmdUndo :
	public LogicBaseClass
{
public:
	CmdUndo(void);
	~CmdUndo(void);
	std::string undo(Storage& _storage, std::vector<CommandType>&);
	std::string printUndoMessage();
};

