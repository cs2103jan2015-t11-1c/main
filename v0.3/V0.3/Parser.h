#pragma once

#include <iostream>
#include "logic.h"
#include "VerificationDateTimeMonth.h"
#include <string>
#include <list>
#include <string>

using namespace std;
enum MonthType {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,MONTHNOTASSIGNED};
const static string INVALID_TIMED_DATE_MONTH_MESSAGE =" Please check your user input time, date and month.\n\n";
const static string INVALID_INPUT = "Invalid user input.\n\n";


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
	logicBaseClass _logicBaseClass;
	VerificationDateTimeMonth _verificationDateTimeMonth;

public:
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATEENDINGTIME, UPDATESTARTINGTIME, DELETE, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, SEARCH, UNDO, CLEAR, HELP, EXIT};
	Parser(void);
	~Parser(void);
	logic::CommandType changeToLogicCommandType(CommandType command);
	void resetAttributesValue();
	int convertMonthTypeToInteger(MonthType);
    string callToLogic(CommandType);
    string addEvent(string );
    string addTimedEvent(string );
	string addEventWithDeadline(string );
	string addFloatingEvent(string );
	MonthType determineMonthType(string );
	bool isTaskWithDeadline(string );
	bool isTimedTask(string );
	string getEventTitle(string &);
	bool isAbleToGetEventDate(string &, int &, MonthType &);
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
	bool isTimeAnInteger(string );

};
