//@author A0114301E
#include "cmdUndo.h"

const static std::string UNDO_ERROR_MESSAGE = "There is no action to undo. Enter a command again.\n\n";
const static std::string UNDO_MESSAGE = "Undo last action successfully\n\n";
const static std::string UNDO_UNSUCCESSFUL_MESSAGE = "Undo unsuccessful\n\n";
const static std::string STRING_ADD = "add";
const static std::string STRING_DELETE = "delete";
const static std::string STRING_UPDATE = "update";
const static std::string STRING_CLEAR = "clear";
const static std::string STRING_DONE = "done";
const static std::string STRING_REPEAT = "update repeat";
const static std::string STRING_UPDATE_RECUR = "update repeat";
const static std::string STRING_DELETE_RECUR = "delete repeat";



cmdUndo::cmdUndo(void)
{
	noOfCommand = 0;
}


cmdUndo::~cmdUndo(void)
{
}

std::string cmdUndo::printUndoMessage(){
	return UNDO_MESSAGE;
}

//undo last command based on the last command word from the user
//support undo for last two actions
std::string cmdUndo::undo(Storage& _storage,std::vector<CommandType>& commandStored){
	CommandType lastCommand = commandStored.back();
	if(commandStored.size() <= 1) {
		return UNDO_UNSUCCESSFUL_MESSAGE;
	}
	commandStored.pop_back();
	while ((lastCommand == UNDO  || lastCommand == DISPLAY || lastCommand == DISPLAYDONE) && commandStored.size() > 0){
		lastCommand = commandStored.back();
		commandStored.pop_back();
	}
	std::string lastCommandString;
	if(lastCommand == ADDEVENTWITHDEADLINE || lastCommand == ADDFLOATINGEVENT || lastCommand == ADDTIMEDEVENT){
		lastCommandString = STRING_ADD;
	} else if (lastCommand == DELETE) {
		lastCommandString = STRING_DELETE;
	} else if (lastCommand == UPDATEENDINGTIME || lastCommand == UPDATENAME || lastCommand == UPDATESTARTINGTIME || lastCommand == CLEAREND || lastCommand == CLEARSTART) {
		lastCommandString = STRING_UPDATE;
	} else if (lastCommand == CLEAR) {
		lastCommandString = STRING_CLEAR;
	} else if (lastCommand == MARKASDONE) {
		lastCommandString = STRING_DONE;
	} else if (lastCommand == DISPLAY) {
		std::cout<<UNDO_ERROR_MESSAGE;
	} else if (lastCommand == HELP) {
		std::cout<<UNDO_ERROR_MESSAGE;
	} else if (lastCommand == REPEAT) {
		lastCommandString = STRING_REPEAT;
	} else if (lastCommand == DELETERECUR) {
		lastCommandString = STRING_DELETE_RECUR;
	} else if (lastCommand == UPDATERECURENDINGTIME || lastCommand == UPDATERECURSTARTINGTIME || lastCommand == UPDATERECURNAME){
		lastCommandString = STRING_UPDATE_RECUR;
	} else {
		return UNDO_UNSUCCESSFUL_MESSAGE;
	}
	if (_storage.unDopreviousActions(lastCommandString)) {	
		_storage.synchronizeDrive();
		return printUndoMessage();
	} else{
		return UNDO_UNSUCCESSFUL_MESSAGE;
	}
}

