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
	//Storage _storage;

public:

	//METHODS
	logic();
	logic(CommandType commandWord);
	~logic();
	//void logicStorage ();
	void setCommand (std::string, int, int, int, int, int, int, list<int>);
	std::string executeCommand(CommandType, string, int, int, int, int, int, int, list<int>);
};
#endif
