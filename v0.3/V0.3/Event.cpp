//@author A0116455H
//This is the class used to store information about an Event.
//All the functions here support retrieve, edit and display of
//a single Event information.
//By default the year stored is 2015.
//If there is a change of year, changeYear functions must be used.
//Display function will display year out if the year of event is not 2015.

#include "Event.h"
#include <assert.h>

const std::string EMPTY_SPACE = " ";
const std::string EMPTY_STRING = "";
const std::string START_INfO_IDENTIFIER = "Starting Info: ";
const std::string END_INFO_IDENTIFIER = "Ending Info: ";
const std::string NIL_IDENTIFIER = "Nil";
const std::string OPEN_SQUARE_BRACKET = "[";
const std::string CLOSE_SQUARE_BRACKET = "]";
const std::string DASH = "-";
const std::string BY = "by";
const std::string YEAR = "Year";
const std::string COLON = ":";
const std::string ZERO = "0";
const std::string JANUARY = "Jan";
const std::string FEBRUARY = "Feb";
const std::string MARCH = "Mar";
const std::string APRIL = "Apr";
const std::string MAY = "May";
const std::string JUNE = "Jun";
const std::string JULY = "Jul";
const std::string AUGUST = "Aug";
const std::string SEPTEMBER = "Sep";
const std::string OCTOBER = "Oct";
const std::string NOVEMBER = "Nov";
const std::string DECEMBER = "Dec";
const std::string INVALID_MONTH = "Invalid Month";
const std::string ERROR_YEAR = "Error: Setting year earlier than 2015 is not allowed. \\n";
const std::string RECURRING_NUMBER = "Recurring number: ";
const int DEFAUlTYEAR = 2015;
const int THOUSAND = 1000;
const int HUNDRED = 100;
const int TEN = 10;
const int NUMBER_ZERO = 0;
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MIN_DATE = 1;
const int MAX_DATE = 31;
const int MAX_TIME = 2359;
const int MIN_TIME = 0000;
const int JANUARY_IN_NUMBER = 1;
const int FEBRUARY_IN_NUMBER = 2;
const int MARCH_IN_NUMBER = 3;
const int APRIL_IN_NUMBER = 4;
const int MAY_IN_NUMBER = 5;
const int JUNE_IN_NUMBER = 6;
const int JULY_IN_NUMBER = 7;
const int AUGUST_IN_NUMBER = 8;
const int SEPTEMBER_IN_NUMBER = 9;
const int OCTOBER_IN_NUMBER = 10;
const int NOVEMBER_IN_NUMBER = 11;
const int DECEMBER_IN_NUMBER = 12;
const int DAY_RANKING = 10000;
const int MONTH_RANKING = 1000000;
const int YEAR_RANKING = 100000000;
const int NO_DUE_DATE_RANKING = 2000000000;
const int NO_DUE_DATE_SPACING = 28;
const int NO_START_TIME_DEFAULT_YEAR_SPACING = 13;
const int NO_START_TIME_NON_DEFAULT_YEAR_SPACING = 24;
const int DEFAUlT_START_NON_DEFAULT_END_YEAR_SPACING = 12;

Event::Event(void) {	
}


Event::Event(std::string newTitle, int newDay, int newMonth, int newTime) {
	assert(newTitle != EMPTY_STRING );
	_title = newTitle;
	_endDay= newDay;
	_endMonth = newMonth;
	_endTime = newTime;
	_endYear = DEFAUlTYEAR;
	_startYear = DEFAUlTYEAR;
	updateDueRanking();
	_durationEvent = false;
	_recurringTaskSeries = 0;
}

Event::~Event(void) {
}

std::string Event::displayEvent() {
	std::ostringstream Ostring;
	Ostring << OPEN_SQUARE_BRACKET;
	if (!isValidDateMonthTime()) {
		Ostring << std::setfill('-') << std::setw(NO_DUE_DATE_SPACING);
		Ostring << CLOSE_SQUARE_BRACKET;
		Ostring << EMPTY_SPACE << _title; 
	} else {
		if (_durationEvent == false) {
			Ostring << BY << EMPTY_SPACE << convertNumberToString(_endDay);
			Ostring << EMPTY_SPACE << convertToMonth(_endMonth);
			int hour = _endTime / HUNDRED;
			int minute = _endTime % HUNDRED;
			Ostring << EMPTY_SPACE << convertNumberToString(hour) << COLON; 
			Ostring	<< convertNumberToString(minute);
			if (_endYear != DEFAUlTYEAR) {
				Ostring << EMPTY_SPACE << YEAR << COLON << EMPTY_SPACE << _endYear;
				Ostring << std::setw(NO_START_TIME_NON_DEFAULT_YEAR_SPACING);
				Ostring << CLOSE_SQUARE_BRACKET << EMPTY_SPACE << _title; 	
			} else {
				Ostring << std::setw(NO_START_TIME_DEFAULT_YEAR_SPACING); 
				Ostring << CLOSE_SQUARE_BRACKET << EMPTY_SPACE;
				Ostring << _title; 
			}
		} else {
			Ostring << convertNumberToString(_startDay);
			Ostring << EMPTY_SPACE << convertToMonth(_startMonth);
			int hour = _startTime / HUNDRED;
			int minute = _startTime % HUNDRED;
			Ostring << EMPTY_SPACE << convertNumberToString(hour);
			Ostring << COLON << convertNumberToString(minute);
			if (_startYear != DEFAUlTYEAR) {
				Ostring << EMPTY_SPACE << YEAR << COLON << EMPTY_SPACE;
				Ostring << _startYear;
			} 
			Ostring << EMPTY_SPACE << DASH << EMPTY_SPACE;
			Ostring << convertNumberToString(_endDay);
			Ostring << EMPTY_SPACE << convertToMonth(_endMonth);
			hour = _endTime / HUNDRED;
			minute = _endTime % HUNDRED;
			Ostring << EMPTY_SPACE << convertNumberToString(hour) << COLON; 
			Ostring << convertNumberToString(minute);
			if (_endYear != DEFAUlTYEAR) {
				Ostring << EMPTY_SPACE << YEAR << COLON << EMPTY_SPACE; 
				Ostring << _endYear; 
			}
			if (_startYear == DEFAUlTYEAR && _endYear != DEFAUlTYEAR) {
				Ostring << std::setw(DEFAUlT_START_NON_DEFAULT_END_YEAR_SPACING);
			}
			Ostring << CLOSE_SQUARE_BRACKET << EMPTY_SPACE;
			Ostring << _title;
		}
	}
	return Ostring.str();
}

// Convert 1 or 2 digit number to 2 char string.
std::string Event::convertNumberToString(int number) {
	if (number / TEN == NUMBER_ZERO) {
		std::string tempString;
		tempString = std::to_string(number);
		return ZERO + tempString;
	} else { 
		return std::to_string(number);
	}
}

std::string Event::convertToMonth(int i) {
	if (i == JANUARY_IN_NUMBER) {
		return JANUARY; 
	} else if (i == FEBRUARY_IN_NUMBER) {
		return FEBRUARY; 
	} else if (i == MARCH_IN_NUMBER) {
		return MARCH;
	} else if (i == APRIL_IN_NUMBER) {
		return APRIL;
	} else if (i == MAY_IN_NUMBER) {
		return MAY;
	} else if (i == JUNE_IN_NUMBER) {
		return JUNE; 
	} else if (i == JULY_IN_NUMBER) {
		return JULY; 
	} else if (i == AUGUST_IN_NUMBER) {
		return AUGUST; 
	} else if (i == SEPTEMBER_IN_NUMBER) {
		return SEPTEMBER; 
	} else if (i == OCTOBER_IN_NUMBER) {
		return OCTOBER; 
	} else if (i == NOVEMBER_IN_NUMBER) {
		return NOVEMBER; 
	} else if (i == DECEMBER_IN_NUMBER) {
		return DECEMBER; 
	}
	return INVALID_MONTH;
}

//Convert time to a 4 char string.
std::string Event::convertTimeToString(int number) {
	std::string tempString;
	tempString = std::to_string(number);
	if (number /TEN == NUMBER_ZERO) {
		return ZERO + ZERO + ZERO + tempString;
	} else if (number/HUNDRED == NUMBER_ZERO) {
		return  ZERO + ZERO + tempString;
	} else if (number/THOUSAND == NUMBER_ZERO) {
		return  ZERO + tempString;
	}
	return tempString;
}

//Display the deadline of a particular task.
std::string Event::getDeadline() {	
	std::string tempString = convertNumberToString(_endDay);
	tempString = tempString + EMPTY_SPACE + convertToMonth(_endMonth);
	tempString = tempString + EMPTY_SPACE + convertTimeToString(_endTime);
	return tempString;
}


void Event::changeTitle(std::string newTitle) {	
	assert(newTitle != EMPTY_STRING );
	_title = newTitle; 
}

void Event::changeEndDay(int newDay) {	
	_endDay = newDay;
	updateDueRanking();
}

void Event::changeEndMonth (int newMonth) {
	_endMonth = newMonth;
	updateDueRanking();
}

void Event::changeEndTime (int newTime) {
	_endTime = newTime;
	updateDueRanking();
}

void Event::changeEndYear (int newYear) {
	if (newYear < DEFAUlTYEAR) {
		throw std::string(ERROR_YEAR);
	}
	_endYear = newYear;
	updateDueRanking();
}

void Event::changeStartDay (int newDay) {
	_startDay = newDay;
	if(isTimedTask()) {
		_durationEvent = true;
	} else {
		_durationEvent = false;
	}
}

void Event::changeStartMonth (int newMonth) {
	_startMonth = newMonth;
	if(isTimedTask()) {
		_durationEvent = true;
	} else {
		_durationEvent = false;
	}
}

void Event::changeStartTime (int newTime) {
	_startTime= newTime;
	if(isTimedTask()) {
		_durationEvent = true;
	} else { 
		_durationEvent = false;
	}
}

void Event::changeStartYear (int newYear) {
	if (newYear < DEFAUlTYEAR) {
		throw std::string(ERROR_YEAR);
	}
	_startYear= newYear;
}

void Event::changeRecurringTaskSeries(int series) {
	_recurringTaskSeries = series;
}

//For the purpose of sorting, arrange the events from earliest year and
//then earliest month and then earliest endday and then earliest hour.
//Events with no deadline are display first.
void Event::updateDueRanking() {
	if(!isValidDateMonthTime()) {
		_dueRanking = NO_DUE_DATE_RANKING ;
	} else {
		_dueRanking = _endYear % 100 * YEAR_RANKING +_endMonth * MONTH_RANKING;
		_dueRanking = _dueRanking + _endDay * DAY_RANKING + _endTime;
	}
}

std::string Event::getTaskName() {
	return _title;
}

int Event::getStartMonth() {
	return _startMonth;
}

int Event::getStartDate() {
	return _startDay;
}

int Event::getEndMonth() {
	return _endMonth;
}

int Event::getEndDate() {
	return _endDay;
}

int Event::getStartTime() {
	return _startTime;
}

int Event::getEndTime() {
	return _endTime;
}

int Event::getRecurringTaskSeries() {
	return _recurringTaskSeries;
}

//Display all information of a Event out for saving data to local file.
//Easier for advance user to change data in a local drive.
std::string Event::saveEvent() {
	std::ostringstream Ostring;
	Ostring << _title << EMPTY_SPACE;
	Ostring << START_INfO_IDENTIFIER;
	if (!_durationEvent) {
		Ostring << NIL_IDENTIFIER << EMPTY_SPACE;
	} else {
		Ostring << convertNumberToString(_startDay) << EMPTY_SPACE; 
		Ostring << convertNumberToString(_startMonth) << EMPTY_SPACE;
		Ostring << convertTimeToString(_startTime) << EMPTY_SPACE; 
		Ostring << convertTimeToString(_startYear) << EMPTY_SPACE;
	}
	Ostring << END_INFO_IDENTIFIER ;
	if(!isValidDateMonthTime()) {
		Ostring << NIL_IDENTIFIER << EMPTY_SPACE;
	} else {
		Ostring << convertNumberToString(_endDay) << EMPTY_SPACE;
		Ostring	<< convertNumberToString(_endMonth) << EMPTY_SPACE;
		Ostring << convertTimeToString(_endTime) << EMPTY_SPACE;
		Ostring << convertTimeToString(_endYear);
	}
	if ( _recurringTaskSeries > 0) {
		Ostring << EMPTY_SPACE << RECURRING_NUMBER << _recurringTaskSeries;
	}
	return Ostring.str();
}

bool Event::isTimedTask() {
	bool isValid = true;
	if(_startDay < MIN_DATE || _startDay > MAX_DATE) {
		isValid = false;
	}
	if(_startMonth < MIN_MONTH || _startMonth > MAX_MONTH) {
		isValid = false;
	}
	if(_startTime < MIN_TIME || _startTime > MAX_TIME) {
		isValid = false;
	}
	return isValid;
}

int Event::getStartYear() {
	return _startYear;
}

int Event::getEndYear() {
	return _endYear;
}

bool Event::isValidDateMonthTime() {
	bool isValid = true;
	if(_endDay < MIN_DATE || _endDay > MAX_DATE) {
		isValid = false;
	}
	if(_endMonth < MIN_MONTH || _endMonth > MAX_MONTH) {
		isValid = false;
	}
	if(_endTime < MIN_TIME || _endTime > MAX_TIME) {
		isValid = false;
	}
	return isValid;
}

bool Event::isFloatingTask() {
	if(isValidDateMonthTime()) {
		return false;
	} else {
		return true;
	}
}