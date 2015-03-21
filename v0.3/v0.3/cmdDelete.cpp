#include "cmdDelete.h"
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

cmdDelete::cmdDelete(void)
{
}


cmdDelete::~cmdDelete(void)
{
}

string cmdDelete::exercutecmdDelete(){
	int eventNumber = stoi(_toDoList);
	Eventlist activeEvents = _storage.displayEvent();

	try{
		if(eventNumber>activeEvents.getTotalNumberOfEvents())

	if(eventNumber>activeEvents.getTotalNumberOfEvents()){

		throw EXCEPTION_INVALID_INDEX;
	}
	Event eventToDelete = _storage.getEvent(eventNumber);
	_storage.deleteEvent(eventNumber);
	_feedback = "\"" + eventToDelete.readEvent() + "\" is deleted.\n";
	return _feedback;
	}catch(string EXCEPTION_INVALID_INDEX){
		cout << EXCEPTION_INVALID_INDEX;
		return "\n";
	}

}
