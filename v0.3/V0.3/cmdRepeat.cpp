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
const std::string ERROR_MESSAGE = "Invalid Repeating Times";
const std::string INVALID_REPEATING_TYPE = "Invalid Repeating Type";
const std::string STRING_DAILY = "daily";
const std::string STRING_WEEKLY = "weekly";
const std::string STRING_MONTHLY = "monthly";
const std::string STRING_EVERY_MONDAY = "every monday";
const std::string STRING_EVERY_TUESDAY = "every tuesday";
const std::string STRING_EVERY_WEDNESDAY = "every wednesday";
const std::string STRING_EVERY_THURSDAY = "every thursday";
const std::string STRING_EVERY_FRIDAY = "every friday";
const std::string STRING_EVERY_SATURDAY = "every saturday";
const std::string STRING_EVERY_SUNDAY = "every sunday";

cmdRepeat::cmdRepeat(void){
}

cmdRepeat::~cmdRepeat(void){
}

//repeat a task
std::string cmdRepeat::executecmdRepeat(Storage& _storage){
	_repeatDetails = _taskName;
	_parser.checkValidityAndGetRepeatDetails(_repeatDetails, &_repeatCommand, &_repeatTimes, &_hasException, &_exceptionDetails);
	determineEventNumber();
	determineRepeatType();
	_repeatTimes = determineRepeatTimes(_repeatTimes);
	_interval = determineInterval();

	Event repeatingEvent;

	if (_commandWord == REPEAT) {
		repeatingEvent = _storage.getEvent(_eventNumber);
	}else if (_commandWord == REPEATDONE) {
		repeatingEvent = _storage.getDoneEvent(_eventNumber);
	}

	if (repeatingEvent.isTimedTask()) {
		repeatTimedTask(repeatingEvent, _storage);
	}else{
		repeatDeadlineTask(repeatingEvent, _storage);
	}

	_storage.sortActiveEventlist();
	_storage.sortDoneEventlist();
	_storage.synchronizeDrive();
	return "\n";
}

//convert repeat type to DAILY, WEEKLY, MONTHLY, EVERYWEEKDAY
cmdRepeat::repeatType cmdRepeat::determineRepeatType(){
	if (_repeatCommand == STRING_DAILY) {
		_type = DAILY;
	}else if (_repeatCommand == STRING_WEEKLY) {
		_type = WEEKLY;
	}else if (_repeatCommand == STRING_MONTHLY) {
		_type = MONTHLY;
	}else if (isRepeatWeekday(_repeatCommand)) {
		_type = EVERYWEEKDAY;
	}else {
		std::cout << INVALID_REPEATING_TYPE << std::endl;
	}
	
	return _type;
}

bool cmdRepeat::isRepeatWeekday(std::string repeatCommand){
	bool isRepeatWeekday = false;

	if (repeatCommand == STRING_EVERY_MONDAY || repeatCommand == STRING_EVERY_TUESDAY || repeatCommand == 
		STRING_EVERY_WEDNESDAY || repeatCommand == STRING_EVERY_THURSDAY || repeatCommand == STRING_EVERY_FRIDAY
		|| repeatCommand == STRING_EVERY_SATURDAY || repeatCommand == STRING_EVERY_SUNDAY) {
		isRepeatWeekday = true;
	}

	return isRepeatWeekday;
}

int cmdRepeat::determineRepeatTimes(int repeatTimes){
	if (repeatTimes == DEFAULT_REPEATING_TIMES_INDICATOR) {
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
	} else {
		return repeatTimes;
	}
}

void cmdRepeat::determineEventNumber(){
	_eventNumber = _taskNumberList.front();
}

int cmdRepeat::determineInterval(){
	switch (_type)
	{
	case DAILY:
		return DAILY_INTERVAL;
	case WEEKLY:
	case EVERYWEEKDAY:
		return WEEKLY_INTERVAL;
	case MONTHLY:
		return MONTHLY_INTERVAL;
	default:
		return NO_INTERVAL;
	}
}

void cmdRepeat::repeatDeadlineTask(Event repeatingEvent, Storage& _storage){
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
	int newYear;

	if (_type  == EVERYWEEKDAY) {
		getTheStartingDate(date, month, newDate, newMonth);
	} else {
	_findNextDate.calculate(date, month, _interval);
	newDate = _findNextDate.getDay();
	newMonth = _findNextDate.getMonth();
	newYear = _findNextDate.getYear();
	}

	for(Tcount = 0; Tcount < _repeatTimes; Tcount++){
		Event newEvent(eventTitle, newDate, newMonth, time);
		if (newYear != STARTING_YEAR) {
			newEvent.changeEndYear(newYear);
		}
		_storage.addEvent(newEvent);
		if (newYear != STARTING_YEAR) {
			_findNextDate.changeDefaultYear(newYear);
		}
		_findNextDate.calculate(newDate, newMonth, _interval);
		newDate = _findNextDate.getDay();
		newMonth = _findNextDate.getMonth();
		newYear = _findNextDate.getYear();
	}

}

int cmdRepeat::determineWeekday(std::string repeatCommand){
	std::string weekdayWord;
	int Tcount;
	Tcount = repeatCommand.find_first_of(" ");
	weekdayWord = repeatCommand.substr(Tcount+1);
	
	int weekday;
	weekday = changeWeekdayToInteger(weekdayWord);

	return weekday;
}

int cmdRepeat::changeWeekdayToInteger(std::string day){
	int weekday;
	if ( day == "monday") {
		weekday = 0;
	} else if (day == "tuesday") {
		weekday = 1;
	} else if (day == "wednesday") {
		weekday == 2;
	} else if (day == "thursday") {
		weekday == 3;
	} else if (day == "friday") {
		weekday == 4;
	} else if (day == "saturday") {
		weekday == 5;
	} else if (day == "sunday") {
		weekday == 6;
	}

	return weekday;
}

int cmdRepeat::getWeekdayToday(int date, int month){
	int weekdayToday;
	_findNextDate.calculate(date, month, 0);
	weekdayToday = _findNextDate.getWeekDay();

	return weekdayToday;
}

void cmdRepeat::getTheStartingDate(int date, int month, int& newDate, int& newMonth){
	int weekdayToday = getWeekdayToday(date, month);
	int repeatingWeekday = determineWeekday(_repeatCommand);
	int interval;
	if (weekdayToday <= repeatingWeekday) {
		interval = repeatingWeekday - weekdayToday;
	} else {
		interval = repeatingWeekday + 7 - weekdayToday;
	}
	_findNextDate.calculate(date, month, interval);

	newDate = _findNextDate.getDay();
	newMonth = _findNextDate.getMonth();
}

void cmdRepeat::repeatTimedTask(Event repeatingEvent, Storage& _storage){
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

	if (startYear != STARTING_YEAR){
		_findNextDate.changeDefaultYear(startYear);
	}
	_findNextDate.calculate(startDate, startMonth, _interval);
	int newStartDate;
	int newStartMonth;
	int newStartYear;
	newStartDate = _findNextDate.getDay();
	newStartMonth = _findNextDate.getMonth();
	newStartYear = _findNextDate.getYear();

	if (endYear != STARTING_YEAR){
		_findNextDate.changeDefaultYear(endYear);
	}
	_findNextDate.calculate(endDate, endMonth, _interval);
	int newEndDate;
	int newEndMonth;
	int newEndYear;
	newEndDate = _findNextDate.getDay();
	newEndMonth = _findNextDate.getMonth();
	newEndYear = _findNextDate.getYear();

	for(Tcount = 0; Tcount < _repeatTimes; Tcount++){
		Event newEvent(eventTitle, newEndDate, newEndMonth, endTime);
		newEvent.changeStartDay(newStartDate);
		newEvent.changeStartMonth(newStartMonth);
		newEvent.changeStartTime(startTime);
		if (newStartYear != STARTING_YEAR) {
			newEvent.changeStartYear(newStartYear);
			newEvent.changeEndYear(newEndYear);
		}
		_storage.addEvent(newEvent);

		if (newStartYear != STARTING_YEAR){
			_findNextDate.changeDefaultYear(newStartYear);
		}
		
		_findNextDate.calculate(newStartDate, newStartMonth, _interval);
		newStartDate = _findNextDate.getDay();
		newStartMonth = _findNextDate.getMonth();
		newStartYear = _findNextDate.getYear();

		if (newEndYear != STARTING_YEAR){
			_findNextDate.changeDefaultYear(newEndYear);
		}
		_findNextDate.calculate(newEndDate, newEndMonth, _interval);
		newEndDate = _findNextDate.getDay();
		newEndMonth = _findNextDate.getMonth();
		newEndYear = _findNextDate.getYear();
	}
}