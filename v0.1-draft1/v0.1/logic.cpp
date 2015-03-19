#include "logic.h"
#include <assert.h>
#include <iostream>
const static string EXIT_MESSAGE = "Thank you for using Minik:)";
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

logic::logic(){
	_storage = Storage();
}

logic::logic(string commandWord, string toDoList){
	//_storage = Storage();
	_commandWord = commandWord;
	_toDoList = toDoList;
}

logic::~logic(){
}

void logic:: setCommand (string commandWord, string toDoList){
	_commandWord = commandWord;
	_toDoList = toDoList;
}
logic::CommandType logic::determineCommandType() {
	if (_commandWord == "add"){
		return ADD;
	}
	else if (_commandWord == "display") {
		return DISPLAY;
	}
	else if (_commandWord == "displayDone"){
		return DISPLAY_DONE;
	}
	else if (_commandWord == "delete") {
		return DELETE;
	}
	else if (_commandWord == "update") {
		return UPDATE;
	}
	else if (_commandWord == "done" || _commandWord == "complete"){
		return DONE;
	}
	else if (_commandWord == "exit") {
		return EXIT;
	}
}
string logic::executeCommand() {
	
	CommandType commandType = determineCommandType();
	switch (commandType)
	{
		case ADD:
			return cmdAdd();
		
		case DISPLAY:
			return cmdDisplay();
		
		case DELETE:
			return cmdDelete();
		
		case UPDATE:
			return cmdUpdate();

		case DISPLAY_DONE:
			return cmdDisplayDone();

		case DONE:
			return cmdMarkAsDone();

		case EXIT:
			exit(0);
			//return EXIT_MESSAGE;
		
		default:
			break;
	}
	
}

Event logic::getEventInformation(string &buffer){
	string title;
	string date;
	string time;
	title = getEventTitle(buffer);
    date = getEventDate(buffer);
	time = getEventTime(buffer);

	Event newEvent = Event(title, date, time);
	return newEvent;
}

string logic::getEventTitle(string &buffer){
	int TIndex;
    string title;

	TIndex = buffer.find("by");
	title = buffer.substr(0, TIndex-1);
	buffer = buffer.substr(TIndex+3);

	return title;
}

//assume one space within the date input
string logic::getEventDate(string &buffer){
	int TIndex;
	string date;
	string day;
	string month;

	TIndex = buffer.find_first_of(" ");
	day = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	TIndex = buffer.find_first_of(" ");
	month = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	date = day + " " + month;
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

int logic::getEventNumber(string &buffer){
	int eventNumber;
	int TIndex;
	string TString;

	TIndex = _toDoList.find_first_of(" ");
	TString = _toDoList.substr(0, TIndex);
	eventNumber = stoi(TString);
	buffer = buffer.substr(TIndex+1);

	return eventNumber;
}

string logic::getUpdateType(string &buffer){
	int TIndex;
	string updateType;

	TIndex = buffer.find_first_of(" ");
	updateType = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return updateType;
}

bool logic::isUpdateTitle(string &buffer){
	string updateType;
	bool isUpdateTitle = false;

	updateType = getUpdateType(buffer);
	if(updateType == ".name"){
		isUpdateTitle = true;
	}

	return isUpdateTitle;
}

string logic::getNewTitle(string &buffer){
	string newTitle;
	newTitle = buffer;
	
	return newTitle;
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

//Acceptable add commands
//add <title> by/@ <date> <time>
string logic::addEventWithDeadline(){
	string &buffer = _toDoList;
	Event newEvent = getEventInformation(buffer);
	_storage.addEvent(newEvent);
	_feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n";
	return _feedback;
}

bool logic::isFloatingTask(){
	bool isFloatingTask = false;
	int TIndex;
	
	TIndex = _toDoList.find("by");
	if(TIndex == string::npos){
		isFloatingTask = true;
	}

	return isFloatingTask;
}

string logic::addEventWithoutDeadline(){
	Event newEvent(_toDoList, "", "");
	_storage.addEvent(newEvent);
	_feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n";
	return _feedback;
}

string logic::cmdAdd(){
	if(isFloatingTask()){
		cout << "hello" <<endl;
		_feedback = addEventWithoutDeadline();
	}else{
		_feedback = addEventWithDeadline();
	}

	return _feedback;
}


string logic::cmdDelete(){
	int eventNumber = stoi(_toDoList);
	Eventlist activeEvents = _storage.displayEvent();

	try{
	if(eventNumber>activeEvents.getTotalNumberOfEvents()){
		throw EXCEPTION_INVALID_INDEX;
	}
	Event eventToDelete = _storage.getEvent(eventNumber);
	_storage.deleteEvent(eventNumber);
	_feedback = "\"" + eventToDelete.readEvent() + "\" is deleted.\n";
	return _feedback;
	}catch(string EXCEPTION_INVALID_INDEX){
		cout << EXCEPTION_INVALID_INDEX;
		return "\n";
	}
}
//mark a task as done
string logic::cmdMarkAsDone(){
	Eventlist activeEvents = _storage.displayEvent();
	int number = stoi(_toDoList);
	Event eventDone = _storage.getEvent(number);
	_storage.markEventAsDone(number);
	_feedback = "\"" + eventDone.readEvent() + "\" is marked as done.\n";
	return _feedback;
	}
		
string logic::cmdDisplay(){
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
string logic::cmdDisplayDone(){
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

string logic::cmdUpdate(){
	int eventNumber;
	string &buffer = _toDoList;
	eventNumber = getEventNumber(buffer);
	Event eventToUpdate; 
	eventToUpdate= _storage.getEvent(eventNumber);
    string Tempt = eventToUpdate.readEvent();
	cout << buffer <<endl;
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
