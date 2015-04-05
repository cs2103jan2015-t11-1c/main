#include "cmdRepeat.h"

const int DAILY_REPTEAT_TIMES = 7;
const int WEEKLY_REPEAT_TIMES = 4;
const int MONTHLY_REPEAT_TIMES = 12;
const int NO_INTERVAL = 0;
const int DAILY_INTERVAL = 1;
const int WEEKLY_INTERVAL = 7;
const int MONTHLY_INTERVAL = 30;
const int STARTING_YEAR = 2015;
const std::string ERROR_MESSAGE = "Invalid Repeating Times";
const std::string INVALID_REPEATING_TYPE = "Invalid Repeating Type";
const std::string STRING_DAILY = "daily";
const std::string STRING_WEEKLY = "weekly";
const std::string STRING_MONTHLY = "monthly";

cmdRepeat::cmdRepeat(void){
}

cmdRepeat::~cmdRepeat(void){
}

//repeat a task
std::string cmdRepeat::executecmdRepeat(Storage& _storage){
	_repeatDetails = _taskName;
	determineEventNumber();
	determineRepeatType(_repeatDetails);
	_repeatTimes = determineRepeatTimes(_repeatDetails);
	_interval = determineInterval();

	Event repeatingEvent;

	if(_commandWord == REPEAT){
		repeatingEvent = _storage.getEvent(_eventNumber);
	}else if(_commandWord == REPEATDONE){
		repeatingEvent = _storage.getDoneEvent(_eventNumber);
	}

	if(repeatingEvent.isTimedTask()){
		repeatTimedTask(repeatingEvent, _storage);
	}else{
		repeatDeadlineTask(repeatingEvent, _storage);
	}

	_storage.sortActiveEventlist();
	_storage.sortDoneEventlist();
	_storage.synchronizeDrive();
	return "\n";
}

//extract repeat frequency(daily, weekly, monthly)
std::string cmdRepeat::getRepeatType(std::string& _repeatDetails){
	std::string repeatType;
	int Tcount;
	Tcount = _repeatDetails.find_first_of(" ");
	if(Tcount != std::string::npos){
		repeatType = _repeatDetails.substr(0, Tcount);
		_repeatDetails = _repeatDetails.substr(Tcount+1);
	}else{
		repeatType = _repeatDetails;
		_repeatDetails.clear();
	}

	return repeatType;
}

//convert repeat type to DAILY, WEEKLY, MONTHLY
cmdRepeat::repeatType cmdRepeat::determineRepeatType(std::string& _repeatDetails){
	std::string repeatType;
	repeatType = getRepeatType(_repeatDetails);
	if (repeatType == STRING_DAILY) {
		_type = DAILY;
	}else if (repeatType == STRING_WEEKLY) {
		_type = WEEKLY;
	}else if (repeatType == STRING_MONTHLY) {
		_type = MONTHLY;
	}else {
		std::cout << INVALID_REPEATING_TYPE << std::endl;
	}

	return _type;
}

int cmdRepeat::determineRepeatTimes(std::string& _repeatDetails){
	if (isDefaultRepeat(_repeatDetails)) {
		switch(_type)
		{
		case DAILY:
			return DAILY_REPTEAT_TIMES;
		case WEEKLY:
			return WEEKLY_REPEAT_TIMES;
		case MONTHLY:
			return MONTHLY_REPEAT_TIMES;
		default:
			break;
		}
	}else{
		if (isNumber(_repeatDetails)){
			_repeatTimes= std::stoi(_repeatDetails);
		}else{
			std::cout << ERROR_MESSAGE << std::endl;
		}
	}

	return _repeatTimes;
}

bool cmdRepeat::isNumber(std::string& string)
{
	bool isNumber = true;
	std::string::iterator iter = string.begin();
	for (iter = string.begin(); iter != string.end(); iter++){
		if (!isdigit(*iter)){
			isNumber = false;
		}
	}

	return  isNumber;
}

bool cmdRepeat::isDefaultRepeat(std::string _repeatDetails){
	bool isDefaultRepeat = false;

	if (_repeatDetails.empty()){
		isDefaultRepeat = true;
	}

	return isDefaultRepeat;
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
	_findNextDate.calculate(date, month, _interval);
	int newDate;
	int newMonth;
	int newYear;
	newDate = _findNextDate.getDay();
	newMonth = _findNextDate.getMonth();
	newYear = _findNextDate.getYear();
	for(Tcount = 0; Tcount < _repeatTimes; Tcount++){
		Event newEvent(eventTitle, newDate, newMonth, time);
		if (newYear != STARTING_YEAR) {
			newEvent.changeEndYear(newYear);}
		_storage.addEvent(newEvent);
		_findNextDate.calculate(newDate, newMonth, _interval);
		newDate = _findNextDate.getDay();
		newMonth = _findNextDate.getMonth();
		newYear = _findNextDate.getYear();
	}

}

void cmdRepeat::repeatTimedTask(Event repeatingEvent, Storage& _storage){
	int Tcount;	
	std::string eventTitle = repeatingEvent.getTaskName();
	int startDate = repeatingEvent.getStartDate();
	int startMonth = repeatingEvent.getStartMonth();
	int startTime = repeatingEvent.getStartTime();
	int endDate = repeatingEvent.getEndDate();
	int endMonth = repeatingEvent.getEndMonth();
	int endTime = repeatingEvent.getEndTime();

	_findNextDate.calculate(startDate, startMonth, _interval);
	int newStartDate;
	int newStartMonth;
	int newStartYear;
	newStartDate = _findNextDate.getDay();
	newStartMonth = _findNextDate.getMonth();
	newStartYear = _findNextDate.getYear();

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
			newEvent.changeEndYear(newStartYear);}
		_storage.addEvent(newEvent);
		
		_findNextDate.calculate(newStartDate, newStartMonth, _interval);
		newStartDate = _findNextDate.getDay();
		newStartMonth = _findNextDate.getMonth();
		newStartYear = _findNextDate.getYear();

		_findNextDate.calculate(newEndDate, newEndMonth, _interval);
		newEndDate = _findNextDate.getDay();
		newEndMonth = _findNextDate.getMonth();
		newEndYear = _findNextDate.getYear();
	}

}
