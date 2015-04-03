#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Storage.h"


#pragma once
class logicBaseClass
{
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
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATEENDINGTIME, UPDATESTARTINGTIME, DELETE, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, SEARCH, CHANGEDIRECTORY, CLEAREND, CLEARSTART, UNDO, CLEAR, HELP};
	CommandType _commandWord;
	std::vector<CommandType> vectorCommand;
	void initialise (CommandType,std::string, int, int, int, int, int, int, std::list<int>);
	logicBaseClass(void);
	logicBaseClass(Storage &storage);
	~logicBaseClass(void);
};

