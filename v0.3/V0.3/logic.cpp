#include "logic.h"
#include <assert.h>
#include <iostream>
const static string EXIT_MESSAGE = "Thank you for using Minik:)";
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

logic::logic(){
	_storage.readFile();
}
logic::logic(CommandType command){
	_commandWord = command;
	_storage.readFile();
}
logic::~logic(){
}
/*
void logic::logicStorage(){
	_storage = Storage();
}
*/
void logic:: setCommand (string taskName, int startingDate, int startingMonth, int startingTime, int endingMonth, int endingDate, int endingTime, list<int> taskNumerlist){
	_taskName = taskName;
	_startingDate = startingDate;
	_startingMonth = startingMonth;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingMonth = endingMonth;
	_endingTime = endingTime;
	_taskNumberList = taskNumerlist;
}

string logic::executeCommand(CommandType command ,string taskName, int startingDate, int startingMonth, int startingTime, int endingDate, int endingMonth, int endingTime, list<int> taskNumerlist){
	_commandWord = command;
	vectorCommand.push_back(command);
	if (command == ADDEVENTWITHDEADLINE || command == ADDFLOATINGEVENT || command == ADDTIMEDEVENT){
		_add.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _add.executecmdAdd(_storage);
	}else if(command == UPDATEENDINGTIME || command == UPDATENAME || command == UPDATESTARTINGTIME){
		_update.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _update.executecmdUpdate(_storage);
	}else if(command == DELETE){
		_delete.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _delete.executecmdDelete(_storage);
	}else if(command == UNDO){
		_undo.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _undo.undo(_storage, vectorCommand);
	}else if(command == CLEAR){
		_clear.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _clear.executeClear(_storage);
	}else if(command == SEARCH){
		_search.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _search.executecmdSearch(_storage);
	}else if(command == DISPLAY){
		_display.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _display.executecmdDisplay(_storage);
	}else if(command == DISPLAYDONE){
		_display.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
	     return _display.cmdDisplayDone(_storage);
	}else if(command == MARKASDONE){
		_markAsDone.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _markAsDone.executeMarkAsDone(_storage);
	}else if(command == HELP){
		return _help.helpMessage();
	}
	return "logic error\n\n";
}


