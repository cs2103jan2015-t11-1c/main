#include "cmdAdd.h"
#include <iostream>
using namespace std;

cmdAdd::cmdAdd(void){

}


cmdAdd::~cmdAdd(void){
}

std:: string cmdAdd::executecmdAdd(Storage& _storage){
	_newEvent = Event(_taskName, _endingDate, _endingMonth, _endingTime);
	switch (_commandWord)
	{
	case ADDEVENTWITHDEADLINE:	
		return addEventWithDeadline(_storage);
	case ADDFLOATINGEVENT:
		return addEventWithoutDeadline(_storage);
	case ADDTIMEDEVENT:
		return addTimedEvent(_storage);
	default:
		break;
	} 
	return "";
}

std::string cmdAdd::addEventWithDeadline(Storage& _storage){
	
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	_storage.sortActiveEventlist();
	_storage.synchronizeDrive();
	return _feedback;
}

std::string cmdAdd::addEventWithoutDeadline(Storage& _storage){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	_storage.sortActiveEventlist();
	_storage.synchronizeDrive();
	return _feedback;
}

std::string cmdAdd::addTimedEvent(Storage& _storage){
	_newEvent.changeStartDay(_startingDate);
	_newEvent.changeStartMonth(_startingMonth);
	_newEvent.changeStartTime(_startingTime);
	_storage.addEvent(_newEvent);
	_storage.sortActiveEventlist();
	_storage.synchronizeDrive();
	_feedback = printFeedback(_newEvent);
	return _feedback;
}

std::string cmdAdd::printFeedback(Event newEvent){
	std::string feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n\n";

	return feedback;
}
