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
	Parser(void);
	~Parser(void);
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATEENDINGTIME, UPDATESTARTINGTIME, DELETE, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, SEARCH, UNDO, CLEAR, CLEAREND, CLEARSTART, CHANGEDIRECTORY, HELP, EXIT, REPEAT, REPEATDONE};
	logic::CommandType changeToLogicCommandType(CommandType );
	MonthType determineMonthType(std::string );
	
    std::string finalVerificationAndCallToLogic(CommandType);
    std::string addEvent(std::string );
    std::string addTimedEvent(std::string );
	std::string addEventWithDeadline(std::string );
	std::string addFloatingEvent(std::string );
	std::string getEventTitle(std::string &);
	std::string getEventTime(std::string &);
	std::string updateEvent(std::string );
	std::string searchEvent(std::string );
	std::string unDo();
	std::string displayEvent(std::string );
	std::string clearEvent();
	std::string markAsDone(std::string );
	std::string deleteEvent(std::string );
	std::string changeDirectory(std::string );
	std::string repeat(std::string, std::string);
	std::string help();
	bool getNumberList(std::string );
	void resetAttributesValue();
	bool isAbleToGetEventDateAndMonth(std::string &, int &, MonthType &);
    bool isTaskWithDeadline(std::string );
	bool isTimedTask(std::string );
	bool isMonthValid(std::string);
	bool isDateValid(std::string );
	bool isStringAnInteger(std::string );
	bool isEmpty(std::string);

	bool isValidIndex(int );
	int convertMonthTypeToInteger(MonthType);
	int firstIndexThatIsNotASpace(std::string );
	int firstIndextThatIsASpace(std::string );
	int changeFromStringToInteger(std::string str);
	int getUpdateEventNumber(std::string &);

};
