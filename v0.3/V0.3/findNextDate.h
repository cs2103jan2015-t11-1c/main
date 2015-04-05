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

public:
	findNextDate(void);
	~findNextDate(void);
	findNextDate(int, int, int);
	int getMonth();
	int getDay();
	int getWeekDay();
	int totalNumberOfDays();
	void calculateTheNextDate();
	void calculateTheWeekDay();

};

