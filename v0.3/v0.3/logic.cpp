#include "logic.h"
#include <assert.h>
#include <iostream>
const static string EXIT_MESSAGE = "Thank you for using Minik:)";
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

logic::logic(){
	//logicStorage();
}
logic::logic(CommandType command){
	_commandWord = command;
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
	if (command == ADDEVENTWITHDEADLINE || command == ADDFLOATINGEVENT || command == ADDTIMEDEVENT){
		_add.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _add.executecmdAdd(_storage);
	}else if(command == UPDATEENDINGTIME || command == UPDATENAME || command == UPDATESTARTINGTIME){
		_update.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _update.executecmdUpdate();
	}else if(command == DELETE){
		_delete.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _delete.executecmdDelete();
	}else if(command == UNDO){
		_undo.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _undo.undo();
	}else if(command == CLEAR){
		_clear.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _clear.executeClear();
	}else if(command == SEARCH){
		_search.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _search.executecmdSearch();
	}else if(command == DISPLAY){
		_display.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _display.executecmdDisplay();
	}else if(command == MARKASDONE){
		_markAsDone.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _markAsDone.exercuteMarkAsDone();
	}
	return "logic error";
}


