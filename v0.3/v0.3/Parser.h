#pragma once

#include <iostream>
#include "logic.h"
#include "Parser.h"
#include <string>
#include <list>
#include <string>
using namespace std;
enum MonthType {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,MONTHNOTASSIGNED};

class Parser
{

private:
	string _taskName;
	string _startingTime;
	string _endingTime;
	int _startingDate;
	int _endingDate;
	MonthType _startingMonth;
	MonthType _endingMonth;
	list<int> _taskNumberList;
	logic _logic;
public:
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATEENDINGTIME, UPDATESTARTINGTIME, DELETE, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, SEARCH, UNDO, CLEAR, HELP};
	Parser(void);
	~Parser(void);
	int convertMonthTypeToInteger(MonthType);
    string callToLogic(CommandType );
    string addEvent(string );
    string addTimedEvent(string );
	string addEventWithDeadline(string );
	string addFloatingEvent(string );
	MonthType determineMonthType(string );
	bool isTaskWithDeadline(string );
	bool isTimedTask(string );
	string getEventTitle(string &);
	void getEventDate(string &, int &, MonthType &);
	string getEventTime(string &);
	string updateEvent(string );
	int getUpdateEventNumber(string &);
	string searchEvent(string );
	string unDo();
	string displayEvent(string );
	string clearEvent();
	string markAsDone(string );
	string deleteEvent(string );
	void getNumberList(string );
};
