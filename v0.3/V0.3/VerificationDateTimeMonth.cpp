#include "VerificationDateTimeMonth.h"
using namespace std;
#include <iostream>
VerificationDateTimeMonth::VerificationDateTimeMonth(void)
{
}

VerificationDateTimeMonth::~VerificationDateTimeMonth(void)
{
}

const int MAX_MINUTE = 60;
const int MAX_HOUR = 23;
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MIN_DATE = 1;
const int MAX_DATE = 31;
const int MAX_TIME = 2359;
const int MIN_TIME = 0000;
const int DATE_29 = 29;
const int DATE_30 = 30;



string VerificationDateTimeMonth::lowercaseMonth(string month){
	int n = month.size();
	for( int i = 0; i < n; i++){
		if(month[i] <='Z' && month[i] >= 'A'){
			month[i] = month[i] - ('Z'-'z');
		}
	}
  return month;
}


//checking for timedtasks whether ending time is later than starting time.
bool VerificationDateTimeMonth::isEndingLaterThanStarting(int startingTime, int startingMonth, int startingDate, int endingTime, int endingMonth, int endingDate){
	bool isEndingLaterThanStarting = false;
	bool areValidMonths = false;
	bool areValidDates = false;
    bool areValidTime = false;

	bool isStartingDateMonthTimeValid = VerificationDateTimeMonth::isDateMonthTimeValid(startingDate, startingMonth, startingTime);
	bool isEndingingDateMonthTimeValid = VerificationDateTimeMonth::isDateMonthTimeValid(endingDate, endingMonth, endingTime);

	if(!isStartingDateMonthTimeValid || !isEndingingDateMonthTimeValid){
		return false;
	}

	if(startingMonth <= endingMonth){
		areValidMonths = true;
	}

	if(areValidMonths && startingMonth == endingMonth){
		if(startingDate <= endingDate ){
			areValidDates = true;
		}
	}
	else if(areValidMonths && startingMonth < endingMonth){
		areValidDates = true;
		areValidTime = true;
	}
	
	if( startingMonth == endingMonth && startingDate == endingDate){
		if(startingTime < endingTime){
			areValidTime = true;
		}
	}
	else if(startingMonth == endingMonth && startingDate < endingDate){
		areValidTime = true;
	}

	if(areValidDates && areValidMonths && areValidTime){
		isEndingLaterThanStarting = true;
	}

	return isEndingLaterThanStarting;
}



//check whether a single date, month and time input is valid
bool VerificationDateTimeMonth::isDateMonthTimeValid(int date, int month, int time){
	bool is_MonthValid = VerificationDateTimeMonth::isMonthValid(month);
	bool is_DateValid; 
	if(is_MonthValid){
		is_DateValid = VerificationDateTimeMonth::isDateValid(date,month);
	}
	else{
		is_DateValid = false;
	}
	
	bool is_TimeValid = VerificationDateTimeMonth::isTimeValid(time);

	bool is_DateMonthTimeValid = false;

	if(is_DateValid && is_MonthValid && is_TimeValid){
		is_DateMonthTimeValid = true;
	}

	return is_DateMonthTimeValid;
}


bool VerificationDateTimeMonth::isTimeValid(int time){
	bool isTimeValid = true;

	if(!(time >= MIN_TIME && time <= MAX_TIME)){
		isTimeValid = false;
	}
	else{
		if(time / 10 == 0 ){
			isTimeValid = true;
		}
		else if(time / 100 == 0 && time >= MAX_MINUTE){
			isTimeValid = false;
		}
		else if( time / 1000 == 0){
			int minute = time % 100;
			
			if(minute >= MAX_MINUTE){
				isTimeValid = false;
			}
		}
		else if(time / 10000 == 0){
			int minute = time % 100;
			int hour = time / 100;
			if(minute >= MAX_MINUTE || hour > MAX_HOUR){
				isTimeValid = false;
			}
		}

	}

	return isTimeValid;
}

bool VerificationDateTimeMonth::isMonthValid(int month){
	bool isMonthValid = false;
	if(month >= MIN_MONTH && month <= MAX_MONTH){
		isMonthValid = true;
	}
	return isMonthValid;
}

bool VerificationDateTimeMonth::isDateValid(int date, int month){
    
	switch(month){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (date >= MIN_DATE && date <= MAX_DATE){
			return true;
		}
		else{
			return false;
		}
	case 2:
		if(date >= MIN_DATE && date <= DATE_29){
			return true;
		}
		else{
			return false;
		}
		
	case 4:
	case 6:
	case 9:
	case 11:
		if(date >= MIN_DATE && date <= DATE_30){
			return true;
		}
		else{
			return false;
		}
		
	default:
		return false;
	}


}
