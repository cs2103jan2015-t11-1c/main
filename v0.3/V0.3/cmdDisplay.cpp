#include "cmdDisplay.h"
#include <sstream>
const static std::string EMPTY_ACTIVE_EVENTS = "Currently no active event. \n\n";

cmdDisplay::cmdDisplay(void){
}


cmdDisplay::~cmdDisplay(void){
}

bool cmdDisplay::isEmptyEventsStorage(Storage& _storage){
	bool isEmpty = false;
	Eventlist activeEvents = _storage.displayEvent();
	if(activeEvents.getTotalNumberOfEvents() == 0){
		isEmpty = true;
	}

	return isEmpty;
}
std::string cmdDisplay::executecmdDisplay(Storage& _storage){
	if(isEmptyEventsStorage(_storage)){
		return EMPTY_ACTIVE_EVENTS;
	}

	switch (_commandWord)
	{
	case DISPLAY:
		return cmdDisplayActive(_storage);
	case DISPLAYDONE:
		return cmdDisplayDone(_storage);
	case DISPLAYTODAY:
		return cmdDisplayToday(_storage);
	default:
		break;
	} 	
	return "";
}
//display active events
std::string cmdDisplay::cmdDisplayActive(Storage& _storage){
	std::ostringstream display;
	Eventlist activeEvents = _storage.displayEvent();
	int i = 1;
	std::list<Event> currentList = activeEvents.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		display  << std::setw(3) << i << "." << (*iter).displayEvent() << "\n";
		i++;
	}
	std::cout<<display.str();
	return "\n";
}

//display completed events
std::string cmdDisplay::cmdDisplayDone(Storage& _storage){
	std::ostringstream display;
	Eventlist doneEvents = _storage.displayDoneEvent();
	int i = 1;
	std::list<Event> currentList = doneEvents.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		display << std::setw(3) << i << "."  << (*iter).displayEvent() << "\n";
		i++;
	}
	std::cout<< std::endl;
	return display.str();
}

//display events today
std::string cmdDisplay::cmdDisplayToday(Storage& _storage){
	return "hahaha";
}