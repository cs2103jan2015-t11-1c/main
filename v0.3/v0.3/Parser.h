#pragma once

#include <iostream>
#include "logic.h"
#include "Parser.h"
#include <string>
#include <list>
#include <string>
using namespace std;

class Parser
{

private:
	string _taskName;
	string _startingTime;
	string _endingTime;
	string _startingDate;
	string _endingDate;
	list<int> _taskNumberList;
	logic _logic;

public:
	Parser(void);
	~Parser(void);
    string callToLogic(string command);
    string addEvent(string toDoList);
    string addTimedEvent(string toDoList);
	string addEventWithDeadline(string toDoList);
	string addFloatingEvent(string toDoList);
	bool isTaskWithDeadline(string toDoList);
	bool isTimedTask(string toDoList);
	string getEventTitle(string &buffer);
	string getEventDate(string &buffer);
	string getEventTime(string &buffer);
	string updateEvent(string toDoList);
	int getUpdateEventNumber(string &buffer);
	string searchEvent(string part);
	string unDo();
	string displayEvent(string command);
	string clearEvent();
	string markAsDone(string numberList);
	string deleteEvent(string numberList);
	void getNumberList(string numberList);
};
