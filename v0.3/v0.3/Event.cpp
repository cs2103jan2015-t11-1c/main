#include "Event.h"


Event::Event(void)
{	
}


Event::Event(std::string newTitle, std::string newDate, std::string newTime)
{	_title = newTitle;
	_endDate = newDate;
	_endTime = newTime;
}


Event::~Event(void)
{
}

std::string Event::readEvent()
{	return _title + " is due " + _endDate + " " + _endTime;
}

std::string Event::getDeadline()
{	return _endDate + _endTime;
}


void Event::changeTitle(std:: string newTitle )
{	_title = newTitle; 
}

void Event::changeEndDate (std:: string newDate )
{	_endDate = newDate;
}

void Event::changeEndTime (std:: string newTime)
{	_endTime = newTime;
}

void Event::changeStartDate (std::string newDate )
{	_startDate = newDate;	
}

void Event::changeStartTime (std::string newTime)
{	_startTime= newTime;
}

void Event::changeDetails (std::string newdetails)
{	_details = newdetails;
}

