//@author A0114301E
#include "logic.h"
#include <assert.h>
#include <iostream>
const static std::string EXIT_MESSAGE = "Thank you for using Minik:)";
const static std::string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

Logic::Logic() {
	_storage.readFile();
}

Logic::Logic(CommandType command) {
	_commandWord = command;
	_storage.readFile();
}

Logic::~Logic() {
}

void Logic:: setCommand (std::string taskName, int startingDate, int startingMonth, int startingTime, int endingMonth, int endingDate, int endingTime, list<int> taskNumerlist) {
	_taskName = taskName;
	_startingDate = startingDate;
	_startingMonth = startingMonth;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingMonth = endingMonth;
	_endingTime = endingTime;
	_taskNumberList = taskNumerlist;
}

//taes in command word and execute command
std::string Logic::executeCommand(CommandType command ,string taskName, int startingDate, int startingMonth, int startingTime, int endingDate, int endingMonth, int endingTime, list<int> taskNumerlist) {
	_commandWord = command;
	assert(_commandWord == command);
	vectorCommand.push_back(command);
	if (command == ADDEVENTWITHDEADLINE || command == ADDFLOATINGEVENT || command == ADDTIMEDEVENT) {
		_add.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _add.executecmdAdd(_storage);
	} else if (command == UPDATEENDINGTIME || command == UPDATENAME || command == UPDATESTARTINGTIME || command == CLEARSTART || command == CLEAREND || command == UPDATERECURNAME || command == UPDATERECURSTARTINGTIME || command == UPDATERECURENDINGTIME) {
		_update.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _update.executecmdUpdate(_storage);
	} else if (command == DELETE || command == DELETERECUR) {
		_delete.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _delete.executecmdDelete(_storage);
	} else if (command == UNDO) {
		_undo.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _undo.undo(_storage, vectorCommand);
	} else if (command == CLEAR) {
		_clear.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _clear.executeClear(_storage);
	} else if (command == SEARCH) {
		_search.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _search.executecmdSearch(_storage);
	} else if (command == DISPLAY || command == DISPLAYTODAY || command == DISPLAYDONE || command == DISPLAYALL || command == DISPLAYTOMORROW ) {
		_display.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _display.executecmdDisplay(_storage);
	} else if (command == MARKASDONE) {
		_markAsDone.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _markAsDone.executeMarkAsDone(_storage);
	} else if (command == HELP) {
		return _help.helpMessage();
	} else if (command == CHANGEDIRECTORY) {
		_changeDirectory.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _changeDirectory.executecmdChangeDirectory(_storage);
	} else if (command == REPEAT || REPEATDONE) {
		_repeat.initialise(command, taskName, startingDate, startingMonth, startingTime, endingDate, endingMonth, endingTime, taskNumerlist);
		return _repeat.executecmdRepeat(_storage);
	}
}

