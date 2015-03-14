#pragma once

#include <string>
#include <iostream>


class Event
{
private:
	std::string _title;
	std::string _date;
	std::string _time;
	std::string _details;

public:
	
	Event(void);
	Event(std::string newTitle, std::string newDate, std::string newTime);
	~Event(void);
	void changeTitle(std:: string newTitle );
	void changeDate (std::string newDate );
	void changeTime (std::string newTime);
	void changeDetails (std::string newdetails);
	std::string readEvent();
};

