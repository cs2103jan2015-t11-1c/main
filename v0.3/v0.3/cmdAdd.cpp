#include "cmdAdd.h"

cmdAdd::cmdAdd(void){
	_newEvent = Event(_taskName, _endingDate, _endingMonth, _endingTime);
}


cmdAdd::~cmdAdd(void){
}

std:: string cmdAdd::executecmdAdd(){
	switch (_commandWord)
	{
	case ADDEVENTWITHDEADLINE:
		_feedback = addEventWithDeadline();
	case ADDFLOATINGEVENT:
		_feedback = addEventWithoutDeadline();
	case ADDTIMEDEVENT:
		_feedback = addTimedEvent();
	default:
		break;
	} 
	return _feedback;
}

std::string cmdAdd::addEventWithDeadline(){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	return _feedback;
}

std::string cmdAdd::addEventWithoutDeadline(){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	return _feedback;
}

std::string cmdAdd::addTimedEvent(){
	_newEvent.changeStartDay(_startingDate);
	_newEvent.changeStartMonth(_startingMonth);
	_newEvent.changeStartTime(_startingTime);
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	return _feedback;
}

std::string cmdAdd::printFeedback(Event event){
	std::string feedback = "\"" + event.readEvent() + "\" is added successfully.\n";
	return feedback;
}
