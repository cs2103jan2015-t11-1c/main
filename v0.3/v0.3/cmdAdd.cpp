#include "cmdAdd.h"


cmdAdd::cmdAdd(void)
{
}


cmdAdd::~cmdAdd(void)
{
}

string cmdAdd::exercutecmdAdd(){
	if(isFloatingTask()){
		cout << "hello" <<endl;
		_feedback = addEventWithoutDeadline();
	}else{
		_feedback = addEventWithDeadline();
	}

	return _feedback;

}
string cmdAdd::addEventWithDeadline(){
	string &buffer = _toDoList;
	Event newEvent = getEventInformation(buffer);
	_storage.addEvent(newEvent);
	_feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n";
	return _feedback;
}
string cmdAdd::addEventWithoutDeadline(){
	Event newEvent(_toDoList, "", "");
	_storage.addEvent(newEvent);
	_feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n";
	return _feedback;
}
string cmdAdd::addTimedEvent(){

}
