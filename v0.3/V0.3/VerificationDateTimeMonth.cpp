#include "VerificationDateTimeMonth.h"

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

VerificationDateTimeMonth::VerificationDateTimeMonth(void) {
}

VerificationDateTimeMonth::~VerificationDateTimeMonth(void) {
}

std::string VerificationDateTimeMonth::lowercaseMonth(std::string month) {
	int n = month.size();

	for (int i = 0; i < n; i ++) {
		if (month[i] <= 'Z' && month[i] >= 'A') {
			month[i] = month[i] - ('Z' - 'z');
		}
	}

  return month;
}

//checking for timedtasks whether ending time is later than starting time.
bool VerificationDateTimeMonth::isEndingLaterThanStarting (int startingTime, int startingMonth, int startingDate, int endingTime, int endingMonth, int endingDate) {
	bool isEndingLaterThanStarting = false;
	bool areValidMonths = false;
	bool areValidDates = false;
	bool areValidTime = false;
	bool isStartingDateMonthTimeValid = isDateMonthTimeValid(startingDate, startingMonth, startingTime);
	bool isEndingingDateMonthTimeValid = isDateMonthTimeValid(endingDate, endingMonth, endingTime);

	if (!isStartingDateMonthTimeValid || !isEndingingDateMonthTimeValid) {
		return false;
	}

	if (startingMonth <= endingMonth) {
		areValidMonths = true;
	} else {
		areValidMonths = false;
	}

	if (areValidMonths && startingMonth == endingMonth) {

		if (startingDate <= endingDate ) {
			areValidDates = true;
		} else {
			areValidDates = false;
		}

	} else if (areValidMonths && startingMonth < endingMonth) {
		areValidDates = true;
		areValidTime = true;
	}
	
	if (startingMonth == endingMonth && startingDate == endingDate) {
		
		if (startingTime < endingTime) {
			areValidTime = true;
		} else {
			areValidTime = false;
		}

	} else if (startingMonth == endingMonth && startingDate < endingDate) {
		areValidTime = true;
	}

	if (areValidDates && areValidMonths && areValidTime) {
		isEndingLaterThanStarting = true;
	} else {
		isEndingLaterThanStarting = false;
	}

	return isEndingLaterThanStarting;
}

//check whether a single date, month and time input is valid
bool VerificationDateTimeMonth::isDateMonthTimeValid(int date, int month, int time) {
	bool isTMonthValid = isMonthValid(month);
	bool isTDateValid = false; 
	bool isTDateMonthTimeValid = false;

	if (isTMonthValid) {
		isTDateValid = isDateValid(date,month);
	} else {
		isTDateValid = false;
	}
	
	bool isTTimeValid = isTimeValid(time);
	
	if (isTDateValid && isTMonthValid && isTTimeValid) {
		isTDateMonthTimeValid = true;
	} else {
		isTDateMonthTimeValid = false;
	}

	return isTDateMonthTimeValid;
}

bool VerificationDateTimeMonth::isTimeValid(int time) {
	bool isTimeValid = true;

	if (!(time >= MIN_TIME && time <= MAX_TIME)) {
		isTimeValid = false;
	} else {

		if (time / 10 == 0 ) {
			isTimeValid = true;
		} else if (time / 100 == 0 && time >= MAX_MINUTE) {
			isTimeValid = false;
		} else if ( time / 1000 == 0) {
			int minute = time % 100;
			
			if (minute >= MAX_MINUTE) {
				isTimeValid = false;
			} else {
				isTimeValid = true;
			}

		} else if(time / 10000 == 0) {
			int minute = time % 100;
			int hour = time / 100;

			if (minute >= MAX_MINUTE || hour > MAX_HOUR) {
				isTimeValid = false;
			} else {
				isTimeValid = true;
			}

		} else {
			isTimeValid = false;
		}

	}

	return isTimeValid;
}

bool VerificationDateTimeMonth::isMonthValid(int month) {
	bool isMonthValid = false;

	if (month >= MIN_MONTH && month <= MAX_MONTH) {
		isMonthValid = true;
	} else {
		isMonthValid = false;
	}

	return isMonthValid;
}

bool VerificationDateTimeMonth::isDateValid(int date, int month) {
    
	switch (month) {
	case 1:

	case 3:

	case 5:

	case 7:

	case 8:

	case 10:

	case 12:
		if (date >= MIN_DATE && date <= MAX_DATE) {
			return true;
		} else {
			return false;
		}

	case 2:
		if (date >= MIN_DATE && date <= DATE_29) {
			return true;
		} else {
			return false;
		}
		
	case 4:

	case 6:

	case 9:

	case 11:
		if (date >= MIN_DATE && date <= DATE_30) {
			return true;
		} else {
			return false;
		}
		
	default:
		return false;
	}

}
