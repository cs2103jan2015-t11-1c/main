#include "cmdSearch.h"
#include <sstream>

const static std::string MESSAGE_EVENT_NOT_FOUND = "Sorry! No relevant event found."; 

cmdSearch::cmdSearch(void){
}


cmdSearch::~cmdSearch(void){
}

std::string cmdSearch::executecmdSearch(Storage& _storage){
	Eventlist events = _storage.displayEvent();
	std::list<Event> allEvents = events.returnAllEvent();
	int eventsNumber = events.getTotalNumberOfEvents();
	std::string keyword = _taskName;
	std::list<Event>::iterator Tcount;
	std::string taskName;
	int Tindex;
	Event currentEvent;

	for(Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++){
		currentEvent = *Tcount;
		taskName = currentEvent.getTaskName();
		Tindex = taskName.find(keyword);
		if(Tindex !=std:: string::npos){
			_eventFound.addEvent(currentEvent);
		}
	}

	if(_eventFound.getTotalNumberOfEvents() != 0){
		_feedback = printEventFound();
	}else{
		_feedback = MESSAGE_EVENT_NOT_FOUND;
	}
	/*for(int j=_eventFound.getTotalNumberOfEvents(); j > 0; j--){
		_eventFound.deleteEvent(j);}*/
	_eventFound.clearEventlist();
	return _feedback;

}

std::string cmdSearch::printEventFound(){
	std::ostringstream feedback;
	std::list<Event>::iterator Tcount;
	Event currentEvent;
	std::list<Event> eventFound = _eventFound.returnAllEvent();
	
	for(Tcount = eventFound.begin(); Tcount != eventFound.end(); Tcount++){
		currentEvent = *Tcount;
		feedback << currentEvent.displayEvent() << "\n";
	}

	std::cout<<feedback.str();	
	return "\n";
}