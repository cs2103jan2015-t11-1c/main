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
//need to modified
void logic:: setCommand (string taskName, int startingDate, string startingTime, int endingDate, string endingTime, list<int> taskNumerlist){
	_taskName = taskName;
	_startingDate = startingDate;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingTime = endingTime;
	_taskNumberList = taskNumerlist;
}

string logic::exercuteCommand(CommandType command ,string taskName, int startingDate, string startingTime, int endingDate, string endingTime, list<int> taskNumerlist){
	setCommand(taskName, startingDate, startingTime, endingDate, endingTime, taskNumerlist);
	if (command == ADDEVENTWITHDEADLINE || command == ADDFLOATINGEVENT || command == ADDTIMEDEVENT){
		return _add.executecmdAdd();
	}else if(command == UPDATEENDINGTIME || command == UPDATENAME || command == UPDATESTARTINGTIME){
		return _update.executecmdUpdate();
	}else if(command == DELETE){
		return _delete.executecmdDelete();
	}
}


