//This class will find the next date when given current day
//and the number of days to the next date.
//week number of the next date are calculated also.
//week number is the number of days since Monday.
//0 is Monday, 1 is Tuesday, and 6 is Sunday.
//By default this class assume year is 2015.
//If the year is not 2015, need to set the year to correct year
//before calling calculate function. 
#include "findNextDate.h"

const int DAYS_IN_MONTH[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int DAYS_IN_MONTH_LEAP_YEAR[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int STARTING_YEAR = 2015;
const int THURSDAY = 3;
const int NUMBER_OF_DAYS_IN_LEAP_YEAR = 366;
const int NUMBER_OF_DAYS_IN_NON_LEAP_YEAR = 365;
const int NUMBER_OF_DAYS_IN_A_WEEK = 7;
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MIN_DATE = 1;
const int MAX_DATE = 31;
const int PREVIOUS_OR_NEXT = 1;
const int LEAP_YEAR_CONDITION_FOUR = 4;
const int LEAP_YEAR_CONDITION_HUNDRED = 100;
const int LEAP_YEAR_CONDITION_FOUR_HUNDRED = 400;
const int ZERO = 0;

//Assumption year is 2015 and the first day of 2015 is Thursday.
//This program cannot used to calculate year earlier than 2015.
findNextDate::findNextDate(void){
	_firstDayOfYear2015 = THURSDAY;
	_year = STARTING_YEAR;
}


findNextDate::~findNextDate(void){
}

//Calculate the next date when given current date and number of days
//to next date. Week number of the next date is calculated too.
void findNextDate::calculate(int day, int month, int numberOfDays ){	
	_currentDay = day;
	_currentMonth = month;
	_advanceNumberOfDays = numberOfDays;
	calculateTheNextDate();
	calculateTheWeekDay();
}

bool findNextDate:: isLeapYear(int year){
	if ((year % LEAP_YEAR_CONDITION_FOUR == ZERO) && (year % LEAP_YEAR_CONDITION_HUNDRED != ZERO))
		return true;
	else if (year % LEAP_YEAR_CONDITION_FOUR_HUNDRED == ZERO)
			return true;

	return false;
}

//Shift the number of days according to days in non leap year month.
void findNextDate::advanceMonth(){
	while (_day > DAYS_IN_MONTH[_month] && _month <= MAX_MONTH){
		_day = _day - DAYS_IN_MONTH[_month];
		_month++;
	}
	if (_month > MAX_MONTH) {
		_month = _month - MAX_MONTH;
		_year = _year + PREVIOUS_OR_NEXT;}
}

//Shift the number of days according to days in leap year month.
void findNextDate::advanceMonthLeapYear(){
	while (_day > DAYS_IN_MONTH_LEAP_YEAR[_month] && _month <= MAX_MONTH){
		_day = _day - DAYS_IN_MONTH_LEAP_YEAR[_month];
		_month++;
		}
	if (_month > MAX_MONTH){
		_year = _year + PREVIOUS_OR_NEXT;
		_month = _month - MAX_MONTH;
	}
}

//Find out the next day and month and year.
void findNextDate::calculateTheNextDate(){
	_day = _currentDay + _advanceNumberOfDays;
	_month = _currentMonth;
	if (isLeapYear(_year)){
		advanceMonthLeapYear();}
	else { 
		advanceMonth(); }
	calculateExtraLongDay();
}

//For extreme case that 2 dates are separated by more than 1 year.
void findNextDate::calculateExtraLongDay(){
	while( _day > MAX_DATE){
		if (isLeapYear(_year)){
			advanceMonthLeapYear();
		} else { 
			advanceMonth(); }
	}
}

//Find the total number of days before a particular month in non leap year.
int findNextDate::calculateDayInMonth(){
	int monthFromJanuary = MIN_MONTH;
	int numberOfDaysInMonth;
	numberOfDaysInMonth = _day;
	while (monthFromJanuary < _month){
		numberOfDaysInMonth = numberOfDaysInMonth + DAYS_IN_MONTH[monthFromJanuary];
		monthFromJanuary ++;
		}
	return numberOfDaysInMonth;
}

//Find the total number of days before a particular month in leap year.
int findNextDate::calculateDayInMonthForLeapYear(){
	int monthFromJanuary = MIN_MONTH;
	int numberOfDaysInMonth;
	numberOfDaysInMonth = _day;
	while (monthFromJanuary < _month){
		numberOfDaysInMonth = numberOfDaysInMonth + DAYS_IN_MONTH_LEAP_YEAR[monthFromJanuary];
		monthFromJanuary ++;
		}
	return numberOfDaysInMonth;
}

//Calculate the number of days in complete years from 2015 to a particular year.
int findNextDate::calculateDayInYear(){
	int year = _year;
	int numberOfDaysInYear = ZERO;
	while ( year > STARTING_YEAR){
		year = year - PREVIOUS_OR_NEXT;
	 if(isLeapYear(year)){
		 numberOfDaysInYear = numberOfDaysInYear + NUMBER_OF_DAYS_IN_LEAP_YEAR;}
	 else {
		 numberOfDaysInYear = numberOfDaysInYear + NUMBER_OF_DAYS_IN_NON_LEAP_YEAR;}
	}

	return numberOfDaysInYear;
}

//Calculate the total number of days since 1 Jan 2015.
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

//Weekday is the number of days since monday.
//Calculate which weekday the current day is.
void findNextDate::calculateTheWeekDay(){
	int weekDay;
	weekDay = _firstDayOfYear2015 + totalNumberOfDays() - PREVIOUS_OR_NEXT;
	weekDay = weekDay % NUMBER_OF_DAYS_IN_A_WEEK;
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

//When this class is used to calculate date beyond 2015.
//This function must be called to change year before calculate functions.
void findNextDate::changeDefaultYear(int year){
	_year = year;
}
