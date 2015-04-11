//@author A0115429H
#include "cmdUpdate.h"
#include <assert.h>

static const int INVALID_DATE = 0;
static const int INVALID_MONTH = 13;
static const int INVALID_TIME = 2400;
const static std::string UPDATE_MESSAGE = "\" is updated to ";
const static std::string ERROR = "Error";
const static std::string QUOTATION_MARKS = "\"";
const static std::string UPDATE_RECURRING_NAME = "Recurring Events' titles are changed.\n\n";
const static std::string UPDATE_RECURRING_TIME = "Recurring Events' times are changed.\n\n";

cmdUpdate::cmdUpdate(void){
}

cmdUpdate::~cmdUpdate(void){
}

//update task name, start time, end time or remove start time or end time
std::string cmdUpdate::executecmdUpdate(Storage& _storage){
	int eventNumber;
	eventNumber= _taskNumberList.front();
	Event eventToUpdate; 
	eventToUpdate= _storage.getEvent(eventNumber);
	switch(_commandWord){
	case UPDATENAME:
		return updateName(eventToUpdate, eventNumber, _storage);
	case UPDATESTARTINGTIME:
		return updateStartingTime(eventToUpdate, eventNumber, _storage);
	case UPDATEENDINGTIME:
		return updateEndingTime(eventToUpdate, eventNumber, _storage);
	case CLEARSTART:
		return clearStartingTime(eventToUpdate, eventNumber, _storage);
	case CLEAREND:
		return clearEndingTime(eventToUpdate, eventNumber, _storage);
	case UPDATERECURNAME:
		return updateRecurringName(eventToUpdate, eventNumber, _storage);
	case UPDATERECURSTARTINGTIME:
		return updateRecurringStartTime(eventNumber, _storage);
	case UPDATERECURENDINGTIME:
		return updateRecurringEndTime(eventNumber, _storage);
	default:
		break;
	}
	return ERROR;
}

//update task name
std::string cmdUpdate::updateName(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.displayEvent();
	eventToUpdate.changeTitle(_taskName);
	_storage.updateEvent(eventNumber, eventToUpdate);
	updateStorage(_storage);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback;
}

//update task ending time
std::string cmdUpdate::updateEndingTime(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.displayEvent();
	eventToUpdate.changeEndDay(_endingDate);
	eventToUpdate.changeEndMonth(_endingMonth);
	eventToUpdate.changeEndTime(_endingTime);
	_storage.updateEvent(eventNumber, eventToUpdate);
	updateStorage(_storage);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback; 
}

//update task start time
std::string cmdUpdate::updateStartingTime(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.displayEvent();
	eventToUpdate.changeStartDay(_startingDate);
	eventToUpdate.changeStartMonth(_startingMonth);
	eventToUpdate.changeStartTime(_startingTime);
	_storage.updateEvent(eventNumber, eventToUpdate);
	updateStorage(_storage);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback;
}

//remove task start time
std::string cmdUpdate::clearStartingTime(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.displayEvent();
	int endDay = eventToUpdate.getEndDate();
	int endMonth = eventToUpdate.getEndMonth();
	int endTime = eventToUpdate.getEndTime();
	std::string eventName = eventToUpdate.getTaskName();
	Event newEvent(eventName, endDay, endMonth, endTime);
	_storage.updateEvent(eventNumber, newEvent);	
    updateStorage(_storage);
	_feedback = printFeedback(Tempt, newEvent);
	return _feedback;
}

//remove task ending time
std::string cmdUpdate::clearEndingTime(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.displayEvent();
	eventToUpdate.changeEndDay(INVALID_DATE);
	eventToUpdate.changeEndMonth(INVALID_MONTH);
	eventToUpdate.changeEndTime(INVALID_TIME);
	_storage.updateEvent(eventNumber, eventToUpdate);
	updateStorage(_storage);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback; 
}

std::string cmdUpdate::updateRecurringName(Event eventToUpdate, int eventNumber, Storage& _storage) {
	eventToUpdate.changeTitle(_taskName);
	_storage.updateRecurring(eventNumber, eventToUpdate);
	updateStorage(_storage);
	_feedback = UPDATE_RECURRING_NAME;
	return _feedback;
}

std::string cmdUpdate::updateRecurringStartTime(int eventNumber, Storage& _storage) {
	_storage.updateRecurringStartTime(eventNumber, _startingTime);
	updateStorage(_storage);
	_feedback = UPDATE_RECURRING_TIME;
	return _feedback;
}

std::string cmdUpdate::updateRecurringEndTime(int eventNumber, Storage& _storage) {
	_storage.updateRecurringEndTime(eventNumber, _endingTime);
	updateStorage(_storage);
	_feedback = UPDATE_RECURRING_TIME;
	return _feedback;
}

std::string cmdUpdate::printFeedback(std::string Tempt, Event eventToUpdate){
	std::string feedback = QUOTATION_MARKS + Tempt + UPDATE_MESSAGE + QUOTATION_MARKS + eventToUpdate.displayEvent() +"\" \n\n";
	return feedback;
}

void cmdUpdate::updateStorage(Storage& _storage){
	_storage.sortActiveEventlist();
	_storage.synchronizeDrive();
}