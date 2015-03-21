#include "cmdUpdate.h"


cmdUpdate::cmdUpdate(void)
{
}


cmdUpdate::~cmdUpdate(void)
{
}

string cmdUpdate::exercutecmdUpdate(){
	int eventNumber;
	string &buffer = _toDoList;
	eventNumber = getEventNumber(buffer);
	Event eventToUpdate; 
	eventToUpdate= _storage.getEvent(eventNumber);
    string Tempt = eventToUpdate.readEvent();
	if(isUpdateTitle(buffer)){
		string newTitle;
		newTitle = getNewTitle(buffer);
		eventToUpdate.changeTitle(newTitle);
		_storage.updateEvent(eventNumber, eventToUpdate);
		_feedback = "\"" + Tempt + "\" 's title is updated to " + "\"" + newTitle +"\" \n";
	}else{	
	Event newEvent;
	cout << buffer << endl;
	newEvent= getEventInformation(buffer);
	_storage.updateEvent(eventNumber, newEvent);
	_feedback = "\"" + Tempt + "\" is updated to " + "\"" + newEvent.readEvent() +"\" \n";
	}
	return _feedback;


}

/*
bool logic::isUpdateDeadline(string &buffer){
	string updateType;
	bool isUpdateDeadline = false;

	updateType = getUpdateType(buffer);
	if(updateType == ".end"){
		isUpdateDeadline = true;
	}

	return isUpdateDeadline;
}
*/