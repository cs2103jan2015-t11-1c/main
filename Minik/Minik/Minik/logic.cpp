#include "logic.h"

logic::logic(){
	storage = new Storage();
}

logic::~logic(){
}

logic::CommandType logic::determineCommandType(string _commandWord) {
	if (_commandWord == "add"){
		return ADD;
	}
	else if (_commandWord == "display") {
		return DISPLAY;
	}
	else if (_commandWord == "delete") {
		return DELETE;
	}
	else if (_commandWord == "edit") {
		return EDIT;
	}
}

void logic::executeCommand(string _commandWord, string _toDoList) {
	
	CommandType commandType = determineCommandType(_commandWord);
	
	switch (commandType)
	{
		case ADD:
			return addEventWithDeadline(_toDoList);
		
		case DISPLAY:
			return;
		
		case DELETE:
			return;
		
		case EDIT:
			return;

		default:
			break;
	}
	
}

Event logic::getEventInformation(string _toDoList){
	string title;
	string date;
	string time;
	string &buffer = _toDoList;
	title = getEventTitle(buffer);
    date = getEventDate(buffer);
	time = getEventTime(buffer);

	Event newEvent = Event(title, date, time);
	return newEvent;
}

string logic::getEventTitle(string &buffer){
	int TIndex;
    string title;

	TIndex = buffer.find_first_of("by, @");
	title = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return title;
}

//assume no spaces within the date input
string logic::getEventDate(string &buffer){
	int TIndex;
	string date;

	TIndex = buffer.find_first_of(" ");
	date = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return date;
}

//assume no spaces within the time input
string logic::getEventTime(string &buffer){
	int TIndex;
	string time;

	TIndex = buffer.find_first_of(" ");
	time = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return time;
}

//Acceptable add commands
//add <title> by/@ <date> <time>
void logic::addEventWithDeadline(string _toDoList){
	Event newEvent = getEventInformation(_toDoList);
	storage->addEvent(newEvent);
	return;
}