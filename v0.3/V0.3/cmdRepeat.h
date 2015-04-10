#pragma once
#include <iostream>
#include <string>
#include "logicbaseclass.h"
#include "findNextDate.h"
#include "cmdRepeatParser.h"

class cmdRepeat :
	public logicBaseClass
{
private:
	findNextDate _findNextDate;
	cmdRepeatParser _parser;
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
	cmdRepeat(void);
	~cmdRepeat(void);
	std::string executecmdRepeat(Storage&);
	void repeatTimedTask(Event, Storage&);
	void repeatDeadlineTask(Event, Storage&);
	bool isWeekday(std::string);
	int determineWeekday(std::string);
	int changeWeekdayToInteger(std::string);
	int getWeekdayToday(int, int);
	repeatType determineRepeatType();
	int determineRepeatTimes(int);
	void determineEventNumber();
	int determineInterval(int, int);
	void getTheStartingDate(int, int, int&, int&);
	int getExceptionTime(std::string);
	int getNumberOfDays(int, int);
	bool isExceptionDay(int, int, int);
	std::string lowercaseCommandWord(std::string);
	void updateStorage();
};