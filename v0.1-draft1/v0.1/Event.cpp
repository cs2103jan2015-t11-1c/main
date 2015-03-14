#include "Event.h"


Event::Event(void)
{	
}


Event::Event(std::string newTitle, std::string newDate, std::string newTime)
{	_title = newTitle;
	_date = newDate;
	_time = newTime;
}


Event::~Event(void)
{
}

std::string Event::readEvent()
{	return _title + " is due " + _date + " " + _time;
}

void Event::changeTitle(std:: string newTitle )
{	_title = newTitle; 
}

void Event::changeDate (std:: string newDate )
{	_date = newDate;
}

void Event::changeTime (std:: string newTime)
{	_time = newTime;
}

void Event::changeDetails (std::string newdetails)
{	_details = newdetails;
}

