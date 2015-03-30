#pragma once
#include <string>
using namespace std;

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
	string lowercaseMonth(string month);
};

