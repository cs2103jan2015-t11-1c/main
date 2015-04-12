//@author A0114301E
#include "cmdMarkAsDone.h"
#include "storage.h"
#include <sstream>
const static std::string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";
const static int ONE_EVENT = 1;
const static std::string MESSAGE_MarkDone_ONE_EVENT = "The following event is marked as done: \n";
const static std::string MESSAGE_MarkDone_MUTIPLE_EVENTS = "The following events are marked as done: \n";
const static std::string NEW_Line = "\n";
const static std::string LOG_MARKASDONE = "executed mark as done";
const static std::string LOG_PRINT_FEEDBACK = "executed print feedback";
const static std::string INFO = "Info";

CmdMarkAsDone::CmdMarkAsDone(void) {
}


CmdMarkAsDone::~CmdMarkAsDone(void) {
}

//mark one event or multiple tasks as done
std::string CmdMarkAsDone::executeMarkAsDone(Storage& _storage) {
	int eventNumber = _taskNumberList.size();
	Eventlist activeEvents = _storage.displayEvent();

	try {
		if (eventNumber>activeEvents.getTotalNumberOfEvents()) {
			throw EXCEPTION_INVALID_INDEX;
	}
	_feedback = printFeedback(_taskNumberList, _storage);
	_storage.markEventAsDone(_taskNumberList);
	_storage.synchronizeDrive();
	Storage storage;
	storage.writeToLogfile(INFO,LOG_MARKASDONE);
	return _feedback;
	} catch(std::string EXCEPTION_INVALID_INDEX){
		std::cout << EXCEPTION_INVALID_INDEX;
		return NEW_Line;
	}
}
	
std::string CmdMarkAsDone::printFeedback(std::list<int> taskNumberList, Storage& _storage) {
	std::ostringstream feedback;
	Event eventMarkedDone;
	if (taskNumberList.size() == ONE_EVENT) {
		eventMarkedDone = _storage.getEvent(taskNumberList.front());
		feedback << MESSAGE_MarkDone_ONE_EVENT << eventMarkedDone.displayEvent() << NEW_Line;
	} else {
		feedback << MESSAGE_MarkDone_MUTIPLE_EVENTS;
		while (!taskNumberList.empty()) {
			eventMarkedDone = _storage.getEvent(taskNumberList.back());
			feedback << eventMarkedDone.displayEvent() << NEW_Line;
			taskNumberList.pop_back();
		}
	}
	std::cout << feedback.str();
	Storage storage;
	storage.writeToLogfile(INFO,(LOG_PRINT_FEEDBACK));
	return NEW_Line;
}
