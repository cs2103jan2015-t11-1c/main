#include "cmdRepeat.h"

const int DAILY_REPTEAT_TIMES = 7;
const int WEEKLY_REPEAT_TIMES = 4;
const int MONTHLY_REPEAT_TIMES = 12;
const int NO_INTERVAL = 0;
const int DEFAULT_REPEATING_TIMES_INDICATOR = 0;
const int DAILY_INTERVAL = 1;
const int WEEKLY_INTERVAL = 7;
const int MONTHLY_INTERVAL = 30;
const int STARTING_YEAR = 2015;
const int WEEK = 7;
const int ZERO = 0;
const int FEBRUARY = 2;
const int APRIL = 4;
const int JUNE = 6;
const int SEPTEMBER = 9;
const int NOVEMBER = 11;
const int TWENTY_EIGHT = 28;
const int TWENTY_NINE = 29;
const int THIRTY = 30;
const int THIRTY_ONE = 31;
const int ONE = 1;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;
const int SIX = 6;
const int HUNDRED = 100;
const int FOUR_HUNDRED = 400;
const int INVALID_DAY = 7;
const std::string INVALID_REPEATING_EVENT_TYPE = "The event you want to repeat has no deadline!\n\n";
const std::string INVALID_REPEATING_TYPE = "Invalid Repeating Type.\n\n";
const std::string INVALID_DAY_MESSAGE = "Invalid day entered.\n\n";
const std::string STRING_DAILY = "daily";
const std::string STRING_WEEKLY = "weekly";
const std::string STRING_MONTHLY = "monthly";
const std::string STRING_MONDAY = "monday";
const std::string STRING_MON = "mon";
const std::string STRING_TUESDAY = "tuesday";
const std::string STRING_WEDNESDAY = "wednesday";
const std::string STRING_THURSDAY = "thursday";
const std::string STRING_FRIDAY = "friday";
const std::string STRING_SATURDAY = "saturday";
const std::string STRING_SUNDAY = "sunday";
const std::string STRING_TUE = "tue";
const std::string STRING_WED = "wed";
const std::string STRING_THUR = "thur";
const std::string STRING_FRI = "fri";
const std::string STRING_SAT = "sat";
const std::string STRING_SUN = "sun";
const std::string NEW_LINE = "\n";

CmdRepeat::CmdRepeat(void){
}

CmdRepeat::~CmdRepeat(void){
}

//repeat a task
std::string CmdRepeat::executecmdRepeat(Storage& _storage){
	_repeatDetails = _taskName;
	_parser.checkValidityAndGetDetails(_repeatDetails, _repeatCommand, _repeatTimes, _hasException, _exceptionDetails);
	determineEventNumber();
	determineRepeatType();

	if (isDefaultRepeatTimes(_repeatTimes)) {
	_repeatTimes = determineDefaultRepeatTimes(_repeatTimes);
	}

	Event repeatingEvent;
	if (_commandWord == REPEAT) {
		repeatingEvent = _storage.getEvent(_eventNumber);
	} else if (_commandWord == REPEATDONE) {
		repeatingEvent = _storage.getDoneEvent(_eventNumber);
	}

	try {
		if (repeatingEvent.isFloatingTask()) {
			throw INVALID_REPEATING_EVENT_TYPE;
		}

		if (repeatingEvent.isTimedTask()) {
			repeatTimedTask(repeatingEvent, _storage);
		} else {
			repeatDeadlineTask(repeatingEvent, _storage);
		}
	} catch (std::string& exceptionalMessage) {
		return exceptionalMessage;
	}

 	_storage.repeatEvent(_events);
	updateStorage(_storage);
	_events.clear();
	return NEW_LINE;
}

//convert repeat type to DAILY, WEEKLY, MONTHLY, EVERYWEEKDAY
CmdRepeat::repeatType CmdRepeat::determineRepeatType(){
	if (_repeatCommand == STRING_DAILY) {
		_type = DAILY;
	} else if (_repeatCommand == STRING_WEEKLY) {
		_type = WEEKLY;
	} else if (_repeatCommand == STRING_MONTHLY) {
		_type = MONTHLY;
	} else if (isWeekday(_repeatCommand)) {
		_type = EVERYWEEKDAY;
	} else {
		throw INVALID_REPEATING_TYPE;
	}
	return _type;
}

bool CmdRepeat::isWeekday(std::string repeatCommand){
	bool isWeekday = false;
	repeatCommand = lowercaseCommandWord(repeatCommand);

	if (repeatCommand == STRING_MONDAY || repeatCommand == STRING_TUESDAY || 
		repeatCommand == STRING_WEDNESDAY || repeatCommand == STRING_THURSDAY || 
		repeatCommand == STRING_FRIDAY || repeatCommand == STRING_SATURDAY || 
		repeatCommand == STRING_SUNDAY || repeatCommand == STRING_MON || 
		repeatCommand == STRING_TUE || repeatCommand == STRING_WED || 
		repeatCommand == STRING_THUR || repeatCommand == STRING_FRI || 
		repeatCommand == STRING_SAT || repeatCommand == STRING_SUN) {
		isWeekday = true;
	}
	return isWeekday;
}

bool CmdRepeat::isDefaultRepeatTimes(int repeatTimes){
	bool isDefault = false;
	if (repeatTimes == DEFAULT_REPEATING_TIMES_INDICATOR) {
		isDefault = true;
	}
	return isDefault;
}

int CmdRepeat::determineDefaultRepeatTimes(int repeatTimes){
	switch(_type)
	{
	case DAILY:
		return DAILY_REPTEAT_TIMES;
	case WEEKLY:
	case EVERYWEEKDAY:
		return WEEKLY_REPEAT_TIMES;
	case MONTHLY:
		return MONTHLY_REPEAT_TIMES;
	default:
		break;
	}
} 

int CmdRepeat::determineEventNumber(){
	_eventNumber = _taskNumberList.front();
	return _eventNumber;
}

int CmdRepeat::determineInterval(int month, int year){
	switch (_type)
	{
	case DAILY:
		return DAILY_INTERVAL;
	case WEEKLY:
	case EVERYWEEKDAY:
		return WEEKLY_INTERVAL;
	case MONTHLY:
		return getNumberOfDays(month, year);
	default:
		return NO_INTERVAL;
	}
}

void CmdRepeat::repeatDeadlineTask(Event repeatingEvent, Storage& _storage){
	int Tcount;	
	std::string eventTitle = repeatingEvent.getTaskName();
	int date = repeatingEvent.getEndDate();
	int month = repeatingEvent.getEndMonth();
	int time = repeatingEvent.getEndTime();
	int year = repeatingEvent.getEndYear();
	if (year != STARTING_YEAR){
		_findNextDate.changeDefaultYear(year);
	}

	int newDate;
	int newMonth;
	int newYear = STARTING_YEAR;
	getStartingRepeatDate(date, month, newYear, newDate, newMonth, newYear);

	int exception;
	if (_hasException) {
		exception = getExceptionTime(_exceptionDetails);
	}

	for (Tcount = 1; Tcount <= _repeatTimes; Tcount++) {
		Event newEvent(eventTitle, newDate, newMonth, time);
		if (newYear != STARTING_YEAR) {
			newEvent.changeEndYear(newYear);
		}

		if (isValidDate (newDate, newMonth, newYear)) {
			if (_hasException) {
				if (isValidEvent(newDate, newMonth, newYear, Tcount, exception)) {
					_events.push_back(newEvent);
				}
			} else {
				_events.push_back(newEvent);
			}
		}
		getNextDate(newDate, newMonth, newYear);
	}
}

void CmdRepeat::repeatTimedTask(Event repeatingEvent, Storage& _storage){
	int Tcount;	
	std::string eventTitle = repeatingEvent.getTaskName();
	int startDate = repeatingEvent.getStartDate();
	int startMonth = repeatingEvent.getStartMonth();
	int startTime = repeatingEvent.getStartTime();
	int startYear = repeatingEvent.getStartYear();
	int endDate = repeatingEvent.getEndDate();
	int endMonth = repeatingEvent.getEndMonth();
	int endTime = repeatingEvent.getEndTime();
	int endYear = repeatingEvent.getEndYear();
	if (startYear != _findNextDate.getYear()){
		_findNextDate.changeDefaultYear(startYear);
	}

	int newStartDate;
	int newStartMonth;
	int newStartYear = STARTING_YEAR;
	getStartingRepeatDate(startDate, startMonth, startYear, newStartDate, newStartMonth, newStartYear);

	int newEndDate;
	int newEndMonth;
	int newEndYear = STARTING_YEAR;
	getStartingRepeatDate(endDate, endMonth, endYear, newEndDate, newEndMonth, newEndYear);

	int exception;
	if (_hasException) {
		exception = getExceptionTime(_exceptionDetails);
	}

	for(Tcount = 1; Tcount <= _repeatTimes; Tcount++){
		Event newEvent(eventTitle, newEndDate, newEndMonth, endTime);
		newEvent.changeStartDay(newStartDate);
		newEvent.changeStartMonth(newStartMonth);
		newEvent.changeStartTime(startTime);
		if (newStartYear != STARTING_YEAR) {
			newEvent.changeStartYear(newStartYear);}
		if (newEndYear != STARTING_YEAR) {
			newEvent.changeEndYear(newEndYear);
		}

		if (isValidDate (newStartDate, newStartMonth, newStartYear) && isValidDate (newEndDate, newEndMonth, newEndYear)) {
			if (_hasException) {
				if (isValidEvent(newStartDate, newStartMonth, newStartYear, Tcount, exception)) {
					_events.push_back(newEvent);
				}
			} else {
				_events.push_back(newEvent);
			}
		}

		getNextDate(newStartDate, newStartMonth, newStartYear);
		getNextDate(newEndDate, newEndMonth, newEndYear);
	}
}

void CmdRepeat::getStartingRepeatDate(int date, int month, int year, int& newDate, int& newMonth, int& newYear){
	_findNextDate.changeDefaultYear(newYear);
	if (_type  == EVERYWEEKDAY) {
		getTheStartingDate(date, month, year, newDate, newMonth);
	} else {
		_interval = determineInterval(month, year);
		_findNextDate.calculate(date, month, _interval);
		if(_type == MONTHLY){
			newDate = date;
		} else {
			newDate = _findNextDate.getDay();
		}
		newMonth = _findNextDate.getMonth();
		newYear = _findNextDate.getYear();
	}
}

void CmdRepeat::getNextDate(int& newDate, int& newMonth, int& newYear){
	_findNextDate.changeDefaultYear(newYear);
	_interval = determineInterval(newMonth, newYear);
	_findNextDate.calculate(newDate, newMonth, _interval);		
	if(_type != MONTHLY){
		newDate = _findNextDate.getDay();
	}
	newMonth = _findNextDate.getMonth();
	newYear = _findNextDate.getYear();
}

bool CmdRepeat::isValidEvent(int date, int month, int year, int Tcount, int exception) {
	bool isValidEvent = false;
	if (((Tcount != exception) && (_type == WEEKLY || _type == EVERYWEEKDAY || _type == MONTHLY))
		|| ((!isExceptionDay(date, month, year, exception)) && (_type == DAILY))) {
			isValidEvent = true;
	}
	return isValidEvent;
}

bool CmdRepeat::isValidDate(int date, int month, int year){
	bool isValidDate = false;
	if (date <= getNumberOfDays(month, year)) {
		isValidDate = true;
	}
	return isValidDate;
}

bool CmdRepeat::isExceptionDay(int day, int month, int year, int exceptionDay){
	int weekdayToday = getWeekdayToday(day, month, year);
	bool isExceptionDay = false;
	if (weekdayToday == exceptionDay) {
		isExceptionDay = true;
	}
	return isExceptionDay;
}

int CmdRepeat::determineWeekday(std::string repeatCommand){
	std::string weekdayWord = repeatCommand;
	int _weekday;
	if (!isWeekday(weekdayWord)) { 
		return INVALID_DAY;
	}
	_weekday = changeWeekdayToInteger(weekdayWord);
	return _weekday;
}

std::string CmdRepeat::lowercaseCommandWord(std::string commandWord){
	int n = commandWord.size();
	for ( int i = 0; i < n; i++){
		if (commandWord[i] <='Z' && commandWord[i] >= 'A'){
			commandWord[i] = commandWord[i] - ('Z'-'z');
		}
	}
  return commandWord;
}

int CmdRepeat::changeWeekdayToInteger(std::string day){
	int weekday;
	std::string repeatDay = lowercaseCommandWord(day);
	if ( repeatDay  == STRING_MONDAY || repeatDay  == STRING_MON ) {
		weekday = ZERO;
	} else if (repeatDay  == STRING_TUESDAY || repeatDay == STRING_TUE) {
		weekday = ONE;
	} else if (repeatDay  == STRING_WEDNESDAY || repeatDay  == STRING_WED) {
		weekday = TWO;
	} else if (repeatDay  == STRING_THURSDAY || repeatDay  == STRING_THUR) {
		weekday = THREE;
	} else if (repeatDay  == STRING_FRIDAY || repeatDay  == STRING_FRI) {
		weekday = FOUR;
	} else if (repeatDay  == STRING_SATURDAY || repeatDay  == STRING_SAT) {
		weekday = FIVE;
	} else if (repeatDay  == STRING_SUNDAY || repeatDay  == STRING_SUN) {
		weekday = SIX;
	} 
	return weekday;
}

int CmdRepeat::getWeekdayToday(int date, int month, int year){
	int weekdayToday;

	if (year != STARTING_YEAR) {
		_findNextDate.changeDefaultYear(year);
	}
	_findNextDate.calculate(date, month, 0);
	weekdayToday = _findNextDate.getWeekDay();

	_findNextDate.changeDefaultYear(STARTING_YEAR);
	return weekdayToday;
}

std::string CmdRepeat::getTheStartingDate(int date, int month, int year, int& newDate, int& newMonth){
	int weekdayToday = getWeekdayToday(date, month, year);
	int repeatingWeekday = determineWeekday(_repeatCommand);

	try {
	if (repeatingWeekday == INVALID_DAY) {
		throw INVALID_DAY_MESSAGE;
	}
		int interval;
		if (weekdayToday < repeatingWeekday) {
			interval = repeatingWeekday - weekdayToday;
		} else {
			interval = repeatingWeekday + WEEK - weekdayToday;
		}

		_findNextDate.calculate(date, month, interval);
		newDate = _findNextDate.getDay();
		newMonth = _findNextDate.getMonth();
	} catch (std::string& invalid) {
		return invalid;
	}
}

int CmdRepeat::getExceptionTime(std::string exceptionDetails){
	if (isWeekday(exceptionDetails)) {
		return changeWeekdayToInteger(exceptionDetails);
	} else {
		return std::stoi(exceptionDetails);
	}
}

int CmdRepeat::getNumberOfDays(int month, int year){
	int numberOfDays;  
	if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)  {
		numberOfDays = THIRTY;  
	} else if (month == FEBRUARY) { 
		if (isLeapYear(year)) {
		numberOfDays = TWENTY_NINE;  
		} else {
		numberOfDays = TWENTY_EIGHT;  
		} 
	} else  {
		numberOfDays = THIRTY_ONE; 
	}
	return numberOfDays;
}

bool CmdRepeat::isLeapYear(int year){
	bool isLeapYear = false;
	if ((year % FOUR == ZERO && year % HUNDRED != ZERO) || (year % FOUR_HUNDRED == ZERO)) {
		isLeapYear = true;
	}
	return isLeapYear;
}

void CmdRepeat::updateStorage(Storage& _storage){
	_storage.sortActiveEventlist();
	_storage.sortDoneEventlist();
	_storage.synchronizeDrive();
}