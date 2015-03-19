#include "logic.h"
#include <assert.h>
#include <iostream>
const static string EXIT_MESSAGE = "Thank you for using Minik:)";
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.\n";

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
			return addEventWithDeadline();
		
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

Event logic::getEventInformation(){
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

//Acceptable add commands
//add <title> by/@ <date> <time>
string logic::addEventWithDeadline(){
	Event newEvent = getEventInformation();
	_storage.addEvent(newEvent);
	_feedback = "\"" + newEvent.readEvent() + "\" is added successfully.\n";
	return _feedback;
}

string logic::cmdDelete(){
	cmdDisplay();
	int taskNumber;;
	Eventlist activeEvents = _storage.displayEvent();
	cin>>taskNumber;
	string waste;
	getline(cin, waste);
	try{
		if(taskNumber>activeEvents.getTotalNumberOfEvents())
		throw EXCEPTION_INVALID_INDEX;
	Event eventToDelete = _storage.getEvent(taskNumber);
	_storage.deleteEvent(taskNumber);
	_feedback = "\"" + eventToDelete.readEvent() + "\" is deleted.\n";
	return _feedback;
	}catch(string EXCEPTION_INVALID_INDEX){
		cout << EXCEPTION_INVALID_INDEX;
	}
	}



//mark a task as done
string logic::cmdMarkAsDone(){
	cmdDisplay();
	int taskNumber;
	Eventlist activeEvents = _storage.displayEvent();
	cin>>taskNumber;
	string buffer;
	getline(cin, buffer);
	Event eventDone = _storage.getEvent(taskNumber);
	_storage.markEventAsDone(taskNumber);
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
	cmdDisplay();
	int taskNumber;
	cin >> taskNumber;
	Eventlist activeEvents;
    string updateDetails;
	getline(cin, updateDetails);
	getline(cin, updateDetails);
	_toDoList = updateDetails;
	Event eventToUpdate = _storage.getEvent(taskNumber);
	Event newEvent = getEventInformation();
	_storage.updateEvent(taskNumber, newEvent);
	_feedback = "\"" + eventToUpdate.readEvent() + "\" is updated to " + "\"" + newEvent.readEvent() +"\" \n";
	return _feedback;

}
