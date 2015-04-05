#include "findNextDate.h"

static int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

findNextDate::findNextDate(void){
}


findNextDate::~findNextDate(void){
}

findNextDate::findNextDate(int day, int month, int numberOfDays ){	
	_currentDay = day;
	_currentMonth = month;
	_advanceNumberOfDays = numberOfDays;
	_firstDayOfYear2015 = 3;
}

void findNextDate::calculateTheNextDate(){
	_day = _currentDay + _advanceNumberOfDays;
	_month = _currentMonth;
	while (_day > daysInMonth[_month]){
		_day = _day - daysInMonth[_month];
		_month++;
	}
}

int findNextDate::totalNumberOfDays(){
	int monthFromJanuary;
	int numberOfDaysInMonth;
	numberOfDaysInMonth = _day;
	monthFromJanuary = 1;
	while (monthFromJanuary < _month){
		numberOfDaysInMonth = numberOfDaysInMonth + daysInMonth[monthFromJanuary];
		monthFromJanuary ++;
	}

	return numberOfDaysInMonth;
}
//weekday is the number of days since monday.
void findNextDate::calculateTheWeekDay(){
	int numberOfDays;
	int weekDay;
	numberOfDays = totalNumberOfDays();
	numberOfDays = numberOfDays % 7;
	weekDay = _firstDayOfYear2015 + numberOfDays;
	weekDay = weekDay % 7;
	if (weekDay == 0){
		_weekDay = 3;}
	else if (weekDay == 1){
		_weekDay = 4;}
	else if (weekDay == 2){
		_weekDay = 5;}
	else if (weekDay == 3){
		_weekDay = 6;}
	else if (weekDay == 4){
		_weekDay = 0;}
	else if (weekDay == 5){
		_weekDay = 1;}
	else if (weekDay == 6){
		_weekDay = 2;}
}

int findNextDate::getDay(){
	return _day;
}

int findNextDate::getMonth(){
	return _month;
}

int findNextDate::getWeekDay(){
	return _weekDay;
}



