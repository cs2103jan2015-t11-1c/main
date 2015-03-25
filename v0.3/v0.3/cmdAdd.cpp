#include "cmdAdd.h"

cmdAdd::cmdAdd(void){
}


cmdAdd::~cmdAdd(void){
}

string cmdAdd::executecmdAdd(){
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
}

string cmdAdd::addEventWithDeadline(){
	Event newEvent = Event(_taskName, _endingDate, _endingMonth, _endingTime); //need to change
	_storage.addEvent(newEvent);
	_feedback = printFeedback(newEvent);
	return _feedback;
}

string cmdAdd::addEventWithoutDeadline(){
	Event newEvent = Event(_taskName, "", ""); //need to change
	_storage.addEvent(newEvent);
	_feedback = printFeedback(newEvent);
	return _feedback;
}

string cmdAdd::addTimedEvent(){
	Event newEvent = Event(_taskName, _startingDate, _startingTime, _endingDate, _endingTime); //need to change!
	_storage.addEvent(newEvent);
	_feedback = printFeedback(newEvent);
	return _feedback;
}

string cmdAdd::printFeedback(Event event){
	string feedback = "\"" + event.readEvent() + "\" is added successfully.\n";
	return feedback;
}
