//@author A0114301E
#include "logicBaseClass.h"
#include <assert.h>

LogicBaseClass::LogicBaseClass(void) {
}

LogicBaseClass::LogicBaseClass(Storage &storage) {

}

LogicBaseClass::~LogicBaseClass(void) {
}


void LogicBaseClass:: initialise(CommandType typeOfCommand, std::string taskName, int startingDate, int startingMonth, int startingTime, int endingDate, int endingMonth, int endingTime, std::list<int> taskNumerlist) {
	_commandWord = typeOfCommand;
	assert(_commandWord == typeOfCommand);
	_taskName = taskName;
	_startingDate = startingDate;
	_startingMonth = startingMonth;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingMonth = endingMonth;
	_endingTime = endingTime;
	_taskNumberList = taskNumerlist;
}
