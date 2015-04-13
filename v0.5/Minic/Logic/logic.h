//@author A0114301E
//logic.h
#ifndef logic_H
#define logic_H

#include "cmdAdd.h"
#include "cmdClear.h"
#include "cmdDelete.h"
#include "cmdDisplay.h"
#include "cmdMarkAsDone.h"
#include "cmdSearch.h"
#include "cmdUndo.h"
#include "cmdUpdate.h"
#include "cmdHelp.h"
#include "cmdChangeDirectory.h"
#include "cmdRepeat.h"

using namespace std;
class Logic : public LogicBaseClass {
private:	
	CmdAdd _add;
	CmdUpdate _update;
	CmdDisplay _display;
	CmdClear _clear;
	CmdMarkAsDone _markAsDone;
	cmdSearch _search;
	CmdUndo _undo;
	CmdDelete _delete;
	CmdHelp _help;
	CmdChangeDirectory _changeDirectory;
	CmdRepeat _repeat;
	//Storage _storage;

public:

	//METHODS
	Logic();
	Logic(CommandType commandWord);
	~Logic();
	//void logicStorage ();
	void setCommand (std::string, int, int, int, int, int, int, list<int>);
	std::string executeCommand(CommandType, std::string, int, int, int, int, int, int, list<int>);
};
#endif
