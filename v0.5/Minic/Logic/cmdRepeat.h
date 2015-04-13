//@author A0115429H
//This cmdRepeat class will repeat a event (either floating or deadline) daily, weekly, monthly
//every weekday (for example, every monday, every thur) for a number of times.
//It also supports one exception in the repeat
//For example, repeat daily except a weekday; repeat weekly/monthly except for a certain week/month
#pragma once
#include <iostream>
#include <string>
#include "logicbaseclass.h"
#include "Storage\findNextDate.h"
#include "cmdRepeatParser.h"

class CmdRepeat :
	public LogicBaseClass
{
private:
	findNextDate _findNextDate;
	CmdRepeatParser _parser;
	std::string _repeatDetails;
	std::string _repeatCommand;
	enum repeatType{DAILY, WEEKLY, MONTHLY, EVERYWEEKDAY};
	repeatType _type;
	int _repeatTimes;
	int _eventNumber;
	int _interval;
	bool _hasException;
	std::string _exceptionDetails;
	std::list<Event> _events;

public:
	CmdRepeat(void);
	~CmdRepeat(void);
	std::string executecmdRepeat(Storage&);
	void repeatTimedTask(Event, Storage&);
	void repeatDeadlineTask(Event, Storage&);
	void getStartingRepeatDate(int, int, int, int&, int&, int&);
	void getNextDate(int&, int&, int&);
	bool isWeekday(std::string);
	int determineWeekday(std::string);
	int changeWeekdayToInteger(std::string);
	int getWeekdayToday(int, int, int);
	repeatType determineRepeatType();
	bool isDefaultRepeatTimes(int repeatTimes);
	int determineDefaultRepeatTimes(int);
	int determineEventNumber();
	int determineInterval(int, int);
	std::string getTheStartingDate(int, int, int, int&, int&);
	int getExceptionTime(std::string);
	int getNumberOfDays(int, int);
	bool isExceptionDay(int, int, int, int);
	bool isValidDate(int, int, int);
	bool isValidEvent(int, int,int, int, int);
	bool isLeapYear(int);
	std::string lowercaseCommandWord(std::string);
	void updateStorage(Storage& _storage);
};