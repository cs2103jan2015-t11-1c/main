//The information of a particular event is all stored in this class.

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>


class Event
{
private:
	std::string _title;
	int _endDay;
	int _endMonth;
	int _endTime;
	int _startDay;
	int _startMonth;
	int _startTime;
	bool _durationEvent;

public:
	int _dueRanking;
	Event(void);
	Event(std::string, int, int, int);
	~Event(void);
	void changeTitle(std:: string);
	void changeStartDay (int);
	void changeStartMonth (int);
	void changeStartTime (int);
	void changeEndDay (int);
	void changeEndMonth (int);
	void changeEndTime (int);
	void updateDueRanking();
	int getStartMonth();
	int getEndMonth();
	int getStartDate();
	int getEndDate();
	int getStartTime();
	int getEndTime();
	std::string getTaskName();
	std::string convertToMonth(int);
	std::string readEvent();
	std::string displayEvent();
	std::string getDeadline();
	std::string convertNumberToString(int);
	std::string convertTimeToString(int);
};

