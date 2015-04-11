//@author A0116455H
//The information of a particular event is all stored in this class.

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>


class Event {
private:
	std::string _title;
	int _endDay;
	int _endMonth;
	int _endTime;
	int _endYear;
	int _startDay;
	int _startMonth;
	int _startTime;
	int _startYear;
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
	void changeStartYear (int);
	void changeEndDay (int);
	void changeEndMonth (int);
	void changeEndTime (int);
	void changeEndYear (int);
	void updateDueRanking();
	int getStartMonth();
	int getEndMonth();
	int getStartDate();
	int getEndDate();
	int getStartTime();
	int getEndTime();
	int getStartYear();
	int getEndYear();
	bool isTimedTask();
	bool isValidDateMonthTime();
	bool isFloatingTask();
	std::string getTaskName();
	std::string convertToMonth(int);
	std::string displayEvent();
	std::string getDeadline();
	std::string saveEvent();
	std::string convertNumberToString(int);
	std::string convertTimeToString(int);
};

