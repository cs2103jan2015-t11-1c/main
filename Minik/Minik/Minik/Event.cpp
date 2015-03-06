#include "Event.h"


Event::Event(void)
{
}

Event::Event(string newTitle, string newDate, string newTime)
{	_title = newTitle;
	_date = newDate;
	_time = newTime;
}


Event::~Event(void)
{
}

void Event::changeTitle( string newTitle )
{	_title = newTitle; 
}

void Event::changeDate ( string newDate )
{	_date = newDate;
}

void Event::changeTime ( string newTime)
{	_time = newTime;
}

void Event::changeDetails (string newdetails)
{	_details = newdetails;
}

