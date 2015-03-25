//logic.h
#ifndef logic_H
#define logic_H

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
	Storage _storage;
	string _feedback;
public:
	//VARIABLE
	enum CommandType {ADD, DELETE, DISPLAY, UPDATE, EXIT};

	//METHODS
	logic();
	logic(string commandWord, string toDoList);
	~logic();
	CommandType determineCommandType();
	Event getEventInformation();
	string getEventTitle(string &buffer);
	string getEventDate(string &buffer);
	string getEventTime(string &buffer);
	string executeCommand();
	string addEventWithDeadline();
	string cmdDisplay();
	string cmdDelete();
	string cmdUpdate();
	void setCommand (string commandWord, string toDoList);
};
#endif
