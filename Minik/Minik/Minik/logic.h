//logic.h
#ifndef logic_H
#define logic_H

#include "UI.h"
#include "Storage.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class logic{
public:
	//VARIABLES
	Storage* storage;
	enum CommandType {ADD, DELETE, DISPLAY, EDIT};

	//METHODS
	logic();
	~logic();
	CommandType determineCommandType(string _commandWord);
	Event getEventInformation(string _toDoList);
	string getEventTitle(string &buffer);
	string getEventDate(string &buffer);
	string getEventTime(string &buffer);
	void executeCommand(string _commandWord, string _toDoList);
	void addEventWithDeadline(string _toDoList);
}
#endif
