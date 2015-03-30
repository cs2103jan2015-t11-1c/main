#include "cmdMarkAsDone.h"
#include <sstream>
const static std::string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";
const static int ONE_EVENT = 1;
const static std::string MESSAGE_DELETE_ONE_EVENT = "The following event is marked as done: \n";
const static std::string MESSAGE_DELETE_MUTIPLE_EVENTS = "The following events are marked as done: \n";

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
	_storage.markEventAsDone(_taskNumberList);
	_storage.synchronizeDrive();
	_feedback = printFeedback(_taskNumberList, _storage);
	return _feedback;

	}catch(std::string EXCEPTION_INVALID_INDEX){
		std::cout << EXCEPTION_INVALID_INDEX;
		return "\n";
	}
}

	

std::string cmdMarkAsDone::printFeedback(std::list<int> taskNumberList, Storage& _storage){
	std::ostringstream feedback;
	Event eventDeleted;
	if(taskNumberList.size() == ONE_EVENT){
		eventDeleted = _storage.getEvent(taskNumberList.front());
		feedback << MESSAGE_DELETE_ONE_EVENT << eventDeleted.readEvent() << "\n\n";
	}else{
		feedback << MESSAGE_DELETE_MUTIPLE_EVENTS;
		while(!taskNumberList.empty()){
			eventDeleted = _storage.getEvent(taskNumberList.back());
			feedback << eventDeleted.readEvent() << "\n";
			taskNumberList.pop_back();
		}
		std::cout<< std::endl;
	}
	return feedback.str();
}