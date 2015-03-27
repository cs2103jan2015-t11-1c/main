#include "logic.h"
#include <assert.h>
#include <iostream>
const static string EXIT_MESSAGE = "Thank you for using Minik:)";
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

logic::logic(){
	_storage = Storage();
}

/*logic::logic(string commandWord, string toDoList){
	_commandWord = commandWord;
	_toDoList = toDoList;
}*/

logic::~logic(){
}

void logic:: setCommand (string taskName, int startingDate, int startingMonth, int startingTime, int endingMonth, int endingDate, int endingTime, list<int> taskNumerlist){
	_taskName = taskName;
	_startingDate = startingDate;
	_startingMonth = startingMonth;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_startingMonth = startingMonth;
	_endingTime = endingTime;
	_taskNumberList = taskNumerlist;
}

string logic::executeCommand(CommandType command ,string taskName, int startingDate, int startingMonth, int startingTime, int endingDate, int endingMonth, int endingTime, list<int> taskNumerlist){
	setCommand(taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
	if (command == ADDEVENTWITHDEADLINE || command == ADDFLOATINGEVENT || command == ADDTIMEDEVENT){
		return _add.executecmdAdd();
	}else if(command == UPDATEENDINGTIME || command == UPDATENAME || command == UPDATESTARTINGTIME){
		return _update.executecmdUpdate();
	}else if(command == DELETE){
		return _delete.executecmdDelete();
	}else if(command == UNDO){
		return _undo.undo();
	}else if(command == CLEAR){
		return _clear.executeClear();
	}else if(command == SEARCH){
		return _search.executecmdSearch();
	}else if(command == DISPLAY){
		return _display.executecmdDisplay();
	}else if(command == MARKASDONE){
		return _markAsDone.exercuteMarkAsDone();
	}
}


