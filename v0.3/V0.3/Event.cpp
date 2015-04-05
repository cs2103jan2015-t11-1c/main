#include "Event.h"

static int DEFAUlTYEAR = 2015;

Event::Event(void)
{	
}


Event::Event(std::string newTitle, int newDay, int newMonth, int newTime)
{	_title = newTitle;
	_endDay= newDay;
	_endMonth = newMonth;
	_endTime = newTime;
	_endYear = DEFAUlTYEAR;
	_startYear = DEFAUlTYEAR;
	updateDueRanking();
	_durationEvent = false;
}

Event::~Event(void)
{
}

std::string Event::displayEvent(){
	std::ostringstream Ostring;
	Ostring << "[";
	if (_endDay <= 0 || _endDay >31 || _endMonth <= 0 || _endMonth >12 || _endTime < 0 || _endTime >2359 ) {
		Ostring << std::setfill('-') << std::setw(29) <<  "] ";
		Ostring << _title; }
	else if(_durationEvent == false) {
		Ostring << "by " << convertNumberToString(_endDay);
		Ostring << " " << convertToMonth(_endMonth);
		int hour;
		int minute;
		hour = _endTime / 100;
		minute = _endTime % 100;
		Ostring << " " << convertNumberToString(hour) << ":" << convertNumberToString(minute);
		if (_endYear != DEFAUlTYEAR){
			Ostring << " Year: " << _endYear; }
		Ostring << std::setw(14) << "] ";
		Ostring << _title; 
	}
	else {
		Ostring << convertNumberToString(_startDay);
		Ostring << " " << convertToMonth(_startMonth);
		int hour;
		int minute;
		hour = _startTime / 100;
		minute = _startTime % 100;
		Ostring << " " << convertNumberToString(hour) << ":" << convertNumberToString(minute);
		if (_startYear != DEFAUlTYEAR){
			Ostring << " Year: " << _endYear; }
		Ostring << " - ";
		Ostring << convertNumberToString(_endDay);
		Ostring << " " << convertToMonth(_endMonth);
		hour = _endTime / 100;
		minute = _endTime % 100;
		Ostring << " " << convertNumberToString(hour) << ":" << convertNumberToString(minute);
		if (_endYear != DEFAUlTYEAR){
			Ostring << " Year: " << _endYear; }
		Ostring << "] ";
		Ostring << _title;
	}

	return Ostring.str();

}

std::string Event::readEvent()
{	std::string finalString;
	if (_endDay <= 0 || _endDay >31 || _endMonth <= 0 || _endMonth >12 ){
		finalString = _title + " no specific deadline";}
	else if( _durationEvent == false){
		finalString = _title + " is due " + convertNumberToString(_endDay) + " " 
		+ convertNumberToString(_endMonth) + " " + convertTimeToString(_endTime);
		if (_endYear != DEFAUlTYEAR){
			finalString = finalString + "Year: " + convertTimeToString(_endYear); }
	}
	else { finalString = _title + " start from " + convertNumberToString(_startDay) + " " + 
	convertNumberToString(_startMonth) + " " + convertNumberToString(_startTime);
	if (_startYear != DEFAUlTYEAR){
		finalString = finalString + " Year: " + convertTimeToString(_startYear); }
	finalString = finalString + " is due " + convertNumberToString(_endDay) + " " + 
	convertNumberToString(_endMonth)+ " " + convertTimeToString(_endTime);
	if (_endYear != DEFAUlTYEAR){
		finalString = finalString + " Year: " + convertTimeToString(_endYear); }
	}
	return finalString;
}

// Convert 1 or 2 digit number to 2 char string.
std::string Event::convertNumberToString(int number){
	if (number/10 == 0){
		std::string tempString;
		tempString = std::to_string(number);
		return "0" + tempString;}
	else return std::to_string(number);
}

std::string Event::convertToMonth(int i){
	if(i == 1) {
		return "Jan"; }
	else if (i == 2) {
		return "Feb"; }
	else if (i == 3) {
		return "Mar"; }
	else if (i == 4) {
		return "Apr"; }
	else if (i == 5) {
		return "May"; }
	else if (i == 6) {
		return "Jun"; }
	else if (i == 7) {
		return "Jul"; }
	else if (i == 8) {
		return "Aug"; }
	else if (i == 9) {
		return "Sep"; }
	else if (i == 10) {
		return "Oct"; }
	else if (i == 11) {
		return "Nov"; }
	else if (i == 12) {
		return "Dec"; }

	return "invalid month";
}

//Convert time to a 4 char string.
std::string Event::convertTimeToString(int number){
	std::string tempString;
	tempString = std::to_string(number);
	if (number /10 == 0)
		return "000" + tempString;
	else if (number/100 == 0)
		return "00" + tempString;
	else if (number/1000 == 0)
		return "0" + tempString;

	return tempString;
}

//Display the deadline of a particular task.
std::string Event::getDeadline()
{	return convertNumberToString(_endDay) + " " + convertToMonth(_endMonth) +
" " + convertTimeToString(_endTime);
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

void Event::changeEndYear (int newYear){
	_endYear = newYear;
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

void Event::changeStartYear (int newYear){
	_startYear = newYear;
}

//For the purpose of sorting, arrange the events from earliest year and then earliest month
//and then earliest endday and then earliest hour.
//Events with no deadline are display first.
void Event::updateDueRanking()
{	if(_endDay <= 0 || _endDay >31 || _endMonth <= 0 || _endMonth >12 || _endTime < 0 || _endTime >2359 )
	_dueRanking = 1.0*1000000000000 ;
else
	_dueRanking = _endYear*100000000 +_endMonth*1000000 + _endDay*10000 + _endTime;
}

std::string Event::getTaskName()
{	return _title;
}

int Event::getStartMonth()
{	return _startMonth;
}

int Event::getStartDate()
{	return _startDay;
}

int Event::getEndMonth()
{	return _endMonth;
}

int Event::getEndDate()
{	return _endDay;
}

int Event::getStartTime()
{   return _startTime;
}

int Event::getEndTime()
{   return _endTime;
}

std::string Event::saveEvent(){
	return "";
}