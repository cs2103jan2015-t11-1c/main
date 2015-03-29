#include "Event.h"


Event::Event(void)
{	
}


Event::Event(std::string newTitle, int newDay, int newMonth, int newTime)
{	_title = newTitle;
	_endDay= newDay;
	_endMonth = newMonth;
	_endTime = newTime;
	updateDueRanking();
	_durationEvent = false;
}


Event::~Event(void)
{
}

std::string Event::readEvent()
{
	if (_endDay == -1){
		return _title + " no specific deadline";}
	else if( _durationEvent == false){
	return _title + " is due " + convertNumberToString(_endDay) + " " 
		+ convertNumberToString(_endMonth) + " " + std::to_string(_endTime);
	}
	else { return _title + " start from " + convertNumberToString(_startDay) + " " + 
	convertNumberToString(_startMonth) + " " + convertNumberToString(_startTime) + 
	" is due " + convertNumberToString(_endDay) + " " + convertNumberToString(_endMonth)
	+ " " + std::to_string(_endTime);
	}
}
std::string Event::convertNumberToString(int number){
	
	if (number/10 == 0){
		std::string tempString;
		tempString = std::to_string(number);
		return "0" + tempString;}
	else return std::to_string(number);
}


std::string Event::getDeadline()
{	return convertNumberToString(_endDay) + convertNumberToString(_endMonth)	
	+ std::to_string(_endTime);
}


void Event::changeTitle(std:: string newTitle )
{	_title = newTitle; 
}

void Event::changeEndDay(int newDay)
{	_endDay = newDay;
	updateDueRanking();
}

void Event::changeEndMonth (int newMonth )
{	_endMonth = newMonth;
	updateDueRanking();
}

void Event::changeEndTime (int newTime)
{	_endTime = newTime;
	updateDueRanking();
}

void Event::changeStartDay (int newDay )
{	_startDay = newDay;	
	_durationEvent = true;
	
}

void Event::changeStartMonth (int newMonth)
{	_startMonth=newMonth;
	_durationEvent = true;
}

void Event::changeStartTime (int newTime)
{	_startTime= newTime;
	_durationEvent = true;
}

void Event::changeDetails (std::string newdetails)
{	_details = newdetails;
}

void Event::updateDueRanking()
{	if(_endDay == 1)
	_dueRanking = 0;
	else
	_dueRanking = _endMonth*1000000 + _endDay*10000 + _endTime;
}

std::string Event::getTaskName()
{	return _title;
}

