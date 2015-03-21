#include "cmdDisplay.h"


cmdDisplay::cmdDisplay(void)
{
}


cmdDisplay::~cmdDisplay(void)
{
}

string cmdDisplay::exercutecmdDisplay(){
	Eventlist activeEvents = _storage.displayEvent();
	int i = 1;
	list<Event> currentList = activeEvents.returnAllEvent();
	list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		cout << i << "." << (*iter).readEvent() << endl;
		i++;
	}
	return "";

}
//display completed events
string cmdDisplay::cmdDisplayDone(){
	Eventlist doneEvents = _storage.displayDoneEvent();
	int i = 1;
	list<Event> currentList = doneEvents.returnAllEvent();
	list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		cout << i << "." << (*iter).readEvent() << endl;
		i++;
	}
	return "";

}