#include "logicBaseClass.h"


logicBaseClass::logicBaseClass(void){
}
logicBaseClass::logicBaseClass(Storage &storage){

}

logicBaseClass::~logicBaseClass(void)
{
}


void logicBaseClass:: initialise(CommandType typeOfCommand, std::string taskName, int startingDate, int startingMonth, int startingTime, int endingDate, int endingMonth, int endingTime, std::list<int> taskNumerlist){
	_commandWord = typeOfCommand;
	_taskName = taskName;
	_startingDate = startingDate;
	_startingMonth = startingMonth;
	_startingTime = startingTime;
	_endingDate = endingDate;
	_endingMonth = endingMonth;
	_endingTime = endingTime;
	_taskNumberList = taskNumerlist;
}
