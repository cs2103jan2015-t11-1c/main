#include "cmdAdd.h"
#include <iostream>
#include <sstream>

const static std::string CLASH_MESSAGE = "Reminder: You will be doing something else at this time. You may want to reschedule.\n";
const static std::string ADD_SUCCESSFUL_MESSAGE = "\" is added successfully.\n\n";

cmdAdd::cmdAdd(void){
}


cmdAdd::~cmdAdd(void){
}

//add event with deadline, floating task or timed event
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

	updateStorage();
	return "";
}

std::string cmdAdd::addEventWithDeadline(Storage& _storage){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	return _feedback;
}

std::string cmdAdd::addEventWithoutDeadline(Storage& _storage){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	return _feedback;
}

//check for clash for timed tasks 
//print a reminder messge if there there is an existing task at that time
//task will still be added if there is a clash
std::string cmdAdd::addTimedEvent(Storage& _storage){
	Eventlist events = _storage.displayEvent();
	std::list<Event> allEvents = events.returnAllEvent();
	int startingMonth = _startingMonth;
	int startingDate = _startingDate;
	int startingTime = _startingTime;
	int endingTime = _endingTime;
	
	std::list<Event>::iterator Tcount;
	Event currentEvent;
	for(Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++){
		currentEvent = *Tcount;
		int startMonth = currentEvent.getStartMonth();
		int startDate = currentEvent.getStartDate();
		int startTime = currentEvent.getStartTime();
		int endTime = currentEvent.getEndTime();
		if (startMonth == startingMonth && startDate == startingDate && startingTime >= startTime && startingTime <= endTime) {
			std::cout << CLASH_MESSAGE;
			break;
		}
	}
	_newEvent.changeStartDay(_startingDate);
	_newEvent.changeStartMonth(_startingMonth);
	_newEvent.changeStartTime(_startingTime);
	_storage.addEvent(_newEvent);

	_feedback = printFeedback(_newEvent);	
	return _feedback;
}

std::string cmdAdd::printFeedback(Event newEvent){
	std::string feedback = "\"" + newEvent.displayEvent() + ADD_SUCCESSFUL_MESSAGE;
	return feedback;
}

void cmdAdd::updateStorage(){
	_storage.sortActiveEventlist();
	_storage.synchronizeDrive();
}