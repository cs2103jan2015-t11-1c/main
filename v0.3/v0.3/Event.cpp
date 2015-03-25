#include "Event.h"


Event::Event(void)
{	
}


Event::Event(std::string newTitle, std::string newDay, std::string newMonth, std::string newTime)
{	_title = newTitle;
	_endDay=newDay;
	_endMonth=newMonth;
	_endTime = newTime;
}


Event::~Event(void)
{
}

std::string Event::readEvent()
{	if( _startDay == "" && _startMonth == "" && _startTime == "")
	return _title + " is due " + _endDay + " " + _endMonth + " " + _endTime;
	else return _title + " start from " + _startDay + " " + _startMonth + " " +
	_startTime + " is due " + _endDay + " " + _endMonth + " " + _endTime;

}

std::string Event::getDeadline()
{	return _endDay +_endMonth + _endTime;
}


void Event::changeTitle(std:: string newTitle )
{	_title = newTitle; 
}

void Event::changeEndDay(std:: string newDay)
{	_endDay = newDay;
}

void Event::changeEndMonth (std:: string newMonth )
{	_endMonth = newMonth;
}

void Event::changeEndTime (std:: string newTime)
{	_endTime = newTime;
}

void Event::changeStartDay (std::string newDay )
{	_startDay = newDay;	
}

void Event::changeStartMonth (std::string newMonth)
{	_startMonth=newMonth;
}

void Event::changeStartTime (std::string newTime)
{	_startTime= newTime;
}

void Event::changeDetails (std::string newdetails)
{	_details = newdetails;
}

