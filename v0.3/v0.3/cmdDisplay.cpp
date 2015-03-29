#include "cmdDisplay.h"
#include <sstream>

cmdDisplay::cmdDisplay(void){
}


cmdDisplay::~cmdDisplay(void){
}

std::string cmdDisplay::executecmdDisplay(Storage& _storage){
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
		display << i << "." << (*iter).readEvent() << "\n";
		i++;
	}
	return display.str();
}

//display completed events
std::string cmdDisplay::cmdDisplayDone(Storage& _storage){
	std::ostringstream display;
	Eventlist doneEvents = _storage.displayDoneEvent();
	int i = 1;
	std::list<Event> currentList = doneEvents.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		display << i << "." << (*iter).readEvent() << "\n";
		i++;
	}
	return display.str();
}

//display events today
std::string cmdDisplay::cmdDisplayToday(Storage& _storage){
	return "hahaha";
}