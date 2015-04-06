#include "findNextDate.h"


const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int daysInMonthLeapYear[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int STARTING_YEAR = 2015;

findNextDate::findNextDate(void){
	_firstDayOfYear2015 = 3;
	_year = STARTING_YEAR;
}


findNextDate::~findNextDate(void){
}

void findNextDate::calculate(int day, int month, int numberOfDays ){	
	_currentDay = day;
	_currentMonth = month;
	_advanceNumberOfDays = numberOfDays;
	calculateTheNextDate();
	calculateTheWeekDay();
}

bool findNextDate:: isLeapYear(int year){
	if ((year % 4 == 0) && (year % 100 != 0))
		return true;
	else if (year % 400 == 0)
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
	if (isLeapYear(_year)){
		advanceMonthLeapYear();}
	else { 
		advanceMonth(); }
	calculateExtraLongDay();
}
void findNextDate::calculateExtraLongDay(){
	while( _day > 31){
		if (isLeapYear(_year)){
			advanceMonthLeapYear();}
		else { 
			advanceMonth(); }
	}
}

int findNextDate::calculateDayInMonth(){
	int monthFromJanuary = 1;
	int numberOfDaysInMonth;
	numberOfDaysInMonth = _day;
	while (monthFromJanuary < _month){
		numberOfDaysInMonth = numberOfDaysInMonth + daysInMonth[monthFromJanuary];
		monthFromJanuary ++;
		}
	return numberOfDaysInMonth;
}

int findNextDate::calculateDayInMonthForLeapYear(){
	int monthFromJanuary = 1;
	int numberOfDaysInMonth;
	numberOfDaysInMonth = _day;
	while (monthFromJanuary < _month){
		numberOfDaysInMonth = numberOfDaysInMonth + daysInMonthLeapYear[monthFromJanuary];
		monthFromJanuary ++;
		}
	return numberOfDaysInMonth;
}

int findNextDate::calculateDayInYear(){
	int year = _year;
	int numberOfDaysInYear = 0;
	while ( year > STARTING_YEAR){
	year = year - 1;
	 if(isLeapYear(year)){
		 numberOfDaysInYear = numberOfDaysInYear + 366;}
	 else {
		 numberOfDaysInYear = numberOfDaysInYear + 365;}
	}

	return numberOfDaysInYear;
}


int findNextDate::totalNumberOfDays(){

	int numberOfDaysInMonth;
	if(	_year > STARTING_YEAR){
		if( isLeapYear(_year)){
			numberOfDaysInMonth = calculateDayInMonthForLeapYear();
		} else {
			numberOfDaysInMonth = calculateDayInMonth();
		}
		numberOfDaysInMonth = numberOfDaysInMonth + calculateDayInYear();
	} else {
		if( isLeapYear(_year)){
		numberOfDaysInMonth = calculateDayInMonthForLeapYear();
		} else {
			numberOfDaysInMonth = calculateDayInMonth();
				}
		}

	return numberOfDaysInMonth;
}
//weekday is the number of days since monday.
void findNextDate::calculateTheWeekDay(){
	int numberOfDays;
	int weekDay;
	numberOfDays = totalNumberOfDays() - 1;
	numberOfDays = numberOfDays % 7;
	weekDay = _firstDayOfYear2015 + numberOfDays;
	weekDay = weekDay % 7;
	_weekDay = weekDay;
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

void findNextDate::changeDefaultYear(int year){
	_year = year;
}
