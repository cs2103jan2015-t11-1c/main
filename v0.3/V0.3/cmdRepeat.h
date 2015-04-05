#pragma once
#include "logicbaseclass.h"
#include "findNextDate.h"
class cmdRepeat :
	public logicBaseClass
{
private:
	findNextDate _findNextDate;
	std::string _repeatDetails;
	enum repeatType{DAILY, WEEKLY, MONTHLY};
	repeatType _type;
	int _repeatTimes;
	int _eventNumber;
	int _interval;

public:
	cmdRepeat(void);
	~cmdRepeat(void);
	std::string executecmdRepeat(Storage&);
	void repeatTimedTask(Event, Storage&);
	void repeatDeadlineTask(Event, Storage&);
	std::string getRepeatType(std::string&);
	repeatType determineRepeatType(std::string&);
	int determineRepeatTimes(std::string&);
	void determineEventNumber();
	int determineInterval();
	bool isDefaultRepeat(std::string);
	bool isNumber(std::string&);
	std::string lowercaseCommandWord(std::string commandWord);
};