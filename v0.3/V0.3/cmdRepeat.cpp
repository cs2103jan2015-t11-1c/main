#include "cmdRepeat.h"

cmdRepeat::cmdRepeat(void){
}

cmdRepeat::~cmdRepeat(void){
}

std::string cmdRepeat::executecmdRepeat(Storage& _storage){
}

std::string cmdRepeat::getRepeatType(){
	std::string repeatType;
	int Tcount;
	Tcount = _taskName.find_first_of(" ");
	repeatType = _taskName.substr(0, Tcount);

	return repeatType;
}

void cmdRepeat::determineRepeatType(){
	std::string repeat;
}

void cmdRepeat::determineRepeatTimes(){
}