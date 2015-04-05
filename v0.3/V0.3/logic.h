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
class logic :
public logicBaseClass
{
private:	
	cmdAdd _add;
	cmdUpdate _update;
	cmdDisplay _display;
	cmdClear _clear;
	cmdMarkAsDone _markAsDone;
	cmdSearch _search;
	cmdUndo _undo;
	cmdDelete _delete;
	cmdHelp _help;
	cmdChangeDirectory _changeDirectory;
	cmdRepeat _repeat;
	//Storage _storage;

public:

	//METHODS
	logic();
	logic(CommandType commandWord);
	~logic();
	//void logicStorage ();
	void setCommand (std::string, int, int, int, int, int, int, list<int>);
	std::string executeCommand(CommandType, std::string, int, int, int, int, int, int, list<int>);
};
#endif
