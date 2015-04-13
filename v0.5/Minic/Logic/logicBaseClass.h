//@author A0114301E
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Storage\Storage.h"

#pragma once
class LogicBaseClass {
protected:
	std::string _taskName;
	int _startingTime;
	int _endingTime;
	int _startingDate;
	int _endingDate;
	int _startingMonth;
	int _endingMonth;
	std::list<int> _taskNumberList;
	Storage _storage;
	std::string _feedback;
	int noOfCommand;

public:
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATERECURNAME, UPDATEENDINGTIME, UPDATERECURENDINGTIME, UPDATESTARTINGTIME, UPDATERECURSTARTINGTIME, DELETE, DELETERECUR, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, DISPLAYTOMORROW, DISPLAYALL, SEARCH, UNDO, CLEAR, CLEAREND, CLEARRECUREND, CLEARSTART, CLEARRECURSTART, CHANGEDIRECTORY, HELP, EXIT, REPEAT, REPEATDONE};
	CommandType _commandWord;
	std::vector<CommandType> vectorCommand;
	void initialise (CommandType,std::string, int, int, int, int, int, int, std::list<int>);
	LogicBaseClass(void);
	LogicBaseClass(Storage &storage);
	~LogicBaseClass(void);
};

