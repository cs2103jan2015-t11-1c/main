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
private:
	string _commandWord;
	string _toDoList;
public:
	//VARIABLES
	Storage* storage;
	enum CommandType {ADD, DELETE, DISPLAY, EDIT};

	//METHODS
	logic();
	logic(string commandWord, string toDoList);
	~logic();
	CommandType determineCommandType();
	Event getEventInformation();
	string getEventTitle(string &buffer);
	string getEventDate(string &buffer);
	string getEventTime(string &buffer);
	bool executeCommand();
	bool addEventWithDeadline();
}
#endif
