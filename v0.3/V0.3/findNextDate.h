#pragma once

#include <stdio.h>
#include <iostream>

class findNextDate
{
private:
	int _month;
	int _day;
	int _weekDay;
	int _currentMonth;
	int _currentDay;
	int _advanceNumberOfDays;
	int _firstDayOfYear2015;
	int _year;

public:
	findNextDate(void);
	~findNextDate(void);
	bool isLeapYear(int);
	int getMonth();
	int getDay();
	int getWeekDay();
	int getYear();
	int totalNumberOfDays();
	void calculate(int, int, int);
	void advanceMonthLeapYear();
	void advanceMonth();
	void calculateTheNextDate();
	void calculateTheWeekDay();
	void calculateExtraLongDay();
	void changeDefaultYear(int);
	int calculateDayInMonthForLeapYear();
	int calculateDayInMonth();
	int calculateDayInYear();

};

