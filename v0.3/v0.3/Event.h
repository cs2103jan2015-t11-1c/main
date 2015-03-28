#pragma once

#include <string>
#include <iostream>


class Event
{
private:
	std::string _title;
	int _endDay;
	int _endMonth;
	int _endTime;
	std::string _details;
	int _startDay;
	int _startMonth;
	int _startTime;
	bool _durationEvent;
	

public:
	
	Event(void);
	Event(std::string newTitle, int newDay, int newMonth, int newTime);
	~Event(void);
	void changeTitle(std:: string newTitle );
	void changeStartDay (int newDay );
	void changeStartMonth (int newMonth );
	void changeStartTime (int newTime);
	void changeEndDay (int newDay );
	void changeEndMonth (int newMonth );
	void changeEndTime (int newTime);
	void changeDetails (std::string newdetails);
	std::string getTaskName();
	std::string readEvent();
	std::string getDeadline();
	std::string convertNumberToString(int number);
	void updateDueRanking ();
	int _dueRanking;
};

