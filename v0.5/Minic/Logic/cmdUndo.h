//@author A0114301E

//This undo class performs undo action, which allows user to 
//recover last action (as long as there is action to undo)
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

