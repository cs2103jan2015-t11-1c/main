#include "cmdRepeatParser.h"

cmdRepeatParser::cmdRepeatParser(void){
}


cmdRepeatParser::~cmdRepeatParser(void){
}

//extract repeat frequency(daily, weekly, monthly)
std::string cmdRepeatParser::getRepeatType(std::string& _repeatDetails){
	std::string repeatType;
	int Tcount;
	Tcount = _repeatDetails.find_first_of(" ");
	if (Tcount != std::string::npos) {
		repeatType = _repeatDetails.substr(0, Tcount);
		_repeatDetails = _repeatDetails.substr(Tcount+1);
	}else{
		repeatType = _repeatDetails;
		_repeatDetails.clear();
	}
	return repeatType;
}
