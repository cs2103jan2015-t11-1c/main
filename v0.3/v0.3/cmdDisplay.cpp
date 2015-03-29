#include "cmdDisplay.h"
#include <sstream>

cmdDisplay::cmdDisplay(void){
}


cmdDisplay::~cmdDisplay(void){
}

std::string cmdDisplay::executecmdDisplay(){
	switch (_commandWord)
	{
	case DISPLAY:
		return cmdDisplayActive();
	case DISPLAYDONE:
		return cmdDisplayDone();
	case DISPLAYTODAY:
		return cmdDisplayToday();
	default:
		break;
	} 	
	return "";
}
//display active events
std::string cmdDisplay::cmdDisplayActive(){
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
std::string cmdDisplay::cmdDisplayDone(){
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
std::string cmdDisplay::cmdDisplayToday(){
	return "hahaha";
}