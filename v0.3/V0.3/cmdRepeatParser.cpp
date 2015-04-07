#include "cmdRepeatParser.h"
#include <string>

const static std::string EMPTY_STRING = "";
const static std::string INVALID_REPEAT_DETAILS = "Sorry, invalid repeat details.";
const static std::string EXCEPT_STRING = "except";
const static int DEFAULT_TIMES = 0;
const static std::string STRING_DAILY = "daily";
const static std::string STRING_WEEKLY = "weekly";
const static std::string STRING_MONTHLY = "monthly";
const static std::string STRING_EVERY = "every";

cmdRepeatParser::cmdRepeatParser(void){
}

cmdRepeatParser::~cmdRepeatParser(void){
}

void cmdRepeatParser::initialzeAttributes() {
	_repeatDetails = EMPTY_STRING;
	_repeatType = EMPTY_STRING;
	_repeatTimes = DEFAULT_TIMES;
	_exceptionType = EMPTY_STRING;
}

bool cmdRepeatParser::checkValidityAndGetRepeatDetails(std::string repeatDetail,std::string &repeatType,int &repeatTimes, bool &isWithException, std::string &exceptionType) {
	initialzeAttributes();

	repeatDetail = lowercaseRepeatDetail(repeatDetail);
	_repeatDetails = repeatDetail;
	bool isValid = false;
	bool isDefault = false;
	bool hasAnException = hasException();
	
	if(isDailyWeeklyMonthly(repeatDetail)){

		if(!hasAnException) {
			isValid = getRepeatTimesForDailyWeeklyMonthly(repeatDetail);
		} else {

			if(getRepeatTimesForDailyWeeklyMonthly(repeatDetail)) {
				isValid = getExceptionTimes(repeatDetail);
			} 

		}
	}  else if(isCertainDayOfAWeek(repeatDetail)) {

		if(!hasAnException) {
			isValid = getDetailsForRepeatCertainDayOfAWeek( repeatDetail);
		} else {
			if(getDetailsForRepeatCertainDayOfAWeek(repeatDetail)) {
				isValid = getExceptionTimes(repeatDetail);
			}
		}
	} else {
		isValid = false;
	}		

	repeatType = _repeatType;
	repeatTimes = _repeatTimes; 
	isWithException = hasException();
	exceptionType = _exceptionType;
	//std::cout << _repeatType <<std::endl <<_repeatTimes <<std::endl << _hasException << std:: endl << _exceptionType <<std::endl;
	
	initialzeAttributes();
	return isValid;
}

bool cmdRepeatParser::getRepeatTimesForDailyWeeklyMonthly(std::string repeatDetail) {

	int repeatTypeSize = _repeatType.size();
	int EIndex = repeatDetail.find(_repeatType);

	repeatDetail = repeatDetail.substr(EIndex +  repeatTypeSize - 1);
	std::string repeatTimeString;

	int TIndex = repeatDetail.find_first_of(" ");

	if (isValidIndex(TIndex)) {
		repeatDetail = repeatDetail.substr(TIndex);
	} else {
		_repeatTimes = DEFAULT_TIMES;
		return true;
	}
		
	TIndex = repeatDetail.find_first_not_of(" ");

	if(isValidIndex(TIndex)){
		repeatDetail = repeatDetail.substr(TIndex);
	}	else {
		_repeatTimes = DEFAULT_TIMES;
		return true;
	}
		
	TIndex = repeatDetail.find_first_of(" ");

	if(isValidIndex(TIndex)){
		repeatTimeString = repeatDetail.substr(0, TIndex);
	} else {
		repeatTimeString = repeatDetail;
	}
		
	if(isStringAnInteger(repeatTimeString)) {
		_repeatTimes = std::stoi(repeatTimeString);
		return true;
	} else {
		return false;
	}

}

bool cmdRepeatParser::getExceptionTimes(std::string repeatDetail) {
	int EIndex = repeatDetail.find(EXCEPT_STRING);
	repeatDetail = repeatDetail.substr(EIndex);
	int TIndex;
	if(repeatDetail.size() > EXCEPT_STRING.size()) {
		TIndex = repeatDetail.find(EXCEPT_STRING) + 6;
		repeatDetail = repeatDetail.substr(TIndex);
	} else {
		return false;
	}

	TIndex = repeatDetail.find_first_not_of(" ");

	if(isValidIndex(TIndex)) {
		repeatDetail = repeatDetail.substr(TIndex);
	} else {
		return false;
	}

	TIndex = repeatDetail.find_first_of(" ");

	if(isValidIndex(TIndex)){
		_exceptionType = repeatDetail.substr(0, TIndex);
	    return true;
	} else {
		_exceptionType = repeatDetail;
		return true;
	}

}	


bool cmdRepeatParser::getDetailsForRepeatCertainDayOfAWeek(std::string repeatDetail) {

	int TIndex = repeatDetail.find(STRING_EVERY);
	repeatDetail = repeatDetail.substr(TIndex);
	TIndex = repeatDetail.find_first_of(" ");

	if(isValidIndex(TIndex)) {
		repeatDetail = repeatDetail.substr(TIndex);
	} else {
		return false;
	}
	
	TIndex = repeatDetail.find_first_not_of(" ");

	if(isValidIndex(TIndex)) {
		repeatDetail = repeatDetail.substr(TIndex);
	} else{
		return false;
	}

	TIndex = repeatDetail.find_first_of(" ");

	if(isValidIndex(TIndex)) {
		_repeatType = repeatDetail.substr(0, TIndex);
		return true;
	} else {
		_repeatType = repeatDetail;
		return true;
	}
}		
	

bool cmdRepeatParser::isValidIndex(int TIndex){
	if (TIndex!=std::string::npos && TIndex >= 0) {
		return true;
	} else {
		return false;
	}
}

bool cmdRepeatParser::hasException() {
	int TIndex;
	TIndex = _repeatDetails.find(EXCEPT_STRING);

	if (isValidIndex(TIndex)) {
		_hasException = true;
	} else { 
		_hasException = false;
	}
	
	return _hasException;
}



bool cmdRepeatParser::isDailyWeeklyMonthly(std::string str){
	int indexOne = str.find(STRING_DAILY);
	int indexTwo = str.find(STRING_WEEKLY);
	int indexThree = str.find(STRING_MONTHLY);

	if( isValidIndex(indexOne) ){
		_repeatType = STRING_DAILY;
		return true;
	} else if (isValidIndex(indexTwo)) {
		_repeatType = STRING_WEEKLY;
		return true;
	} else if (isValidIndex(indexThree)) {
		_repeatType = STRING_MONTHLY;
		return true;
	} else {
		return false;
	}
}

bool cmdRepeatParser::isCertainDayOfAWeek(std::string str){
	int Tindex = str.find(STRING_EVERY);
	if (isValidIndex(Tindex)) {
		return true;
	} else {
		return false;
	}
}

bool cmdRepeatParser::isStringAnInteger(std::string str) {
	for (int i = str.size()-1; i>=0; i--) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

std::string cmdRepeatParser::lowercaseRepeatDetail(std::string repeatDetail){
	int n = repeatDetail.size();
	for( int i = 0; i < n; i++){
		if(repeatDetail[i] <='Z' && repeatDetail[i] >= 'A'){
			repeatDetail[i] = repeatDetail[i] - ('Z'-'z');
		}
	}

  return repeatDetail;
}