#include "findNextDate.h"


static int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static int daysInMonthLeapYear[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

findNextDate::findNextDate(void){
	_firstDayOfYear2015 = 3;
	_year = 2015;
}


findNextDate::~findNextDate(void){
}

void findNextDate::calculate(int day, int month, int numberOfDays ){	
	_currentDay = day;
	_currentMonth = month;
	_advanceNumberOfDays = numberOfDays;
	calculateTheNextDate();
}

bool findNextDate:: isLeapYear(){
	if ((_year % 4 == 0) && (_year % 100 != 0))
		return true;
	else if (_year % 400 == 0)
			return true;

	return false;
}

void findNextDate::advanceMonth(){
	while (_day > daysInMonth[_month] && _month < 13){
		_day = _day - daysInMonth[_month];
		_month++;
	}
	if (_month > 12) {
		_month = _month - 12;
		_year = _year + 1;}
}

void findNextDate::advanceMonthLeapYear(){
	while (_day > daysInMonthLeapYear[_month] && _month < 13){
		_day = _day - daysInMonthLeapYear[_month];
		_month++;
		}
	if (_month >12){
		_year = _year +1;
		_month = _month - 12;
	}
}

void findNextDate::calculateTheNextDate(){
	_day = _currentDay + _advanceNumberOfDays;
	_month = _currentMonth;
	if (isLeapYear()){
		advanceMonthLeapYear();}
	else { 
		advanceMonth(); }
	calculateExtraLongDay();
}
void findNextDate::calculateExtraLongDay(){
	while( _day > 31){
		if (isLeapYear()){
			advanceMonthLeapYear();}
		else { 
			advanceMonth(); }
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

int findNextDate::getYear(){
	return _year;
}

