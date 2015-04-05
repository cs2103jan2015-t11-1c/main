#pragma once
#include "logicbaseclass.h"
class cmdRepeat :
	public logicBaseClass
{
private:
	enum repeatType{DAILY, WEEKLY, MONTHLY};
	repeatType type;
	int repeatTimes;

public:
	cmdRepeat(void);
	~cmdRepeat(void);
	std::string executecmdRepeat(Storage& _storage);
	std::string getRepeatType();
	void determineRepeatType();
	void determineRepeatTimes();
};