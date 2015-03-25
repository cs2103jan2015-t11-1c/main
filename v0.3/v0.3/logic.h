//logic.h
#ifndef logic_H
#define logic_H

#include "Storage.h"
#include "cmdAdd.h";
#include "cmdClear.h";
#include "cmdDelete.h";
#include "cmdDisplay.h";
#include "cmdMarkAsDone.h";
#include "cmdSearch.h";
#include "cmdUndo.h";
#include "cmdUpdate.h";
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class logic{
protected:
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATEENDINGTIME, UPDATESTARTINGTIME, DELETE, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, SEARCH, UNDO, CLEAR, HELP};
	CommandType _commandWord;
	string _taskName;
	string _startingTime;
	string _endingTime;
	int _startingDate;
	int _endingDate;
	MonthType _startingMonth;
	MonthType _endingMonth;
	list<int> _taskNumberList;
	Storage _storage;
	string _feedback;
	cmdAdd _add;
	cmdUpdate _update;
	cmdDisplay _display;
	cmdClear _clear;
	cmdMarkAsDone _markAsDone;
	cmdSearch _search;
	cmdUndo _undo;
	cmdDelete _delete;

public:

	//METHODS
	logic();
	logic(string commandWord, string toDoList);
	~logic();
	void setCommand (string, int, string, int, string, list<int>);
	string exercuteCommand(CommandType, string, int, string, int, string, list<int>);
};
#endif
