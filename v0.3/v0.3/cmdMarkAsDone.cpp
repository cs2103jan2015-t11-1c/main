#include "cmdMarkAsDone.h"
#include <sstream>
const static std::string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";
const static int ONE_EVENT = 1;
const static std::string MESSAGE_MarkDone_ONE_EVENT = "The following event is marked as done: \n";
const static std::string MESSAGE_MarkDone_MUTIPLE_EVENTS = "The following events are marked as done: \n";

cmdMarkAsDone::cmdMarkAsDone(void)
{
}


cmdMarkAsDone::~cmdMarkAsDone(void)
{
}

std::string cmdMarkAsDone::executeMarkAsDone(Storage& _storage){
	int eventNumber = _taskNumberList.size();
	Eventlist activeEvents = _storage.displayEvent();

	try{
		if(eventNumber>activeEvents.getTotalNumberOfEvents()){
			throw EXCEPTION_INVALID_INDEX;
	}
	_feedback = printFeedback(_taskNumberList, _storage);
	_storage.markEventAsDone(_taskNumberList);
	_storage.synchronizeDrive();
	return _feedback;
	}catch(std::string EXCEPTION_INVALID_INDEX){
		std::cout << EXCEPTION_INVALID_INDEX;
		return "\n";
	}
}
	
std::string cmdMarkAsDone::printFeedback(std::list<int> taskNumberList, Storage& _storage){
	std::ostringstream feedback;
	Event eventMarkedDone;
	if(taskNumberList.size() == ONE_EVENT){
		eventMarkedDone = _storage.getEvent(taskNumberList.front());
		feedback << MESSAGE_MarkDone_ONE_EVENT << eventMarkedDone.readEvent() << "\n";
	}else{
		feedback << MESSAGE_MarkDone_MUTIPLE_EVENTS;
		while(!taskNumberList.empty()){
			eventMarkedDone = _storage.getEvent(taskNumberList.back());
			feedback << eventMarkedDone.readEvent() << "\n";
			taskNumberList.pop_back();
		}
	}
	std::cout<< feedback.str();
	return "\n";
}
