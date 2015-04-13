//@author A0115429H
#include "cmdAdd.h"
#include <iostream>
#include <sstream>
#include <assert.h>

const static std::string CLASH_MESSAGE = "Reminder: You will be doing something else at this time. You may want to reschedule.\n";
const static std::string ADD_SUCCESSFUL_MESSAGE = "\" is added successfully.\n\n";
const static std::string QUOTATION_MARKS = "\"";
const static std::string EMPTY_STRING = "";

CmdAdd::CmdAdd(void){
}

CmdAdd::~CmdAdd(void){
}

//add event with deadline, floating task or timed event
std:: string CmdAdd::executecmdAdd(Storage& _storage){
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
	return EMPTY_STRING;
}

std::string CmdAdd::addEventWithDeadline(Storage& _storage){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	updateStorage(_storage);
	return _feedback;
}

std::string CmdAdd::addEventWithoutDeadline(Storage& _storage){
	_storage.addEvent(_newEvent);
	_feedback = printFeedback(_newEvent);
	updateStorage(_storage);
	return _feedback;
}

//check for clash for timed tasks 
//print a reminder messge if there there is an existing task at that time
//task will still be added if there is a clash
std::string CmdAdd::addTimedEvent(Storage& _storage){
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
	updateStorage(_storage);
	return _feedback;
}

std::string CmdAdd::printFeedback(Event newEvent){
	std::string feedback = QUOTATION_MARKS + newEvent.displayEvent() + ADD_SUCCESSFUL_MESSAGE;
	return feedback;
}

void CmdAdd::updateStorage(Storage& _storage){
	_storage.sortActiveEventlist();
	_storage.synchronizeDrive();
}