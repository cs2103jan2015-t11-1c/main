#include "cmdRepeat.h"

const int DAILY_REPTEAT_TIMES = 7;
const int WEEKLY_REPEAT_TIMES = 4;
const int MONTHLY_REPEAT_TIMES = 12;
const int NO_INTERVAL = 0;
const int DAILY_INTERVAL = 1;
const int WEEKLY_INTERVAL = 7;
const int MONTHLY_INTERVAL = 30;
const int STARTING_YEAR = 2015;

cmdRepeat::cmdRepeat(void){
}

cmdRepeat::~cmdRepeat(void){
}

std::string cmdRepeat::executecmdRepeat(Storage& _storage){
	_repeatDetails = _taskName;
	determineEventNumber();
	determineRepeatType(_repeatDetails);
	_repeatTimes = determineRepeatTimes(_repeatDetails);
	_interval = determineInterval();
	int Tcount;
	
	Event repeatingEvent;

	if(_commandWord == REPEAT){
		repeatingEvent = _storage.getEvent(_eventNumber);
	}else if(_commandWord == REPEATDONE){
		repeatingEvent = _storage.getDoneEvent(_eventNumber);
	}else{
		std::cout << "Error commandWord!" << std::endl;
	}

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


	return "";
}

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

cmdRepeat::repeatType cmdRepeat::determineRepeatType(std::string& _repeatDetails){
	std::string repeatType;
	repeatType = getRepeatType(_repeatDetails);
	if(repeatType == "daily"){
		_type = DAILY;
	}else if(repeatType == "weekly"){
		_type = WEEKLY;
	}else if(repeatType == "monthly"){
		_type = MONTHLY;
	}

	return _type;
}

int cmdRepeat::determineRepeatTimes(std::string& _repeatDetails){
	if(isDefaultRepeat(_repeatDetails)){
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
		//if (isdigit(_repeatDetails))

	 _repeatTimes= std::stoi(_repeatDetails);
	}

	return _repeatTimes;
}
/*
bool cmdRepeat::isNumber(std::string& string)
{
    bool isNumber = true;
	std::string::iterator iter = string.begin();
    for (iter = string.begin(), iter != string.end(), iter++){
		if(!isdigit(*iter)){
			isNumber = false;
		}
	}

    return  isNumber;
}
*/
bool cmdRepeat::isDefaultRepeat(std::string _repeatDetails){
	bool isDefaultRepeat = false;

	if(_repeatDetails.empty()){
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