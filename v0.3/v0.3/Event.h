#pragma once

#include <string>
#include <iostream>


class Event
{
private:
	std::string _title;
	std::string _endDay;
	std::string _endMonth;
	std::string _endTime;
	std::string _details;
	std::string _startDay;
	std::string _startMonth;
	std::string _startTime;

public:
	
	Event(void);
	Event(std::string newTitle, std::string newDay, std::string newMonth, std::string newTime);
	~Event(void);
	void changeTitle(std:: string newTitle );
	void changeStartDay (std::string newDay );
	void changeStartMonth (std::string newMonth );
	void changeStartTime (std::string newTime);
	void changeEndDay (std::string newDay );
	void changeEndMonth (std::string newMonth );
	void changeEndTime (std::string newTime);
	void changeDetails (std::string newdetails);
	std::string readEvent();
	std::string getDeadline();
};

