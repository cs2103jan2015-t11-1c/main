#pragma once
#include <iostream>
class cmdRepeatParser
{
private:
	std::string _repeatDetails; //this one is just the string after the eventnumber
	//I need these attributes hahaha

	//string _type; this is the repeat type: daily, weekly, monthly, every mondayblah blah blah
	//this type pass me the string can alr?
	//int _repeatTimes; like: repeat 1 daily 60, then _repeatTimes = 60
	//bool _hasException, if got exception then return true? this one discuss later
	//exception details need break down TTT


public:
	cmdRepeatParser(void);
	~cmdRepeatParser(void);

	std::string getRepeatType(std::string& _repeatDetails);
	std::string getRepeatTimes(std::string& _repeatDetails);
};

