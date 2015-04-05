#pragma once
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
	findNextDate(int, int, int);
	bool isLeapYear();
	int getMonth();
	int getDay();
	int getWeekDay();
	int getYear();
	int totalNumberOfDays();
	void advanceMonthLeapYear();
	void advanceMonth();
	void calculateTheNextDate();
	void calculateTheWeekDay();
	void calculateExtraLongDay();

};

