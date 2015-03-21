#include "Parser.h"


Parser::Parser(void)
{
}


Parser::~Parser(void)
{
}

Parser::CommandType Parser::determineCommandType() {
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
string Parser::executeCommand() {
	
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

Event Parser::getEventInformation(string &buffer){
	string title;
	string date;
	string time;
	title = getEventTitle(buffer);
    date = getEventDate(buffer);
	time = getEventTime(buffer);

	Event newEvent = Event(title, date, time);
	return newEvent;
}

string Parser::getEventTitle(string &buffer){
	int TIndex;
    string title;

	TIndex = buffer.find("by");
	title = buffer.substr(0, TIndex-1);
	buffer = buffer.substr(TIndex+3);

	return title;
}

//assume one space within the date input
string Parser::getEventDate(string &buffer){
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
string Parser::getEventTime(string &buffer){
	int TIndex;
	string time;

	TIndex = buffer.find_first_of(" ");
	time = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return time;
}

int Parser::getEventNumber(string &buffer){
	int eventNumber;
	int TIndex;
	string TString;

	TIndex = _toDoList.find_first_of(" ");
	TString = _toDoList.substr(0, TIndex);
	eventNumber = stoi(TString);
	buffer = buffer.substr(TIndex+1);

	return eventNumber;
}

string Parser::getUpdateType(string &buffer){
	int TIndex;
	string updateType;

	TIndex = buffer.find_first_of(" ");
	updateType = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return updateType;
}

bool Parser::isUpdateTitle(string &buffer){
	string updateType;
	bool isUpdateTitle = false;

	updateType = getUpdateType(buffer);
	if(updateType == ".name"){
		isUpdateTitle = true;
	}

	return isUpdateTitle;
}

string Parser::getNewTitle(string &buffer){
	string newTitle;
	newTitle = buffer;
	
	return newTitle;
}


bool Parser::isFloatingTask(){
	bool isFloatingTask = false;
	int TIndex;
	
	TIndex = _toDoList.find("by");
	if(TIndex == string::npos){
		isFloatingTask = true;
	}

	return isFloatingTask;
}
