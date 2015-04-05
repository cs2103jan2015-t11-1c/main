#include "cmdSearch.h"
#include <sstream>

const static std::string MESSAGE_EVENT_NOT_FOUND = "Sorry! No relevant event found.\n\n"; 

cmdSearch::cmdSearch(void){
}


cmdSearch::~cmdSearch(void){
}

//search for key words from task list
std::string cmdSearch::executecmdSearch(Storage& _storage){
	Eventlist events = _storage.displayEvent();
	std::list<Event> allEvents = events.returnAllEvent();
	int eventsNumber = events.getTotalNumberOfEvents();

	searchForEvent(allEvents, eventsNumber);

	if (_eventFound.getTotalNumberOfEvents() != 0) {
		_feedback = printEventFound();
	}else{
		_feedback = MESSAGE_EVENT_NOT_FOUND;
	}

	_eventFound.clearEventlist();
	_eventNumbers.clear();

	return _feedback;

}

//this function converts upper case letter to lower case
std::string cmdSearch::lowercaseCommandWord(std::string commandWord){
	int n = commandWord.size();
	for( int i = 0; i < n; i++){
		if(commandWord[i] <='Z' && commandWord[i] >= 'A'){
			commandWord[i] = commandWord[i] - ('Z'-'z');
		}
	}

  return commandWord;
}

void cmdSearch::searchForEvent(std::list<Event> allEvents, int){
	std::string keyword = _taskName;
	std::string taskName = lowercaseCommandWord(keyword);
	std::list<Event>::iterator Tcount;
	std::string eventName;
	int Tindex;
	int eventNumber = 0;
	Event currentEvent;

	for(Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++){
		eventNumber++;
		currentEvent = *Tcount;
		eventName = currentEvent.getTaskName();
		std::string newEventName = lowercaseCommandWord(eventName);
		Tindex = newEventName.find(taskName);
		if(Tindex !=std:: string::npos){
			_eventNumbers.push_back(eventNumber);
			_eventFound.addEvent(currentEvent);
		}
	}
}

std::string cmdSearch::printEventFound(){
	std::ostringstream feedback;
	std::list<Event>::iterator Titer;
	Event currentEvent;
	int eventNumber;
	int Tcount = 0;
	std::list<Event> eventFound = _eventFound.returnAllEvent();
	
	for(Titer = eventFound.begin(); Titer != eventFound.end(); Titer++){
		currentEvent = *Titer;
		eventNumber = _eventNumbers[Tcount];
		feedback << eventNumber << "." << currentEvent.displayEvent() << "\n\n";
		Tcount ++;
	}

	return feedback.str();
}