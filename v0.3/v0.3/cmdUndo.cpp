#include "cmdUndo.h"
#include "UI.h"


cmdUndo::cmdUndo(void)
{
	noOfCommand = 0;
}


cmdUndo::~cmdUndo(void)
{
}

string cmdUndo::printUndoMessage(){
	return "Undo last action successfully";
}

//undo last command based on the last command word from the user
string cmdUndo::undo(){
	CommandType lastCommand = vectorCommand[noOfCommand];
	if(lastCommand == ADDEVENTWITHDEADLINE || lastCommand == ADDFLOATINGEVENT || lastCommand == ADDTIMEDEVENT){
		_storage.unDoAddEvent();
		//printUndoMessage();
	}else if(lastCommand == DELETE){
		_storage.unDoDeleteEvent();
		//printUndoMessage();
	}else if(lastCommand == UPDATEENDINGTIME || lastCommand == UPDATENAME || lastCommand == UPDATESTARTINGTIME){
		_storage.unDoUpdateEvent();
		//printUndoMessage();
	}else if(lastCommand == CLEAR){
		_storage.unDoClearActiveEvent();
		_storage.unDoClearDoneEvent();
		//printUndoMessage();
	}else if(lastCommand == MARKASDONE){
		_storage.unDomarkEventAsDone();
		//printUndoMessage();
	}
		return printUndoMessage();
	}