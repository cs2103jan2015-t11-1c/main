#pragma once
#include <string>

class VerificationDateTimeMonth
{
public:
	VerificationDateTimeMonth(void);
	~VerificationDateTimeMonth(void);
	bool isEndingLaterThanStarting(int , int , int , int , int , int );
	bool isDateMonthTimeValid(int , int , int );
	bool isTimeValid(int );
	bool isMonthValid(int );
	bool isDateValid(int, int );
	std::string lowercaseMonth(std::string month);
};

