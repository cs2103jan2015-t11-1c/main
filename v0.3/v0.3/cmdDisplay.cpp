#include "cmdDisplay.h"
#include <sstream>

cmdDisplay::cmdDisplay(void){
}


cmdDisplay::~cmdDisplay(void){
}

string cmdDisplay::executecmdDisplay(){
	switch (_commandWord)
	{
	case DISPLAY:
		_feedback = cmdDisplayActive();
	case DISPLAYDONE:
		_feedback = cmdDisplayDone();
	case DISPLAYTODAY:
		_feedback = cmdDisplayToday();
	default:
		break;
	} 	
}
//display active events
string cmdDisplay::cmdDisplayActive(){
	ostringstream display;
	Eventlist activeEvents = _storage.displayEvent();
	int i = 1;
	list<Event> currentList = activeEvents.returnAllEvent();
	list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		display << i << "." << (*iter).readEvent() << "\n";
		i++;
	}
	return display.str();
}

//display completed events
string cmdDisplay::cmdDisplayDone(){
	ostringstream display;
	Eventlist doneEvents = _storage.displayDoneEvent();
	int i = 1;
	list<Event> currentList = doneEvents.returnAllEvent();
	list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		display << i << "." << (*iter).readEvent() << "\n";
		i++;
	}
	return display.str();
}

//display events today
string cmdDisplay::cmdDisplayToday(){
}