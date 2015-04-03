#include "cmdHelp.h"
#include <sstream>

const static std::string HELP_ADD = "add <task name> by: date month time\ne.g. add submit report by: 2 mar 1211\n\n";
const static std::string HELP_DELETE = "delete <task number(s)>\ne.g. delete 1   delete 1 2 3\n\n";
const static std::string HELP_DISPLAY = "display undone tasks: display    display done tasks: displayDonen\n\n";
const static std::string HELP_UPDATE = "update <task number> .name new name\ne.g update 1 .name collect homework\n\n";
const static std::string HELP_UPDATE_START = "update <task number> .start new start time\ne.g. update 1 .start 1 mar 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_START = "update <task number> .clear start\ne.g. update 2 .start 2 mar 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_END = "update <task number> .clear end\ne.g. update 2 .end 2 mar 1211\n\n";
const static std::string HELP_UPDATE_END = "update <task number> .start new end time\ne.g. update 1 .end 1 mar 1211\n\n";
const static std::string HELP_MARKASDONE = "mark task(s) as done\ne.g. done 1   done 1 2 3\n\n";
const static std::string HELP_UNDO = "undo last action: undo\n\n";
const static std::string HELP_SEARCH = "search <key words>\ne.g. search homework\n\n";
const static std::string LINE = "================================================\n";

cmdHelp::cmdHelp(void){
}

cmdHelp::~cmdHelp(void){
}

std::string cmdHelp::helpMessage(){
	return LINE+ HELP_ADD + HELP_DELETE + HELP_UPDATE + HELP_UPDATE_START + HELP_UPDATE_END 
		   + HELP_UPDATE_CLEAR_START + HELP_UPDATE_CLEAR_END + HELP_MARKASDONE + HELP_UNDO 
		   + HELP_SEARCH + LINE;
}