#include "cmdSearch.h"
#include <sstream>

const static string MESSAGE_EVENT_NOT_FOUND = "Sorry! No relevant event found."; 

cmdSearch::cmdSearch(void){
}


cmdSearch::~cmdSearch(void){
}

string cmdSearch::executecmdSearch(){
	Eventlist events = _storage.displayEvent();
	list<Event> allEvents = events.returnAllEvent();
	int eventsNumber = events.getTotalNumberOfEvents();
	string keyword = _taskName;
	list<Event>::iterator Tcount;
	string taskName;
	int Tindex;
	Event currentEvent;

	for(Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++){
		currentEvent = *Tcount;
		taskName = currentEvent.getTaskName();
		Tindex = taskName.find(keyword);
		if(Tindex != string::npos){
			_eventFound.addEvent(currentEvent);
		}
	}

	if(_eventFound.getTotalNumberOfEvents() != 0){
		_feedback = printEventFound();
	}else{
		_feedback = MESSAGE_EVENT_NOT_FOUND;
	}

	return _feedback;

}

string cmdSearch::printEventFound(){
	ostringstream feedback;
	list<Event>::iterator Tcount;
	Event currentEvent;
	list<Event> eventFound = _eventFound.returnAllEvent();
	
	for(Tcount = eventFound.begin(); Tcount != eventFound.end(); Tcount++){
		currentEvent = *Tcount;
		feedback << currentEvent.readEvent() << "\n";
	}
	return feedback.str();	
}