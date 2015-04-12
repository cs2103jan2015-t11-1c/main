//@author A0114301E
#include "cmdDelete.h"
#include "storage.h";

#include <sstream>
const static std::string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";
const static std::string MESSAGE_DELETE_ONE_EVENT = "The following event is deleted: \n";
const static std::string MESSAGE_DELETE_MUTIPLE_EVENTS = "The following events are deleted: \n";
const static int ONE_EVENT = 1;
const static std::string NEW_LINE = "\n";
const static std::string LOG_DELETE = "executed delete";
const static std::string RECURRING_EVENTS_DELETED = "Recurring events are deleted. \n\n";
const static std::string INFO = "Info";

CmdDelete::CmdDelete(void){
}

CmdDelete::~CmdDelete(void){
}

//delete one task or multiple tasks
std::string CmdDelete::executecmdDelete(Storage& _storage) {
	if (_commandWord == DELETERECUR) {
		return deleteRecurringEvents(_taskNumberList, _storage);
	}

	int eventNumber = _taskNumberList.size();
	Eventlist activeEvents = _storage.displayEvent();
	try {
		if (eventNumber>activeEvents.getTotalNumberOfEvents()) {
			throw EXCEPTION_INVALID_INDEX;
	}
	_feedback = printFeedback(_taskNumberList, _storage);
	_storage.deleteEvent(_taskNumberList);
	_storage.synchronizeDrive();
	Storage storage;
	storage.writeToLogfile(INFO, LOG_DELETE);
	return _feedback;

	} catch(std::string EXCEPTION_INVALID_INDEX){
		std::cout << EXCEPTION_INVALID_INDEX;
		return NEW_LINE;
	}
}
//@author A0115429H
//This method return the feedback for either deleting one event or multiple events
std::string CmdDelete::printFeedback(std::list<int> taskNumberList, Storage& _storage) {
	std::ostringstream feedback;
	int eventNumber;
	Event eventDeleted;
	if (taskNumberList.size() == ONE_EVENT) {
		feedback << MESSAGE_DELETE_ONE_EVENT;
		eventNumber = taskNumberList.back();
		eventDeleted = _storage.getEvent(eventNumber);
		feedback << eventDeleted.displayEvent() << NEW_LINE;
	} else {
		feedback << MESSAGE_DELETE_MUTIPLE_EVENTS;
		while (!taskNumberList.empty()) {
			eventNumber = taskNumberList.back();
			eventDeleted = _storage.getEvent(eventNumber);
			feedback << eventDeleted.displayEvent() << NEW_LINE;
			taskNumberList.pop_back();
		} 
	}
	feedback << NEW_LINE;
	return feedback.str();
}

std::string CmdDelete::deleteRecurringEvents(std::list<int> taskNumberList, Storage& _storage) {
	int recurringEventNumber = taskNumberList.back();
	_storage.deleteRecurring(recurringEventNumber);
	_storage.synchronizeDrive();
	return RECURRING_EVENTS_DELETED;
}