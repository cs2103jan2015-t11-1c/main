#include "cmdUndo.h"
#include "UI.h"

const static std::string UNDO_ERROR_MESSAGE = "There is no action to undo. Enter a command again.";
const static std::string BLANK_LINES = "\n\n";

cmdUndo::cmdUndo(void)
{
	noOfCommand = 0;
}


cmdUndo::~cmdUndo(void)
{
}

string cmdUndo::printUndoMessage(){
	return "Undo last action successfully\n\n";
}

//undo last command based on the last command word from the user
string cmdUndo::undo(Storage& _storage,std::vector<CommandType> commandStored){
	CommandType lastCommand = commandStored.back();
	if(lastCommand == UNDO && commandStored.size()==1){
		return UNDO_ERROR_MESSAGE + BLANK_LINES;
	}
	else{
	while (lastCommand == UNDO || lastCommand == DISPLAY || lastCommand == DISPLAYDONE){
		commandStored.pop_back();
		lastCommand = commandStored.back();
	}
	commandStored.pop_back();
	std::string lastCommandString;

	if(lastCommand == ADDEVENTWITHDEADLINE || lastCommand == ADDFLOATINGEVENT || lastCommand == ADDTIMEDEVENT){
		lastCommandString = "add";
	}else if(lastCommand == DELETE){
		lastCommandString = "delete";
	}else if(lastCommand == UPDATEENDINGTIME || lastCommand == UPDATENAME || lastCommand == UPDATESTARTINGTIME){
		lastCommandString = "update";
	}else if(lastCommand == CLEAR){
		lastCommandString = "clear";
	}else if(lastCommand == MARKASDONE){
		lastCommandString = "done";
	}
	if (_storage.unDopreviousActions(lastCommandString)) {	
	_storage.synchronizeDrive();
	return printUndoMessage();}
	else return "Undo unsuccessful\n\n";
	}
}