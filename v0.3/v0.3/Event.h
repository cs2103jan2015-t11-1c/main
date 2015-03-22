#pragma once

#include <string>
#include <iostream>


class Event
{
private:
	std::string _title;
	std::string _endDate;
	std::string _endTime;
	std::string _details;
	std::string _startDate;
	std::string _startTime;

public:
	
	Event(void);
	Event(std::string newTitle, std::string newDate, std::string newTime);
	~Event(void);
	void changeTitle(std:: string newTitle );
	void changeStartDate (std::string newDate );
	void changeStartTime (std::string newTime);
	void changeEndDate (std::string newDate );
	void changeEndTime (std::string newTime);
	void changeDetails (std::string newdetails);
	std::string readEvent();
	std::string getDeadline();
};

