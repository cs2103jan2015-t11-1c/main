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
protected:
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

	void setCommand (string commandWord, string toDoList);
};
#endif
