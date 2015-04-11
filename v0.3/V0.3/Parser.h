//@author A0115253R
#pragma once

#include <iostream>
#include "logic.h"
#include "VerificationDateTimeMonth.h"
#include <string>
#include <list>
#include <string>

enum MonthType {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER,MONTHNOTASSIGNED};

class Parser {

private:
	std::string _taskName;
	std::string _startingTime;
	std::string _endingTime;
	int _startingDate;
	int _endingDate;
	MonthType _startingMonth;
	MonthType _endingMonth;
	std::list<int> _taskNumberList;
	logic _logic;
	logicBaseClass _logicBaseClass;
	VerificationDateTimeMonth _verificationDateTimeMonth;

public:
	Parser(void);
	~Parser(void);
	enum CommandType {ADDTIMEDEVENT, ADDEVENTWITHDEADLINE,ADDFLOATINGEVENT, UPDATENAME, UPDATERECURNAME, UPDATEENDINGTIME, UPDATERECURENDINGTIME, UPDATESTARTINGTIME, UPDATERECURSTARTINGTIME, DELETE, DELETERECUR, DISPLAY, MARKASDONE, DISPLAYDONE, DISPLAYTODAY, DISPLAYTOMORROW, DISPLAYALL, SEARCH, UNDO, CLEAR, CLEAREND, CLEARRECUREND, CLEARSTART, CLEARRECURSTART, CHANGEDIRECTORY, HELP, EXIT, REPEAT, REPEATDONE};
    std::string VerifyAllAttributesAndCallLogic(CommandType);
    std::string addEvent(std::string );
    std::string addTimedEvent(std::string );
	std::string addEventWithDeadline(std::string );
	std::string addFloatingEvent(std::string );
	std::string getTaskName(std::string &);
	std::string getEventTime(std::string &);
	std::string updateEvent(std::string, std::string );
	std::string searchEvent(std::string );
	std::string unDo();
	std::string displayEvent(std::string );
	std::string clearEvent();
	std::string markAsDone(std::string );
	std::string deleteEvent(std::string, std::string);
	std::string changeDirectory(std::string );
	std::string repeat(std::string, std::string);
	std::string help();
	std::string updateName(std::string );
	std::string updateClear(std::string , std::string );
	std::string updateEndingTime(std::string , std::string );
	std::string updateStartingTime(std::string, std::string );
	bool isAbleToGetEventDateAndMonth(std::string &, int &, MonthType &);
    bool isTaskWithDeadline(std::string );
	bool isTimedTask(std::string );
	bool isStringAnInteger(std::string );
	bool isEmpty(std::string);
	bool isValidIndex(int );
	bool isAbleToGetNumberList(std::string );
	int convertMonthTypeToInteger(MonthType);
	int getIndexOfFirstNonWhiteSpace(std::string );
	int getIndexOfFirstWhiteSpace(std::string );
	int convertStringToInteger(std::string str);
	int getUpdatetaskNumber(std::string &);
	logic::CommandType changeToLogicCommandType(CommandType );
	MonthType determineMonthType(std::string );
	void resetAttributesValue();
	void replaceStringWithItsSubstring(std::string &, int );
	void  assignDateTimeMonthAttributes(std::string startOrEnd, std::string &, int , MonthType );
	void setAttributes(std::string ,std::string ,std::string ,int ,int ,MonthType ,MonthType ,std::list<int> );
};
