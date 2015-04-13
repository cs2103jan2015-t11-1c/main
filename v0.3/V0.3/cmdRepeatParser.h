//@author A0115253R
#pragma once
#include <iostream>
//repeat 1 daily/monthly/weekly 60
//repeat 1 every mon/tue / thurs
//repeat 1 daily except mon.tue.wed
//repeat 1 weekly except week 2
class CmdRepeatParser
{
private:
	std::string _repeatDetails; 
	std::string _repeatType;
	int _repeatTimes; 
	bool _hasException;
	std::string _exceptionDetail;

public:
	CmdRepeatParser(void);
	~CmdRepeatParser(void);
	bool hasException();
	bool isValidIndex(int);
	bool getDetailsForRepeatCertainDayOfAWeek(std::string repeatDetail);
	bool isDailyWeeklyMonthly(std::string );
	bool isCertainDayOfAWeek(std::string );
	bool getRepeatTimes(std::string);
	bool getExceptionDetails(std::string );
	bool checkValidityAndGetDetails(std::string ,std::string &,int &, bool &, std::string &); 
	bool isStringAnInteger(std::string );
	std::string lowercaseRepeatDetail(std::string );
	void initialzeAttributes();
};

