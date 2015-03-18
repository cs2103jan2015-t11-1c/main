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
	enum CommandType {ADD, DELETE, DISPLAY, DISPLAY_DONE, UPDATE, DONE, COMPLETED, EXIT};

	//METHODS
	logic();
	logic(string commandWord, string toDoList);
	~logic();
	CommandType determineCommandType();
	Event getEventInformation(string &buffer);
	bool isFloatingTask();
	string getEventTitle(string &buffer);
	string getEventDate(string &buffer);
	string getEventTime(string &buffer);
	string getUpdateType(string &buffer);
	int getEventNumber(string &buffer);
	bool isUpdateTitle(string &buffer);
	string getNewTitle(string &buffer);
	bool isUpdateDeadline(string &buffer);
	string executeCommand();
	string addEventWithDeadline();
	string addEventWithoutDeadline();
	string cmdAdd();
	string cmdDisplay();
	string cmdDisplayDone();
	string cmdDelete();
	string cmdUpdate();
	string cmdMarkAsDone();
	void setCommand (string commandWord, string toDoList);
};
#endif
