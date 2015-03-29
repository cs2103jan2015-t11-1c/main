#include "cmdAdd.h"
#include <iostream>
using namespace std;

cmdAdd::cmdAdd(void){

}


cmdAdd::~cmdAdd(void){
}

std:: string cmdAdd::executecmdAdd(Storage& storage){
	_storage = storage;
	_newEvent = Event(_taskName, _endingDate, _endingMonth, _endingTime);
	switch (_commandWord)
	{
	case ADDEVENTWITHDEADLINE:	
		return addEventWithDeadline();
	case ADDFLOATINGEVENT:
		return addEventWithoutDeadline();
	case ADDTIMEDEVENT:
		return addTimedEvent();
	default:
		break;
	} 
	return "";
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

std::string cmdAdd::printFeedback(Event newEvent){
	std::string feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n";
	return feedback;
}
