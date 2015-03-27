#include "cmdDelete.h"
#include <sstream>
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";
const static int ONE_EVENT = 1;
const static string MESSAGE_DELETE_ONE_EVENT = "The following event is deleted: \n";
const static string MESSAGE_DELETE_MUTIPLE_EVENTS = "The following events are deleted: \n";

cmdDelete::cmdDelete(void){
}


cmdDelete::~cmdDelete(void){
}

string cmdDelete::executecmdDelete(){
	int eventNumber = _taskNumberList.size();
	Eventlist activeEvents = _storage.displayEvent();

	try{
		if(eventNumber>activeEvents.getTotalNumberOfEvents()){
			throw EXCEPTION_INVALID_INDEX;
	}
	_feedback = printFeedback(_taskNumberList);
	_storage.deleteEvent(_taskNumberList);
	return _feedback;

	}catch(string EXCEPTION_INVALID_INDEX){
		cout << EXCEPTION_INVALID_INDEX;
		return "\n";
	}

}

string cmdDelete::printFeedback(list<int> taskNumberList){
	ostringstream feedback;
	Event eventDeleted;
	if(taskNumberList.size() == ONE_EVENT){
		eventDeleted = _storage.getEvent(taskNumberList.front());
		feedback << MESSAGE_DELETE_ONE_EVENT << eventDeleted.readEvent() << "\n";
	}else{
		feedback << MESSAGE_DELETE_MUTIPLE_EVENTS;
		while(!taskNumberList.empty()){
			eventDeleted = _storage.getEvent(taskNumberList.back());
			feedback << eventDeleted.readEvent() << "\n";
			taskNumberList.pop_back();
		}
	}
	return feedback.str();
}
